/*
 * titus_opcontrol.c
 *
 *  Created on: Oct 29, 2015
 *      Author: Jules
 */


#include <math.h>
#include <../include/API.h>
#include <../include/robot.h>


#define DONT_MOVE 0
void controlmotors(int lb, int rb,int lf,int rf){
	if(!DONT_MOVE){
		motorSet(MOT_LEFT1,lb);
		motorSet(MOT_LEFT2,lf);
		motorSet(MOT_RIGHT1,rb);
		motorSet(MOT_RIGHT2,rf);
	}
}

void titus_controldrive(int straif, int forward, int turn) {
	int lf,lb,rf,rb;
	int pi = 3.14;

	rf=lf=straif*cos(-pi/4)-forward*sin(-pi/4);
	rb=lb=straif*sin(-pi/4)+forward*cos(-pi/4);
	
	rb+=turn;
	rf+=turn;
	lf-=turn;
	lb-=turn;

	controlmotors(lb, rb, lf, rf); 
}

void driveoperation() {
	int joyforward = (abs(joystickGetAnalog(1,JOY_FORWARD_T)) > JOY_DEAD_T) ? joystickGetAnalog(1,JOY_FORWARD_T) : 0;
	int joyturn = (abs((joystickGetAnalog(1,JOY_TURN_T))) > JOY_DEAD_T) ? joystickGetAnalog(1,JOY_TURN_T) : 0;
	int joystrafing = (abs(joystickGetAnalog(1,JOY_STRAFING)) > JOY_DEAD_T) ? joystickGetAnalog(1,JOY_STRAFING) : 0;

	titus_controldrive(joyturn,joyforward,joystrafing);
}

void operatorControl() {

	driveoperation();

}
