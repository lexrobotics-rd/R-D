/*
T4Calculus.h

LastUpdatedOn: [date]
LastUpdatedBy: [name]
Status: [status - final scrim copy, compiles but untested, just started, etc.]
*/


/* HOW TO USE IT
T4 (timer 4 on NXT) Management Functions.
All encapsulated for timer management on T4. Used for integrals and derivatives.

INIT
T4Init();
//at the beginning of anywhere. It's smart enough only to do anything once.

RUN
T4DiffUpdate(prevtime);
//Updates prevtime to the current time, and returns the difference in milliseconds.

Never disturb Timer T4.
*/
bool T4FirstRun = true;
void T4Init(){//Can I run this onload? Is that a bad idea?
	if(T4FirstRun){//Resets it only once, to not mess up anything else being run on T4.
		T4FirstRun = false;
		ClearTimer(T4);
	}
}
int T4DiffUpdate(int& prevTime){//Returns the difference of times (ms), and sets the variable to the new current time.
	int diff;
	if(prevTime > time1[T4])//Working around looparound of
		diff = 65535 + (time1[T4] - prevTime); //Does this work? Is it precise enough?
	else
		diff = time1[T4] - prevTime;
		//Delta time, in centiseconds. Can store up to 32767 milliseconds, so about 30 seconds. Plus there's looparound compensation.

	prevTime = time1[T4];

	return diff;
}

/* HOW TO USE IT
Derivatives and Integrals, with respect to (T4) time.
INITIALIZE:
INTR i; initIntr(i);
DERIV d; initDeriv(d);

USAGE (in loop):
float integralFromZero = integrate(i, currvalue);
float currentDerivative = derivative(d, currvalue);
*/
typedef struct{float prev; float prevTime; float integral;} INTR;
void initIntr(INTR* intr){
	T4Init();
	intr->prev=0;
	intr->prevTime=time1[T4];
	intr->integral=0;
	return;
}
float integrate(INTR* intr, float curr){
	float diff = T4DiffUpdate(intr->prevTime);
	float tmpprev = intr->prev; intr->prev = curr;
	return intr->integral += 0.5*(curr + tmpprev)*(diff / 1000.0);//Trapezoidal approximation.
}

typedef struct{float prev; float prevTime;} DERIV;
void initDeriv(DERIV* d){
	T4Init();
	d->prev=0;
	d->prevTime=time1[T4];
	return;
}
float derivative(DERIV* d, float curr){
	float diff = T4DiffUpdate(d->prevTime);
	float tmpprev = d->prev; d->prev = curr;
	return (curr - tmpprev) / diff;//Average derivative.
		//Are there better ways to approximate current instantaneous derivative? Maybe use 2nd deriv? No.
}
