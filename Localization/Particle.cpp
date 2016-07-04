/*
 * Particle.cpp
 *
 *  Created on: Jul 2, 2016
 *      Author: colman
 */

#include "Particle.h"
#include <math.h>
// Normalize every belief that over 30% probability
#define NORMALIZE_FACTOR 2

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
		angle = (i -333) * 3.14 / 180;

		angle =0;
		int x_map_pos = (this->_xPos + 6.85) / 0.025;
		int y_map_pos = (this->_yPos - 4.73) / 0.025 * -1;
		is_Passed_Obstacle = false;
		vector<vector<bool> > mapgrid = map.Getmap();
		for (int j=0; j<lp->GetRange(i) * 40;j++){
			int colReadPos = x_map_pos + ((double)(cos(angle + this->_yaw * 1.0) * j));
			int rowReadPos = y_map_pos -((double)(sin(angle + this->_yaw *1.0) * j));
			if ( 0 <= rowReadPos && rowReadPos <mapgrid.size() &&
				 0 <= colReadPos &&	colReadPos < mapgrid[0].size() &&
				 mapgrid[rowReadPos][colReadPos] != 1 &&
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
		probabilty = (countHits * 1.0)/ (countHits + countMisses);
	}
	return probabilty;
}

double Particle::ProbByMove(double deltaX, double deltaY, double deltayaw, Map& map){
	double probability =0;
	int x_map_pos = (this->_xPos + 6.85) / 0.025;
	int y_map_pos = (this->_yPos - 4.73) / 0.025 * -1;
	if (map.Getmap()[0].size() > x_map_pos && map.Getmap().size() > y_map_pos){
		// if it isnt obstacle
		if (map.Getmap()[y_map_pos][x_map_pos] != 1)
		{
			probability = 0.9;
		}
	}
	return probability;
}
void Particle::update(double deltaX, double deltaY, double deltayaw,LaserProxy* lp,Map& map){
	this->_xPos += deltaX;
	this->_yPos += deltaY;
	this->_yaw += deltayaw;
	double pred_bel = this->_belief * ProbByMove(deltaX,deltaY,deltayaw,map);
	//double pred_bel = 1;
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

