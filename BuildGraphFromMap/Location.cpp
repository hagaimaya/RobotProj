/*
 * Location.cpp
 *
 *  Created on: Jun 14, 2016
 *      Author: colman
 */

#include "Location.h"


Location::Location(unsigned int row, unsigned int col){
	this->row = row;
	this->col = col;
}
unsigned int Location::get_row(){
	return this->row;
}
unsigned int Location::get_col(){
	return this->col;
}

void Location::set_row(unsigned int row){
	this->row = row;
}
void Location::set_col(unsigned int col){
	this->col = col;
}
Location::~Location() {
	// TODO Auto-generated destructor stub
}

