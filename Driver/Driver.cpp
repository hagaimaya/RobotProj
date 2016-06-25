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
#include <stdlib.h>

#define PI 3.14159265

using namespace std;

Driver::Driver(Robot *robot) : robot(robot) {

}

double Driver::distance(double x1, double y1, double x2, double y2) {
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

void Driver::moveToNextWaypoint(double x, double y) {
	robot->read();
	//305, 362
	//x = x - 362;
	//y = y - 305;
	double currX = robot->getX();
	double currY = robot->getY();
	cout << "x: " << currX << ", y: " << currY << endl;

	double currYaw = robot->getYaw();
	double dX = x - currX;
	double dY =  (y - currY) ;

	double result = atan2 (dY,dX);



	cout << "result : " << result << endl;
	cout << "current : " << currYaw << endl;

	double angle = 0.11;
	double startedYaw = currYaw;
	//result -=  20 * 3.14 / 180;
	while (abs(result  - currYaw ) > 0.05){

		robot->setSpeed(0,angle);
		robot->read();
		currYaw = robot->getYaw();

		cout << "curr Yaw : " << currYaw;
		cout << " expectation :" << result << endl;
	}

	robot->setSpeed(0,0);



	while (distance(currX, currY, x, y)  > slowSpeedRange) {
		robot->setSpeed(linearSpeed, 0);

		robot->read();
		currX = robot->getX();
		currY = robot->getY();

				cout << "x: " << currX << ", y: " << currY << endl;

	}

	while (distance(currX, currY, x, y)  > tolerance) {
		robot->setSpeed(linearSpeed * slowSpeedRatio, 0);

		robot->read();
		currX = robot->getX();
		currY = robot->getY();
		cout << "x: " << currX << ", y: " << currY << endl;

		currX = robot->getX();
		currY = robot->getY();


	}

	robot->setSpeed(0, 0);
}

Driver::~Driver() {
	// TODO Auto-generated destructor stub
}

