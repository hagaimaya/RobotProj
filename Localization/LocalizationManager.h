/*
 * LocalizationManager.h
 *
 *  Created on: Jul 2, 2016
 *      Author: colman
 */

#include "Particle.h"
#include <vector>
using namespace std;

#ifndef LOCALIZATIONMANAGER_H_
#define LOCALIZATIONMANAGER_H_

class LocalizationManager {
private:
	vector<Particle *> _particles;
public:
	LocalizationManager(Particle* particle);

	void update(double deltaX,double deltaY, double yaw,LaserProxy* lp,Map& map);
	void resampleParticles();
	Particle *getBestParticle();
	virtual ~LocalizationManager();
};

#endif /* LOCALIZATIONMANAGER_H_ */
