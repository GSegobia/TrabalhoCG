#include "Particles.h"

ParticleSystem::ParticleSystem(void){

	current_particle = 0;

	for(int i = 0; i < NUMBER_OF_PARTICLES; i++)
		particles[i] = generateNewParticle();
}


Particle ParticleSystem::generateNewParticle(void){

	Particle part;

	part.azimuth_rotation = generateRandomNumber(MIN_ROTATION, MAX_ROTATION);
	part.zenith_rotation = generateRandomNumber(MIN_ROTATION, MAX_ROTATION);//240 e 270
	part.surface_translation_factor = generateRandomNumber(MIN_TRANS, MAX_TRANS);
	part.delta_azimuth = generateRandomNumber(MIN_DELTA_ROTATION, MAX_DELTA_ROTATION);
	part.delta_zenith = generateRandomNumber(MIN_DELTA_ROTATION, MAX_DELTA_ROTATION);
	part.delta_surface = generateRandomNumber(MIN_DELTA_SURFACE, MAX_DELTA_SURFACE);
	part.expand_flag = true;

	part.life_time = (int)generateRandomNumber(MIN_LIFETIME, MAX_LIFETIME);

	return part;
}


Particle ParticleSystem::getNextParticle(void){

	current_particle = (current_particle == NUMBER_OF_PARTICLES) ? 0 : current_particle;

	return particles[current_particle++];
}

int ParticleSystem::getNumberOfParticles(void){

	return NUMBER_OF_PARTICLES;
}

float ParticleSystem::generateRandomNumber(float lower, float upper){

	static bool first_time = true;
	time_t random_number_seed;

	if(first_time){

		time(&random_number_seed);
		srand(random_number_seed);
		first_time = false;
	}

	return (lower + ((upper - lower) * (float(rand()) / RAND_MAX)));
}

void ParticleSystem::updateAll(void){

	for(int i = 0; i < NUMBER_OF_PARTICLES; i++){
		if(particles[i].life_time == 0)
			particles[i] = generateNewParticle();
		else{
			
			particles[i].azimuth_rotation += particles[i].delta_azimuth;
			
			particles[i].zenith_rotation += particles[i].delta_zenith;	

			particles[i].surface_translation_factor += particles[i].delta_surface;

			particles[i].life_time -= DELTA_LIFETIME; 
		}
	}
}