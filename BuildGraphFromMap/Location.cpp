/*
 * Location.cpp
 *
 *  Created on: Jun 14, 2016
 *      Author: colman
 */

#include "Location.h"
#include <math.h>

Location::Location(double row, double col){
	this->row = row;
	this->col = col;
}
double Location::get_row(){
	return this->row;
}
double Location::get_col(){
	return this->col;
}

void Location::set_row(double row){
	this->row = row;
}
void Location::set_col(double col){
	this->col = col;
}
Location::~Location() {
	// TODO Auto-generated destructor stub
}

double Location::calc_distance(Location* otherlocation){
		return sqrt(pow(this->get_row() - otherlocation->get_row(), 2) + pow(this->get_col() - otherlocation->get_col(), 2));
}
