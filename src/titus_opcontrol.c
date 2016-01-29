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

void titus_controldrive(int t, int f, int s) {
	int strafe=s;
	int turn=t;
	int forward=f;
	int lf,lb,rf,rb;

	int forward_lf = 1  * forward;
	int forward_lb = 1  * forward;
	int forward_rf = -1 * forward;
	int forward_rb = -1 * forward;

	int sideways_lf = 1  * strafe;
	int sideways_lb = -1 * strafe;
	int sideways_rf = 1  * strafe;
	int sideways_rb = -1 * strafe;


	/*
	float pi = 3.14;

	rf=lb=straif*cos(-pi/4)-forward*sin(-pi/4);
	lb=-lb;
	rb=lf=straif*sin(-pi/4)+forward*cos(-pi/4);
	lf=-lf;
	rf=lb=straif;
	lb=-lb;
	rb=lf=forward;
	lf=-lf;
	//*/


	lf = forward_lf + sideways_lf;
	lb = forward_lb + sideways_lb;
	rf = forward_rf + sideways_rf;
	rb = forward_rb + sideways_rb;

	//*/
	lf+=turn;
	lb+=turn;
	rf+=turn;
	rb+=turn;

	controlmotors(lb, rb, lf, rf); 
}
void controldrive(int turn, int forward)
{
	titus_controldrive(turn, forward, 0);
}

void driveoperation() {
	int joyforward = (abs(joystickGetAnalog(1,JOY_FORWARD_T)) > JOY_DEAD_T) ? joystickGetAnalog(1,JOY_FORWARD_T) : 0;
	int joyforward2 = (abs(joystickGetAnalog(1,JOY_FORWARD2_T)) > JOY_DEAD_T) ? joystickGetAnalog(1,JOY_FORWARD2_T) : 0;
	int joyturn = (abs((joystickGetAnalog(1,JOY_TURN_T))) > JOY_DEAD_T) ? joystickGetAnalog(1,JOY_TURN_T) : 0;
	int joystrafing = (abs(joystickGetAnalog(1,JOY_STRAFING)) > JOY_DEAD_T) ? joystickGetAnalog(1,JOY_STRAFING) : 0;

	titus_controldrive(joyturn,joyforward+joyforward2,joystrafing);
}

void operatorControl() {
	while(1) 
		driveoperation();

}
