#include "T4Math.c" //All the integrals and derivatives with respect to time, measured on T4.

/*
PID Control
INITIALIZE:
PID p;
initPID(p, Kp, Ki, Kd); //Sets the constants, initializes integral, etc.

USAGE (in loop):
float PIDOutput = updatePID(p, currError); //Using the current error, calculates P, I, and D

RESET:
reset(p); //zeroes the integrals and stuff; uses the same constants

All Integrals and Derivatives use Timer 4 on the NXT. Never touch it.
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
	init(pid->integral);
	init(pid->prevErr);
}
void reset(PID* p){
	initPID(p,p->Kp,p->Ki,p->Kd);
}
float updatePID(PID& pid, float error) {
	return pid.Kp * error								//P
		+ pid.Ki * integrate(pid.integral, error);		//I //Does integral need a cap on value?
		+ pid.Kd * derivative(pid.derivative, error);	//D
}
