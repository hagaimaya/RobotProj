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


	if (dY < 0)
	cout << "result : " << result << endl;
	cout << "current : " << currYaw << endl;

	double angle = 0.11;

	//result -=  20 * 3.14 / 180;
	while (abs(result  - currYaw )> 0.05 && distance(currX, currY,x ,y) > 0.05){
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

		cout << "curr Yaw : " << currYaw;
		cout << " expectation :" << result << endl;
	}

	robot->setSpeed(0,0);

	double startedX = currX;
	double startedY = currY;
	cout << "(" << x << "," << y << ")" << endl;
	double temp =1;
	//while (robot->getLaserProxy()->GetRange(333) > 0.45 && distance(currX, currY,startedX, startedY) * 0.025 < distance(startedX, startedY, x, y) * 0.025 /temp ){
	while (distance(currX, currY,x ,y) > 0.05 && distance(currX, currY,x ,y) < 1){
		robot->setSpeed(0.08 , 0);

				robot->read();
				currX = robot->getX();
				currY = robot->getY();

				cout << "curr location: (" << currX << "," << currY << ")" <<endl;
				cout << "next location: (" << x << "," << y << ")" << endl;
				//temp *= 1.03;
	}
	/**while (distance(currX, currY, x, y) *0.001  > slowSpeedRange) {
		robot->setSpeed(linearSpeed, 0);

		robot->read();
		currX = robot->getX();
		currY = robot->getY();

				cout << "x: " << currX << ", y: " << currY << endl;

	}

	while (distance(currX, currY, x, y) *0.001  > tolerance) {
		robot->setSpeed(linearSpeed * slowSpeedRatio, 0);

		robot->read();
		currX = robot->getX();
		currY = robot->getY();
		cout << "x: " << currX << ", y: " << currY << endl;

		currX = robot->getX();
		currY = robot->getY();


	}**/

	robot->setSpeed(0, 0);
}

Driver::~Driver() {
	// TODO Auto-generated destructor stub
}

