#ifndef SCREEN_H_
#define SCREEN_H_

#include <SDL.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "Swarm.h"
#undef main

class Screen {
public:
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;

private:
	SDL_Window *mWindow;
	SDL_Renderer * mRenderer;
	SDL_Texture *mTexture;
	Uint32 *mBuffer1;
	Uint32 *mBuffer2;


public:
	Screen();
	bool initalization();
	bool processEvents();
	void close();
	void update();
	void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
	void clear();
	void boxBlur();

};

#endif // !SCREEN_H_