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
void controlmotors(int lb, int rb, int lf, int rf){
	if(!DONT_MOVE){
		motorSet(MOT_LEFT1,lb);
		motorSet(MOT_LEFT2,lf);
		motorSet(MOT_RIGHT1,rb);
		motorSet(MOT_RIGHT2,rf);
	}
}

void titus_controldrive(int t, int s, int f) {
	double straif=f;
	double turn=t;
	double forward=f;
	int lf,lb,rf,rb;
	float pi = 3.14;

	rf=lb=straif*cos(-pi/4)-forward*sin(-pi/4);
	lb=-lb;
	rb=lf=straif*sin(-pi/4)+forward*cos(-pi/4);
	lf=-lf;

/*	rf=lb=straif;
	lb=-lb;
	rb=lf=forward;
	lf=-lf;*/
	rb+=turn;
	rf-=turn;
	lf-=turn;
	lb+=turn;

	controlmotors(lb, rb, lf, rf); 
}

void driveoperation() {
	int joyforward = (abs(joystickGetAnalog(1,JOY_FORWARD_T)) > JOY_DEAD_T) ? joystickGetAnalog(1,JOY_FORWARD_T) : 0;
	int joyturn = (abs((joystickGetAnalog(1,JOY_TURN_T))) > JOY_DEAD_T) ? joystickGetAnalog(1,JOY_TURN_T) : 0;
	int joystrafing = (abs(joystickGetAnalog(1,JOY_STRAFING)) > JOY_DEAD_T) ? joystickGetAnalog(1,JOY_STRAFING) : 0;

	titus_controldrive(joyturn,joyforward,joystrafing);
}

void intakemotors(int intakespeed) {
	if(!DONT_MOVE){
		motorSet(MOT_INTAKE1, intakespeed);
		motorSet(MOT_INTAKE2, intakespeed);
		motorSet(MOT_INTAKE3, intakespeed);
	}
}

void intakecontrol(int intake, int outtake) {
	int intakespeed;

	if(intake) {
		intakespeed = intake;
	}
	else if(outtake) {
		intakespeed = -outtake;
	}
	else {
		intakespeed = 0;
	}

	intakemotors(intakespeed);
}
void intakeoperation() {

	int joyintake = (abs(joystickGetDigital(1,5,JOY_UP)) > JOY_DEAD_T) ? joystickGetDigital(1,5,JOY_UP) : 0; //Change the Joystick number to 2 after testing
	int joyouttake = (abs(joystickGetDigital(1,5,JOY_DOWN)) > JOY_DEAD_T) ? joystickGetDigital(1,5,JOY_DOWN) : 0; //Change the Joystick number to 2 after testing

	intakecontrol(joyintake,joyouttake);
}

void operatorControl() {
	while(1) {
		driveoperation();
		intakeoperation();
	}
}
