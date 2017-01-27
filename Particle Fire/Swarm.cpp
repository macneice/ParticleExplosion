#include "Swarm.h"



Swarm::Swarm(): lastTime(0) {
	mParticles = new Particle[NPARTICLES];

}


Swarm::~Swarm() {
	delete[] mParticles;

}

void Swarm::update(int elapsed) {

	int interval = elapsed - lastTime;

	//load color data into the buffer
	for (int i = 0; i < NPARTICLES; i++) {
		mParticles[i].update(interval);

	}

	lastTime = elapsed;

}
