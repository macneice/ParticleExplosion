#include "Screen.h"

Screen::Screen() :
	mWindow(NULL), mRenderer(NULL), mTexture(NULL), mBuffer1(NULL), mBuffer2(NULL) {

}

bool Screen::initalization() {

	//initalize sdl video, and exit if it has a problem 
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return false;

	//initalize the window, and check to see if it has been made
	mWindow = SDL_CreateWindow("Particle Fire", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (mWindow == NULL)
		return false;

	//create the renderer, and check to see if it has been made correctly, destroy if not
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_PRESENTVSYNC);
	if (mRenderer == NULL) {
		SDL_DestroyWindow(mWindow);
		SDL_Quit();
		return false;

	}

	//create the texture, and check to see if it has been initalized properly 
	mTexture = SDL_CreateTexture(mRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (mTexture == NULL) {
		SDL_DestroyRenderer(mRenderer);
		SDL_DestroyWindow(mWindow);
		SDL_Quit();
		return false;

	}

	//create buffer, and don't bother checking memory space. As this is a simple example
	mBuffer1 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
	mBuffer2 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
	clear();

	update();

	return true;
}

void Screen::update() {
	//draw content to the screen
	SDL_UpdateTexture(mTexture, NULL, mBuffer1, SCREEN_WIDTH * sizeof(Uint32));
	SDL_RenderClear(mRenderer);
	SDL_RenderCopy(mRenderer, mTexture, NULL, NULL);
	SDL_RenderPresent(mRenderer);

}

void Screen::clear() {
	memset(mBuffer1, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
	memset(mBuffer2, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));

}

void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {

	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
		return;
	}

	//create color container using 8 bit color code
	//last value is the alpha 
	Uint32 color = 0;
	color += red;
	color <<= 8;
	color += green;
	color <<= 8;
	color += blue;
	color <<= 8;
	color += 0xFF;

	//set value in the buffer
	mBuffer1[x + (y * SCREEN_WIDTH)] = color;

}

bool Screen::processEvents() {
	SDL_Event event;

	//check to see if the quit event has been thrown
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT)
			return false;

	}

	return true;
}

void Screen::close() {
	//deallocate all the data
	delete[] mBuffer1;
	delete[] mBuffer2;
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyTexture(mTexture);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();

}

void Screen::boxBlur() {

	//swap values of the buffers
	Uint32 *temp = mBuffer1;
	mBuffer1 = mBuffer2;
	mBuffer2 = temp;

	//iterate over every pixel in the window
	for (int y = 0; y<SCREEN_HEIGHT; y++) {
		for (int x = 0; x<SCREEN_WIDTH; x++) {

			int redTotal = 0;
			int greenTotal = 0;
			int blueTotal = 0;

			//interate over the 9 pixels around the current pixel
			for (int row = -1; row <= 1; row++) {
				for (int col = -1; col <= 1; col++) {
					int currentX = x + col;
					int currentY = y + row;

					//if the pixel is on the screen, add the red values to red, green to green, and blue to blue
					if (currentX >= 0 && currentX < SCREEN_WIDTH && currentY >= 0 && currentY < SCREEN_HEIGHT) {
						Uint32 color = mBuffer2[currentY * SCREEN_WIDTH + currentX];

						Uint8 red = color >> 24;
						Uint8 green = color >> 16;
						Uint8 blue = color >> 8;

						redTotal += red;
						greenTotal += green;
						blueTotal += blue;


					}
				}

			}

			//calculate the average color of the 9 pixels 
			Uint8 red = redTotal / 9;
			Uint8 green = greenTotal / 9;
			Uint8 blue = blueTotal / 9;

			//set the pixel color
			setPixel(x, y, red, green, blue);

		}


	}

}