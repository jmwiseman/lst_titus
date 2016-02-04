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
void controlmotors(int lb, int rb, int lf, int rf)
{
	if(!DONT_MOVE)
	{
		motorSet(MOT_LEFT1,lb);
		//motorSet(MOT_LEFT2,lf);
		motorSet(MOT_RIGHT1,rb);
		//motorSet(MOT_RIGHT2,rf);
	}
}

void titus_controldrive(int t, int f, int s)
{
	printf("titus_controldrive()");
	int strafe = s;
	int turn = t;
	int forward = f;
	int lf,lb,rf,rb;

/*
	int forward_lf = 1  * forward;
	int forward_lb = -1  * forward;
	int forward_rf = -1 * forward;
	int forward_rb = 1 * forward;

	int sideways_lf = 1  * strafe;
	int sideways_lb = -1 * strafe;
	int sideways_rf = 1  * strafe;
	int sideways_rb = -1 * strafe;
//*/

	int forward_lf = 1  * forward;
	int forward_lb = 1  * forward;
	int forward_rf = -1 * forward;
	int forward_rb = -1 * forward;

	int sideways_lf = 1  * strafe;
	int sideways_lb = -1 * strafe;
	int sideways_rf = 1  * strafe;
	int sideways_rb = -1 * strafe;

	lf = forward_lf + sideways_lf;
	lb = forward_lb + sideways_lb;
	rf = forward_rf + sideways_rf;
	rb = forward_rb + sideways_rb;

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

void intakemotors(int intakespeed) {
	if(!DONT_MOVE){
		motorSet(MOT_INTAKE, intakespeed);
	}
}

void intakecontrol(int intake, int outtake) {
	int intakespeed;

	if(intake) {
		intakespeed = INTAKESPEED;
	}
	else if(outtake) {
		intakespeed = -INTAKESPEED;
	}
	else {
		intakespeed = 0;
	}

	intakemotors(intakespeed);
}
void intakeoperation() {

	int joyintake = joystickGetDigital(2,5,JOY_UP);
	int joyouttake = joystickGetDigital(2,5,JOY_DOWN);

	intakecontrol(joyintake,joyouttake);
}

void flywheelmotors(int wheelspeed) {
	motorSet(MOT_FLYWHEEL1, wheelspeed);
	motorSet(MOT_FLYWHEEL2, wheelspeed);
	motorSet(MOT_FLYWHEEL3, -wheelspeed);
	motorSet(MOT_FLYWHEEL4, -wheelspeed);
	motorSet(MOT_FLYWHEEL5, -wheelspeed);
	motorSet(MOT_FLYWHEEL6, -wheelspeed);
	motorSet(MOT_FLYWHEEL7, wheelspeed);
	motorSet(MOT_FLYWHEEL8, wheelspeed);
}
//*
void flywheeloperation() {
	int joyflywheel = WHEELSPEED*joystickGetDigital(2,6,JOY_UP);

	flywheelmotors(joyflywheel);
}//*/

void rampmotors(int rampspeed) {
	motorSet(MOT_RAMP1, rampspeed);
}

void rampoperation() {
	int joyramp = (abs(joystickGetAnalog(2,JOY_RAMP)) > JOY_DEAD_T) ? joystickGetAnalog(2,JOY_RAMP) : 0;

	rampmotors(joyramp);
}

void operatorControl() {
	while(1) {
		driveoperation();
		intakeoperation();
		flywheeloperation();
		delay(20);
	}
}
