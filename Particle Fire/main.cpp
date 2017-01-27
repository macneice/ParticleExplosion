#include "Screen.h"
#include <math.h>

using namespace std;

int main(void) {

	srand(time(NULL));

	//initalize the screen
	Screen screen;
	if (screen.initalization() == false) {
		cout << "Error initalzing SDL" << endl;
		return 1;

	}

	//initalize the swarm
	Swarm swarm;

	const Particle * const pParticles = swarm.getParticles();

	while (true) {
		//get the time since the program started in milliseconds
		int elapsed = SDL_GetTicks();

		//update the particle positions, uncomment clear for differnt effect
		//screen.clear();
		swarm.update(elapsed);

		//calculate the particle colors
		Uint8 green = (unsigned char)((1 + sin(elapsed * 0.0001)) * 128);
		Uint8 red = (unsigned char)((1 + sin(elapsed * 0.0002)) * 128);
		Uint8  blue = (unsigned char)((1 + sin(elapsed * 0.0003)) * 128);

		//load color data into the buffer
		for (int i = 0; i < swarm.NPARTICLES; i++) {
			Particle particle = pParticles[i];

			int x = (particle.mX + 1) * screen.SCREEN_WIDTH / 2;
			int y = particle.mY * screen.SCREEN_WIDTH / 2 + screen.SCREEN_HEIGHT/2;

			screen.setPixel(x, y, red, green, blue);
		}

		//add the blur effect, and draw the screen
		screen.boxBlur();
		screen.update();

		// Check for messages/events
		if (screen.processEvents() == false) {
			break;
		}
	}

	screen.close();
	return 0;
}