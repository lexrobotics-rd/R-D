/*
PID.h
Implements PID control.

Schpeeeeeeeeel:
PID.h implements the PID algorithm. "PID" stands for "Proportional," "Integral," and "Derivative." Using 
these three components, the algorithm decides how to act. Proportional is the current error. Most of the 
correction involved is going to be looking at the current error, just because that makes sense. Integral 
is more or less the average error, which helps account for things like gyro drift. Derivative is current 
change in error - if you kick the balancer it'll have a sudden change in error, and Proportional will be 
unable to cope, but Derivative will see a large change in error and help correct any oscillations.

Wikipedia has an even simpler and quite insightful way of explaining it: "P" corrects for current error, 
"I" for past error, and "D" for future error. In that way, it will very effectively maintain balance.


LastUpdatedOn: 10/28/14
LastUpdatedBy: Clive
Status: it works, I think. Tuning is extremely hard.

Notes for tuning:
//Tuning tips: http://robotics.stackexchange.com/questions/167/what-are-good-strategies-for-tuning-pid-loops
//Also, double PID loops: http://forum.arduino.cc/index.php?topic=197688.0
//PID for physical position, not just rotational? (need accel)
//Swag: https://www.youtube.com/watch?v=n_6p-1J551Y
//Maybe we should try a unisphere balancing robot :) https://www.youtube.com/watch?v=bI06lujiD7E
*/

#include "T4Calculus.h"

/* HOW TO USE IT
INITIALIZE:
PID p;
initPID(p, Kp, Ki, Kd); //Sets the constants, initializes integral, etc.

USAGE (in loop):
float PIDOutput = updatePID(p, currError); //Using the current error, calculates P, I, and D
//A good thing to do is two wait ~5-10ms, because the sensors have a polling limit of a few ms.

RESET:
reset(p); //zeroes the integrals and stuff; uses the same constants

All Integrals and Derivatives (and anything else using T4Calculus.h) use Timer 4 on the NXT. Never touch it.
*/

typedef struct {
	float Kp;
	float Ki;
	float Kd;
	INTR integral;
	DERIV derivative;
} PID;
void initPID(PID* pid, float p, float i, float d){
	pid->Kp = p;
	pid->Ki = i;
	pid->Kd = d;
	initIntr(pid->integral);
	initDeriv(pid->derivative);
}
void reset(PID* p){
	initPID(p,p->Kp,p->Ki,p->Kd);
}
float updatePID(PID& pid, float error) {
	return pid.Kp * error								//P
		+ pid.Ki * integrate(pid.integral, error)		//I //Does integral need a cap on value?
		+ pid.Kd * derivative(pid.derivative, error);	//D
}
