/*
 * Robot.cpp
 *
 *  Created on: Apr 12, 2016
 *      Author: colman
 */

#include "Robot.h"
#include <iostream>

Robot::Robot(string ip, int port) {
	pc = new PlayerClient(ip, port);
	pp = new Position2dProxy(pc);
	pp->SetMotorEnable(true);
	lp = new LaserProxy(pc);
	xPos=0;
	yPos=0;
	yawPos=0;
	deltaX=0;
	deltaY=0;
	deltaYaw=0;
}

void Robot::read() {
	pc->Read();



}

double Robot::getX() {
	return pp->GetXPos();
}

double Robot::getY() {
	return pp->GetYPos();
}

double Robot::getYaw() {
	double yawPos = pp->GetYaw();
	if (yawPos > 3.14){
		yawPos = yawPos - 3.14 ;
	}

	return yawPos;
}
double Robot::getDeltaX(){
	return this->deltaX;
}
double Robot::getDeltaY(){
	return this->deltaY;
}
double Robot::getDeltaYaw(){
	return this->deltaYaw;
}
void Robot::setSpeed(double linearSpeed, double angularSpeed) {
	pp->SetSpeed(linearSpeed, angularSpeed);
}
void Robot::CalculateDelats(){
	this->deltaY = getY() - this->yPos;
	this->deltaYaw = getYaw() - this->yawPos;
	this->deltaX = getX() - this->xPos;
	this->xPos = getX();
	this->yPos = getY();
	this->yawPos = getYaw();


}
void Robot::setOdometry(double x, double y, double yaw) {
	pp->SetOdometry(x, y, yaw);

	this->xPos =x;
	this->yPos = y;
	this->yawPos = yaw;
}

LaserProxy* Robot::getLaserProxy(){
	return this->lp;
}

float Robot::getLaserRead(int index) {
	return ((*this->lp).GetRange(index));
}

Robot::~Robot() {
	delete lp;
	delete pp;
	delete pc;
}

