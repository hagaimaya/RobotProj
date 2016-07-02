/*
 * Particle.cpp
 *
 *  Created on: Jul 2, 2016
 *      Author: colman
 */

#include "Particle.h"

// Normalize every belief that over 30% probability
#define NORMALIZE_FACTOR 3

Particle::Particle() {
	// TODO Auto-generated constructor stub

}

Particle::Particle(double xPos, double yPos, double yaw, Map map){
	this->_xPos = xPos;
	_yPos = yPos;
	_yaw = yaw;
	this->_belief = 1;
	vector<vector<bool> > mapgrid = map.Getmap();
	this->map.resize(mapgrid.size());
	for (unsigned int i=0;i<mapgrid.size();++i){
		this->map[i].resize(mapgrid[i].size());
		for(unsigned int j=0;j<mapgrid[i].size();++j){
			this->map[i][j] = mapgrid[i][j];
		}
	}
}
double Particle::ProbByMesure(LaserProxy lp){
	double probabilty =0;

	return probabilty;
}

double Particle::ProbByMove(double deltaX, double deltaY, double deltayaw){
	double probability =0;

	// if it isnt obstacle
	if (this->map[this->_yPos][this->_xPos] != 1)
	{

	}
	return probability;
}
void Particle::update(double deltaX, double deltaY, double deltayaw,LaserProxy lp){
	this->_xPos += deltaX;
	this->_yPos += deltaY;
	this->_yaw += deltayaw;
	double pred_bel = this->_belief * ProbByMove(deltaX,deltaY,deltayaw);
	this->_belief = NORMALIZE_FACTOR * pred_bel * ProbByMesure(lp);
}
double Particle::getBelief();
void Particle::printPosition();

Particle::~Particle() {
	// TODO Auto-generated destructor stub
}

