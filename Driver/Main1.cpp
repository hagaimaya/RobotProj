/*
 * Main.cpp
 *
 *  Created on: Apr 12, 2016
 *      Author: colman
 */

#include "Robot.h"
#include "Driver.h"

int main1() {
	Robot robot("localhost", 6665);
	robot.setOdometry(2, -3, 0);
	Driver driver(&robot);

	driver.moveToNextWaypoint(3, -3);
	return 0;
}


