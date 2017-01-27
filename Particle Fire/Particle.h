#ifndef PARTICLE_H_
#define PARTICLE_H_


#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>

class Particle {
public:
	double mX;
	double mY;

public:
	Particle();
	~Particle();
	void update(int interval);


private:
	double mSpeed;
	double mDirection;


};

#endif // !PARTICLE_H_