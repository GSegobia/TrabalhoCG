#include <cmath>
#include <cstdlib>
#include <ctime>

#include "GlobalParticlesValue.h"

struct Particle{

	float azimuth_rotation, zenith_rotation, surface_translation_factor;
	float delta_azimuth, delta_zenith, delta_surface;
	int life_time;
	bool sphere_flag;
};

class ParticleSystem{

public:
	ParticleSystem(bool first_sphere);
	Particle getNextParticle(void);
	void updateAll(void);
	int getNumberOfParticles(void);

private:
	Particle particles[NUMBER_OF_PARTICLES];
	int current_particle;
	float generateRandomNumber(float lower, float upper);
	Particle generateNewParticle(bool first_sphere);
};
