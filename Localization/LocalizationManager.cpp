/*
 * LocalizationManager.cpp
 *
 *  Created on: Jul 2, 2016
 *      Author: colman
 */

#include "LocalizationManager.h"
#define MAX_PARTICLES 1000
LocalizationManager::LocalizationManager(Particle* particle) {
	// TODO Auto-generated constructor stub
	this->_particles.push_back(particle);
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
		if (this->_particles[particleIndex]->getBelief() < 0.2){
			this->_particles.erase(this->_particles.begin() + particleIndex);
			particleIndex--;
		}
	}

	if (this->_particles.size() == 0){
		cout << "0 particles"<<endl;
		throw "eerrer";
	}
	int size = this->_particles.size();
	// from the left particles we will create another particles
	for (int particleIndex =0; particleIndex < size && this->_particles.size() <= MAX_PARTICLES; ++particleIndex){
		if (this->_particles[particleIndex]->getBelief() > 0.8)
		{
			for (int i=0; i< 20; ++i){
				this->_particles.push_back(new Particle(this->_particles[particleIndex]->getXPos() + static_cast<double>(rand() % 100 / 10000 - rand() % 100 / 10000 ),
						this->_particles[particleIndex]->getYPos() + static_cast<double>(rand() % 100 / 10000 - rand() % 100 / 10000 ),
						this->_particles[particleIndex]->getyaw() + static_cast<double>(rand() % 360 - rand() % 360) * 3.14/180));
			}
		}
	}

	cout << "particle num: " << this->_particles.size() << endl;
	for (int particleIndex =0; particleIndex < this->_particles.size(); ++particleIndex){
		cout << "particle[" << particleIndex << "] (" << _particles[particleIndex]->getXPos() << ","
				                                      << _particles[particleIndex]->getYPos() << ","
				                                      << _particles[particleIndex]->getyaw() << ") belief: " << _particles[particleIndex]->getBelief() << endl;
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
