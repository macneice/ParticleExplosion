#include "Particle.h"

#include <iostream>
using namespace std;

//initalize the position of the particle when it is created
Particle::Particle() :mX(0), mY(0) {
	mDirection = (2.0 * M_PI  * rand()) / RAND_MAX;
	mSpeed = (0.01 * rand()) / RAND_MAX;

	mSpeed *= mSpeed;

}


Particle::~Particle() {
}

//update the position of the particle
void Particle::update(int interval) {

	mDirection += interval * 0.0003;

	double xSpeed = mSpeed * cos(mDirection);
	double ySpeed = mSpeed * sin(mDirection);

	mX += xSpeed * interval;
	mY += ySpeed * interval;


}
