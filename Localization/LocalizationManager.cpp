/*
 * LocalizationManager.cpp
 *
 *  Created on: Jul 2, 2016
 *      Author: colman
 */

#include "LocalizationManager.h"
#define MAX_PARTICLES 50
#define BAD_PARTICLE 0.2
#define GOOD_PARTICLE 0.7
LocalizationManager::LocalizationManager() {
	this->_particles.push_back(new Particle(-6.85 + 362 *0.025,4.75 - 305 * 0.025,20 * 3.14 / 180));
	// TODO Auto-generated constructor stub
	for (int index = 0; index < MAX_PARTICLES / 5; index++){
				double x= -6.85 + (360 - static_cast<double>(rand() % 200) )* 0.025;
				double y = 4.73  - ((305 - static_cast<double>(rand() % 160) )* 0.025 );
				double yaw = static_cast<double>(rand() % 314 / 100 );
				this->_particles.push_back(new Particle(x, y,yaw));
			}
}

LocalizationManager::~LocalizationManager() {
	// TODO Auto-generated destructor stub
}

void LocalizationManager::update(double deltaX,double deltaY, double yaw,LaserProxy* lp, Map& map){
	for (int particleIndex =0; particleIndex < this->_particles.size(); ++particleIndex){
		this->_particles[particleIndex]->update(deltaX, deltaY,yaw,lp, map);
	}
}

void LocalizationManager::resampleParticles(Robot& robot){
	// delete unneeded particles
	for (int particleIndex =0; particleIndex < this->_particles.size(); ++particleIndex){
		if (this->_particles[particleIndex]->getBelief() < BAD_PARTICLE){
			this->_particles.erase(this->_particles.begin() + particleIndex);
			particleIndex--;
		}

	}

	int size = this->_particles.size();
	// from the left particles we will create another particles
	for (int particleIndex =0; particleIndex < size && this->_particles.size() <= MAX_PARTICLES; ++particleIndex){
		if (this->_particles[particleIndex]->getBelief() > GOOD_PARTICLE)
		{
			for (int i=0; i< 20; ++i){
				this->_particles.push_back(new Particle(this->_particles[particleIndex]->getXPos() + static_cast<double>(rand() % 100 / 1000 - rand() % 100 / 10000 ),
						this->_particles[particleIndex]->getYPos() + static_cast<double>(rand() % 100 / 1000 - rand() % 100 / 1000 ),
						this->_particles[particleIndex]->getyaw() + static_cast<double>(rand() % 360 - rand() % 360) * 3.14/180));
			}
		}
	}
	if (this->_particles.size() == 0){
		throw ;
		for (int index = 0; index < MAX_PARTICLES / 5; index++){
			double x= -6.85 + (360 - static_cast<double>(rand() % 200) )* 0.025;
			double y = 4.73  - ((305 - static_cast<double>(rand() % 160) )* 0.025 );
			double yaw = static_cast<double>(rand() % 314 / 100 );
			this->_particles.push_back(new Particle(x, y,yaw));
		}

	}

}

Particle *LocalizationManager::getBestParticle(){
	double maxBelief =  this->_particles[0]->getBelief();
	Particle bestParticle = *this->_particles[0];
	for (int particleIndex =0; particleIndex < this->_particles.size(); ++particleIndex){
			if (this->_particles[particleIndex]->getBelief() > maxBelief){
				maxBelief = this->_particles[particleIndex]->getBelief();
				bestParticle = *this->_particles[particleIndex];
			}
	}

	return &bestParticle;
}
