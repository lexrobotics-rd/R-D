/*
T4 Management Functions.
All encapsulated for timer management on T4. Used for integrals and derivatives.
*/
bool T4FirstRun = true;
void T4Init(){
	if(T4FirstRun){//Resets it only once, to not mess up anything else being run on T4.
		T4FirstRun = false;
		ClearTimer(T4);
	}
}
float T4DiffUpdate(float& prevTime){
	float diff;
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

USAGE (in loop):
float integral = integrate(i, currvalue);
float derivative = derivative(i, currvalue);
*/
typedef struct{float prev; float prevTime; float integral;} INTR;
float initIntr(INTR* intr){
	T4Init();
	intr->prev=0;
	intr->prevTime=time1[T4];
	intr->integral=0;
}
float integrate(INTR* intr, float curr){
	float diff = T4DiffUpdate(intr->prevTime);
	float tmpprev = intr->prev; intr->prev = curr;
	return (intr->integral += 0.5*(curr + tmpprev)*(diff / 1000.0));//Trapezoidal approximation.
}

typedef struct{float prev; float prevTime;} DERIV;
float initDeriv(DERIV* d){
	T4Init();
	d->prev=0;
	d->prevTime=time1[T4];
}
float derivative(DERIV* d, float curr){
	float diff = T4DiffUpdate(d->prevTime);
	float tmpprev = d->prev; d->prev = curr;
	return (curr - tmpprev) / diff;//Average derivative.
		//Are there better ways to approximate current instantaneous derivative? Maybe use 2nd deriv?
}
