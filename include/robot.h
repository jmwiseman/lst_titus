/*
 * titus_robot.h
 *
 *  Created on: Oct 29, 2015
 *      Author: Jules
 */

//For driver mode code
#ifndef TITUS_ROBOT_H_
#define TITUS_ROBOT_H_

#define MOT_LEFT1 4
#define MOT_LEFT2 2
#define MOT_RIGHT1 5
#define MOT_RIGHT2 3

#define JOY_TURN_T 1
#define JOY_FORWARD_T 2
#define JOY_FORWARD2_T 3
#define JOY_DEAD_T 20
#define JOY_STRAFING 4
#define JOY_RAMP 3

#define MOT_INTAKE 1
#define INTAKESPEED 150

#define MOT_FLYWHEEL1 2 //right top clock
#define MOT_FLYWHEEL2 2 //right top clock
#define MOT_FLYWHEEL3 8 //left top counter
#define MOT_FLYWHEEL4 8 //left top counter
#define MOT_FLYWHEEL5 7 //bottom right counter
#define MOT_FLYWHEEL6 7 //bottom right counter
#define MOT_FLYWHEEL7 9 //bottom left clock
#define MOT_FLYWHEEL8 9 //bottom left clock
#define WHEELSPEED 100

#define MOT_RAMP1 1

//For autonomous mode code
#define ENC_RF_TOP 1
#define ENC_RF_BOT 2

#define ENC_LF_TOP 3
#define ENC_LF_BOT 4

#define ENC_LB_TOP 5
#define ENC_LB_BOT 6

#define ENC_RB_TOP 7
#define ENC_RB_BOT 8

#define LCD_PORT uart1



#endif /* TITUS_ROBOT_H_ */
