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
#include <unistd.h>
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

	double currYaw = robot->getYaw();
	double dX = x - currX;
	double dY =  (y - currY) ;

	double result = atan2 (dY,dX);


	double angle = 0.11;

	//result -=  20 * 3.14 / 180;
	while (((int)((abs(result  - currYaw ) * 100)) % 314) * 1.0 / 100.0 > 0.05 ){
		//if (((int)((abs(result  - currYaw ) * 100)) % 314) * 1.0 / 100.0 < 0.5){
		//	angle = 0.03;
		//}
		//cout <<"result: " << result << " (" << robot->getX() << "," << robot->getY() << "," << robot->getYaw() << ")"<< endl;
		if (((result < 0 &&  currYaw < 0 && result > currYaw) ||
			(result < -PI /2 && currYaw > PI / 2) ||
			(result > 0 && currYaw > 0 && result > currYaw) )&&
			angle < 0 ){
				angle *= -1;
		}
		else if (!((result < 0 &&  currYaw < 0 && result > currYaw) ||
			(result < -PI /2 && currYaw > PI / 2) ||
			(result > 0 && currYaw > 0 && result > currYaw) ) &&
			angle > 0){
				angle *= -1;
		}

		robot->setSpeed(0,angle);
		robot->read();
		currYaw = robot->getYaw();

	}

	robot->setSpeed(0,0);

	double startedX = currX;
	double startedY = currY;

	double temp =1;
	//while (robot->getLaserProxy()->GetRange(333) > 0.45 && distance(currX, currY,startedX, startedY) * 0.025 < distance(startedX, startedY, x, y) * 0.025 /temp ){
	while (distance(currX, currY,x ,y) > 0.05 ){
		robot->setSpeed(0.08 , 0);
		robot->read();
		currX = robot->getX();
		currY = robot->getY();

	}

	robot->setSpeed(0, 0);
}

Driver::~Driver() {
	// TODO Auto-generated destructor stub
}

