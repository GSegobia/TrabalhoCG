#include "Particles.h"

ParticleSystem::ParticleSystem(bool first_sphere){

	current_particle = 0;

	for(int i = 0; i < NUMBER_OF_PARTICLES; i++)
		particles[i] = generateNewParticle(first_sphere);
}


Particle ParticleSystem::generateNewParticle(bool first_sphere){

	Particle part;

	part.azimuth_rotation = (int)generateRandomNumber(0, 360);
	part.zenith_rotation = (int)generateRandomNumber(0, 360);//first_sphere ? (int)generateRandomNumber(0, 180) : (int)generateRandomNumber(180, 360);

	part.surface_translation_factor = 0.5;

	part.delta_azimuth = generateRandomNumber(MIN_DELTA_ROTATION, MAX_DELTA_ROTATION);;
	part.delta_zenith = generateRandomNumber(MIN_DELTA_ROTATION, MAX_DELTA_ROTATION);
	part.delta_surface = generateRandomNumber(MIN_DELTA_SURFACE, MAX_DELTA_SURFACE);

	part.sphere_flag = first_sphere;

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

		if(particles[i].sphere_flag){

			particles[i].azimuth_rotation += particles[i].delta_azimuth;
			if(GROW_FIRST){
				if(particles[i].surface_translation_factor < 10)
					particles[i].surface_translation_factor += particles[i].delta_surface;
				else {

					GROW_FIRST = false;
					particles[i].surface_translation_factor -= particles[i].delta_surface;
				}
			} else {

				if(particles[i].surface_translation_factor > 0.5)
					particles[i].surface_translation_factor -= particles[i].delta_surface;
				// else{

				// 	GROW_FIRST = true;
				// 	particles[i].surface_translation_factor += 0.03;
				// }
			}
			//particles[i].zenith_rotation = particles[i].azimuth_rotation;
		}
		else{

			particles[i].zenith_rotation += particles[i].delta_zenith;

			if(!GROW_FIRST){
				if(particles[i].surface_translation_factor < 10)
					particles[i].surface_translation_factor += particles[i].delta_surface;
				else {

					GROW_FIRST = true;
					particles[i].surface_translation_factor -= particles[i].delta_surface;
				}
			} else {

				if(particles[i].surface_translation_factor > 0.5)
					particles[i].surface_translation_factor -= particles[i].delta_surface;
				// else{

				// 	GROW_FIRST = false;
				// 	particles[i].surface_translation_factor += 0.3;
				// }
			}
			//particles[i].zenith_rotation = 15 * sin(particles[i].azimuth_rotation);
		}
	}
}
