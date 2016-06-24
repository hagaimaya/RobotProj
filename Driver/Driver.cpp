/*
 * Driver.cpp
 *
 *  Created on: Apr 12, 2016
 *      Author: colman
 */

#include "Driver.h"
#include <cmath>
#include <math.h>
#include <iostream>

#define PI 3.14159265

using namespace std;

Driver::Driver(Robot *robot) : robot(robot) {

}

double Driver::distance(double x1, double y1, double x2, double y2) {
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

void Driver::moveToNextWaypoint(double x, double y) {
	robot->read();
	double currX = robot->getX();
	double currY = robot->getY();
	cout << "x: " << currX << ", y: " << currY << endl;
	double result = atan2 (x - currX,currY - y);
	double currYaw = robot->getYaw();
	double dX = x - currX;
	double dY = currY - y;
	if((dX > 0) && (dY > 0)){
	  //section = 1;
	  result += 0;
	}
	else if((dX < 0) && (dY > 0)){
	   //section = 2;
	  result += PI;
	}
	else if((dX < 0) && (dY < 0)){
	   //section = 3
	  result -= PI;
	}
	else if((dX > 0) && (dY < 0)){
	   //section = 4
	  result -= 0.5*PI;
	}
	else if(x == currX){
	    if(y > currY){
	    	result = PI/2;
	    }
	    if(currY > y){
	    	result = -PI/2;
	    }
	}
	else if(currY == y){
	   if(x > currX){
		   result = 0;
	   }
	   if(currX > x){
		   result = PI;
	   }
	}

	cout << "result : " << result << endl;
	cout << "current : " << currYaw << endl;

	double angle = 0.1;

	while (result - currYaw > 0.01){
		if (result < currYaw && angle > 0){
			angle *= -1;
		}
		robot->setSpeed(0,angle);
		robot->read();
		currYaw = robot->getYaw();
		cout << "curr Yaw : " << currYaw;
		cout << " expectation :" << result << endl;
	}

	robot->setSpeed(0,0);
	while (distance(currX, currY, x, y) > slowSpeedRange) {
		robot->setSpeed(linearSpeed, 0);

		robot->read();
		currX = robot->getX();
		currY = robot->getY();
		cout << "x: " << currX << ", y: " << currY << endl;
	}

	while (distance(currX, currY, x, y) > tolerance) {
		robot->setSpeed(linearSpeed * slowSpeedRatio, 0);

		robot->read();
		currX = robot->getX();
		currY = robot->getY();
		cout << "x: " << currX << ", y: " << currY << endl;
	}

	robot->setSpeed(0, 0);
}

Driver::~Driver() {
	// TODO Auto-generated destructor stub
}

