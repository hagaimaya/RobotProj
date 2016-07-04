/*
 * Robot.h
 *
 *  Created on: Apr 12, 2016
 *      Author: colman
 */

#ifndef ROBOT_H_
#define ROBOT_H_

#include <libplayerc++/playerc++.h>
#include <string>
using namespace PlayerCc;
using namespace std;

class Robot {
private:
	PlayerClient *pc;
	Position2dProxy *pp;
	LaserProxy *lp;
	double xPos;
	double yPos;
	double yawPos;
	double deltaX;
	double deltaY;
	double deltaYaw;

public:
	Robot(string ip, int port);
	void read();
	double getX();
	double getY();
	double getDeltaX();
	double getDeltaY();
	double getDeltaYaw();
	void CalculateDelats();
	void setOdometry(double x, double y, double yaw);
	void setSpeed(double linearSpeed, double angularSpeed);
	double getYaw();
	LaserProxy* getLaserProxy();
	float getLaserRead(int index);
	virtual ~Robot();
};

#endif /* ROBOT_H_ */
