/*
 * LocalizationManager.cpp
 *
 *  Created on: Jul 2, 2016
 *      Author: colman
 */

#include "LocalizationManager.h"

LocalizationManager::LocalizationManager() {
	// TODO Auto-generated constructor stub

}

LocalizationManager::~LocalizationManager() {
	// TODO Auto-generated destructor stub
}

void LocalizationManager::update(double deltaX,double deltaY, double yaw,LaserProxy* lp, Map& map){
	for (int particleIndex =0; particleIndex < this->_particles.size(); ++particleIndex){
		this->_particles[particleIndex]->update(deltaX, deltaY,yaw,lp, map);
	}
}

void LocalizationManager::resampleParticles(){
	// delete unneeded particles
	for (int particleIndex =0; particleIndex < this->_particles.size(); ++particleIndex){
		if (this->_particles[particleIndex]->getBelief() < 0.6){
			this->_particles.erase(this->_particles.begin() + particleIndex);
			particleIndex--;
		}
	}

	// from the left particles we will create another particles
	for (int particleIndex =0; particleIndex < this->_particles.size(); ++particleIndex){
		for (int i=0; i< 20; ++i){
			this->_particles.push_back(new Particle(this->_particles[particleIndex]->getXPos() + static_cast<double>(rand() % 100 / 10000 - rand() % 100 / 10000 ),
													this->_particles[particleIndex]->getYPos() + static_cast<double>(rand() % 100 / 10000 - rand() % 100 / 10000 ),
													this->_particles[particleIndex]->getyaw() + static_cast<double>(rand() % 360 - rand() % 360) * 3.14/180));
		}
	}
}
