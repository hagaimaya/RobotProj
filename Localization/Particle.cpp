/*
 * Particle.cpp
 *
 *  Created on: Jul 2, 2016
 *      Author: colman
 */

#include "Particle.h"
#include <math.h>
// Normalize every belief that over 30% probability
#define NORMALIZE_FACTOR 3

Particle::Particle() {
	// TODO Auto-generated constructor stub

}

Particle::Particle(double xPos, double yPos, double yaw){
	this->_xPos = xPos;
	_yPos = yPos;
	_yaw = yaw;
	this->_belief = 1;

}
double Particle::ProbByMesure(LaserProxy* lp,Map& map){
	double probabilty =0;
	double angle;
	int countMisses = 0;
	int countHits = 0;
	bool is_Passed_Obstacle = false;
	for (int i=0; i< lp->GetCount(); i+=30){
		// angle in radians
		angle = (i * 0.36 - 120) * 3.14 / 180;
		//pathToLocation[i] = new Location(4.73  - (pathToLocation[i]->get_row() + 1) * 0.025,
		//									-6.85 + (pathToLocation[i]->get_col() + 1) * 0.025);
		int x_map_pos = (this->_xPos + 6.85) / 0.025;
		int y_map_pos = (this->_yPos - 4.73) / 0.025 * -1;
		is_Passed_Obstacle = false;
		for (int j=0; j<lp->GetRange(i) * 40;j++){
			int colReadPos = this->_xPos + (cos(angle + this->_yaw) * j);
			int rowReadPos = this->_yPos -(sin(angle + this->_yaw) * j);
			if ( 0 <= rowReadPos && rowReadPos < map.Getmap().size() &&
				 0 <= colReadPos &&	colReadPos < map.Getmap()[0].size() &&
				 map.Getmap()[rowReadPos][colReadPos] != 1 &&
				 !is_Passed_Obstacle){
				countHits++;
			}
			else{
				countMisses++;
				is_Passed_Obstacle = true;
			}
		}
	}

	if (countMisses == 0){
		probabilty = 1;
	}
	else {
		probabilty = countHits / (countHits + countMisses);
	}
	return probabilty;
}

double Particle::ProbByMove(double deltaX, double deltaY, double deltayaw, Map& map){
	double probability =0;
	if (map.Getmap()[0].size() > this->_xPos && map.Getmap().size() > this->_yPos){
		// if it isnt obstacle
		if (map.Getmap()[this->_yPos][this->_xPos] != 1)
		{
			probability = 0.85;
		}
	}
	return probability;
}
void Particle::update(double deltaX, double deltaY, double deltayaw,LaserProxy* lp,Map& map){
	this->_xPos += deltaX;
	this->_yPos += deltaY;
	this->_yaw += deltayaw;
	double pred_bel = this->_belief * ProbByMove(deltaX,deltaY,deltayaw,map);
	this->_belief = NORMALIZE_FACTOR * pred_bel * ProbByMesure(lp,map);
}
double Particle::getBelief(){
	return this->_belief;
}
//void Particle::printPosition();

double Particle::getYPos(){
	return this->_yPos;
}
double Particle::getXPos(){
	return this->_xPos;
}
double Particle::getyaw(){
	return this->_yaw;
}
Particle::~Particle() {
	// TODO Auto-generated destructor stub
}

