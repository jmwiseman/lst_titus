#include <main.h>
#include <math.h>
#include <API.h>
#include <../include/robot.h>
#include <limits.h>

extern void titus_controldrive(int t, int f, int s);
extern void intakecontrol(int intake, int outtake);
void flywheelmotors(int wheelspeed);

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
#define AUTO_SPEED 127
#define TEAM 1 //1 is blue, -1 is red

int get_foreward()
{
	int forward_lf = 1  * encoderGet(lf_encoder);
	int forward_lb = 1  * encoderGet(lb_encoder);
	int forward_rf = -1 * encoderGet(rf_encoder);
	int forward_rb = -1 * encoderGet(rb_encoder);
	int result = (forward_lf + forward_lb + forward_rf + forward_rb) / 4;
	printf("%8d\n\r",result);
	return result;
}

void forward_ticks(int ticks)//negative speed is backward
{
	int speed = AUTO_SPEED;// * abs(ticks)/ticks;
	reset_op();
	int start_ticks = 0;
	titus_controldrive(0, speed, 0);
	while (get_foreward() - start_ticks < ticks)
	{
		//sanity???
		printf("%8d -%8d <%8d == true\n\r", get_foreward(), start_ticks, ticks);
		delay(20);
	}
	titus_controldrive(0, 0, 0);
}

int get_sideways()
{
	//*
	int sideways_lf = 1  * encoderGet(lf_encoder);
	int sideways_lb = -1 * encoderGet(lb_encoder);
	int sideways_rf = 1  * encoderGet(rf_encoder);
	int sideways_rb = -1 * encoderGet(rb_encoder);
	//return (sideways_lf + sideways_lb + sideways_rf + sideways_rb) / 4;
	int result = (sideways_lf + sideways_lb + sideways_rf + sideways_rb) / 4;
	printf("%8d\n\r",result);
	return result;
	//*/
	//return encoderGet(lf_encoder);
}

void sideways_ticks(int ticks)// positive speed means strafe right
{
	int speed = AUTO_SPEED;// * abs(ticks)/ticks;
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
	//return (turn_lf + turn_lb + turn_rf + turn_rb) / 4;
	int result = (turn_lf + turn_lb + turn_rf + turn_rb) / 4;
	printf("%8d\n\r",result);
	return result;
}

void turn_ticks(int ticks)// positive speed means clockwise
{
	int speed = AUTO_SPEED;// * abs(ticks)/ticks;
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

#define D_F 0
#define D_S 2
#define D_T 1
	//*
	int n = 9;
	int m = 11;
	int direc[] = {D_T, D_T,   D_F,  D_T, D_F, D_T,  D_F, D_T, D_F,    D_F, D_T};
	int ticks[] = {270,-270,  1377,-1080,1315,1080,-3005,1080,1315,  -2630,-540};

	// go get balls
	for(int i=0;i<n;i++)
	{
		//ticks[i] *= TEAM;
		if(direc[i]==D_F)
		{
			forward_ticks(ticks[i]);
		}
		//else if(direc[i]==D_S)
		//{
		//	sideways_ticks(TEAM*ticks[i]);
		//}
		else if(direc[i]==D_T)
		{
			turn_ticks(TEAM*ticks[i]);
		}
		if(i==n-1)
		{
			intakecontrol(1, 0);
		}
	}
	//come back
	for(int i=n-1;i>=0+2;i--)
	{
		if(i==n-1)
		{
			intakecontrol(0, 0);
		}
		//ticks[i] *= TEAM;
		if(direc[i]==D_F)
		{
			forward_ticks(ticks[i]*(-1));
		}
		//else if(direc[i]==D_S)
		//{
		//	sideways_ticks(TEAM*ticks[i]);
		//}
		else if(direc[i]==D_T)
		{
			turn_ticks(TEAM*ticks[i]*(-1));
		}
	}
	//into launch position
	for(int i=n;i<m;i++)
	{
		//ticks[i] *= TEAM;
		if(direc[i]==D_F)
		{
			forward_ticks(ticks[i]);
		}
		//else if(direc[i]==D_S)
		//{
		//	sideways_ticks(TEAM*ticks[i]);
		//}
		else if(direc[i]==D_T)
		{
			turn_ticks(TEAM*ticks[i]);
		}
	}
	//*/

	flywheelmotors(WHEELSPEED);
	delay(4000);
	while(1)
	{
		printf("--------------Conveyor on--------\n\r");
		intakecontrol(1, 0);
		delay(1000);
		printf("--------------Conveyor off-------\n\r");
		intakecontrol(0, 0);
		delay(1000);
	}



	/*
	int forward  = 1377;
	int right    = 1315;
	int turn     = 1080;
	int left     = 3005;
	int forward2 = 1315;
	forward_ticks(AUTO_SPEED, forward);
	sideways_ticks(AUTO_SPEED*team, right*team);
	turn_ticks(AUTO_SPEED*team, turn*team);
	sideways_ticks(-AUTO_SPEED*team, -left*team);
	forward_ticks(AUTO_SPEED, forward2);
	//*/

}

void init_encoders()
{
	rf_encoder = encoderInit(ENC_RF_TOP,ENC_RF_BOT,0);
	lf_encoder = encoderInit(ENC_LF_TOP,ENC_LF_BOT,0);
	lb_encoder = encoderInit(ENC_LB_TOP,ENC_LB_BOT,0);
	rb_encoder = encoderInit(ENC_RB_TOP,ENC_RB_BOT,0);
}


void autonomous()
{
	//*
	//test
	//titus_controldrive(0, AUTO_SPEED, 0);
	//delay(1000);
	/*
	while(1)
	{
		delay(100);
		printf("%8d\n\r",get_foreward());
	}
	//*/

	/*
	//initialize encoders and reset them
	init_encoders();
	reset_op();

	//navigational code
	runop();

	//*/
}
