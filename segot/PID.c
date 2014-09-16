/*
T4 Management Functions.
All encapsulated for timer management on T4. Used for integrals and derivatives.
*/
bool T4FirstRun = true;
int T4(){
	return time1[T4];
}
void T4Init(){
	if(T4FirstRun){//Resets it only once, to not mess up anything else being run on T4.
		T4FirstRun = false;
		ClearTimer(T4);
	}
}
double T4DiffUpdate(float& prevTime){
	double diff;
	if(prevTime > time1[T4])//Working around looparound of 
		diff = 65535 + (time1[T4] - prevTime); //Does this work? Is it precise enough?
	else
		diff = time1[T4] - prevTime;
		//Delta time, in centiseconds. Can store up to 32767 milliseconds, so about 30 seconds. Plus there's looparound compensation.
	
	prevTime = time1[T4];
	
	return diff;
}

/*
Derivatives and Integrals.
INITIALIZE:
INTR i; init(i);
DERIV d; init(d);

USAGE:
integrate(i, currvalue);
derivative(i, currvalue);
*/
typedef struct{float prev; float prevTime; float integral;} INTR;
float init(INTR* intr){
	T4Init();
	intr->prev=0;
	intr->prevTime=T4();
	intr->integral=0;
}
float integrate(INTR* intr, float curr){
	float diff = T4DiffUpdate(intr->prevTime);
	float tmpprev = d->prev; d->prev = curr;
	return (intr->integral += 0.5*(curr + tmpprev)*(diff / 1000.0));//Trapezoidal approximation.
}

typedef struct{float prev; float prevTime;} DERIV;
float init(INTR* intr){
	T4Init();
	intr->prev=0;
	intr->prevTime=T4();
}
float derivative(DERIV d, float curr){
	float diff = T4DiffUpdate(d->prevTime);
	float tmpprev = d->prev; d->prev = curr;
	return (curr - tmpprev) / diff;//Average derivative.
		//Are there better ways to approximate current instantaneous derivative?
}

/*
PID Control
INITIALIZE:
PID p;
initPID(p, Kp, Ki, Kd); //Sets the constants, initializes integral, etc.

USAGE:
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
