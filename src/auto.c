#include <main.h>
#include <API.h>
#include <../include/robot.h>
#include <limits.h>

extern void titus_controldrive(int t, int f, int s);

/*
void automotors()
{
	motorSet(MOT_LEFT1, lb);
	motorSet(MOT_LEFT2, lf);
	motorSet(MOT_RIGHT1, rb);
	motorSet(MOT_RIGHT2, rf);
}//*/

void reset_op()
{
	encoderReset(rf_encoder);
	encoderReset(lf_encoder);
	encoderReset(rb_encoder);
	encoderReset(lb_encoder);
}

int get_foreward()
{
	int forward_lf = 1  * encoderGet(lf_encoder);
	int forward_lb = 1  * encoderGet(lb_encoder);
	int forward_rf = -1 * encoderGet(rf_encoder);
	int forward_rb = -1 * encoderGet(rb_encoder);
	return (forward_lf + forward_lb + forward_rf + forward_rb) / 4;
}

void forward_ticks(int speed, int ticks)//negative speed is backward
{
	reset_op();
	int start_ticks = 0;
	titus_controldrive(0, speed, 0);
	while (get_foreward() - start_ticks < ticks)
	{
		delay(20);
	}
	titus_controldrive(0, 0, 0);
}

int get_sideways()
{
	int sideways_lf = 1  * encoderGet(lf_encoder);
	int sideways_lb = -1 * encoderGet(lb_encoder);
	int sideways_rf = 1  * encoderGet(rf_encoder);
	int sideways_rb = -1 * encoderGet(rb_encoder);
	return (sideways_lf + sideways_lb + sideways_rf + sideways_rb) / 4;
}

void sideways_ticks(int speed, int ticks)// positive speed means strafe right
{
	reset_op();
	int start_ticks = 0;
	titus_controldrive(0, 0, speed);
	while (get_sideways() - start_ticks < ticks)
	{
		delay(20);
	}
	titus_controldrive(0, 0, 0);
}

int get_turn()
{
	int turn_lf = 1 * encoderGet(lf_encoder);
	int turn_lb = 1 * encoderGet(lb_encoder);
	int turn_rf = 1 * encoderGet(rf_encoder);
	int turn_rb = 1 * encoderGet(rb_encoder);
	return (turn_lf + turn_lb + turn_rf + turn_rb) / 4;
}

void turn_ticks(int speed, int ticks)// positive speed means clockwise
{
	reset_op();
	int start_ticks = 0;
	titus_controldrive(speed, 0, 0);
	while (get_turn() - start_ticks < ticks)
	{
		delay(20);
	}
	titus_controldrive(0, 0, 0);
}


void runop()
{
	int AUTO_SPEED = 127;
	int forward  = 1377;
	int left     = 1315;
	int turn     = 1080;
	int right    = 3005;
	int forward2 = 1315;

	forward_ticks(AUTO_SPEED, forward);
	sideways_ticks(-AUTO_SPEED, -left);
	turn_ticks(AUTO_SPEED, turn);
	sideways_ticks(AUTO_SPEED, right);
	forward_ticks(AUTO_SPEED, forward2);

}


void autonomous()
{
	reset_op();
	runop();
}
