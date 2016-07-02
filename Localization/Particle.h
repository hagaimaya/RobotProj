/*
 * Particle.h
 *
 *  Created on: Jul 2, 2016
 *      Author: colman
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_
#include <vector>
#include "../BuildGraphFromMap/Map.h"
#include "../Driver/Robot.h"
using namespace std;

class Particle {
private:
	double _xPos;
	double _yPos;
	double _yaw;
	double _belief;
	vector<vector<int> > map;

	/**
	 * Function Name: probByMove
	 * Summary      : Calculate the probability of this point as the current location
	 * return: number between 0 and 1
	 */
	double ProbByMove(double deltaX, double deltaY,double deltayaw);

	/**
	 * Function Name: ProbByMeasure
	 * Summary      : Calculate the probability of this point as the current location
	 * return       : number between  0 and 1
	 */
	double ProbByMesure(LaserProxy lp);

public:
	Particle();
	Particle(double xPos, double yPos, double yaw, Map map);
	double getBelief();
	void update(double deltaX, double deltaY, double deltayaw, LaserProxy lp);
	void printPosition();
	virtual ~Particle();
};

#endif /* PARTICLE_H_ */
