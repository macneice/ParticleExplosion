#ifndef SWARM_H_
#define SWARM_H_

#include "Particle.h"

class Swarm {
public:
	const int NPARTICLES = 5000;

private:
	Particle *mParticles;
	int lastTime;

public:
	Swarm();
	~Swarm();
	 const Particle *const getParticles() { return mParticles; };
	 void update(int elapsed);

};

#endif // !SWARM_H_