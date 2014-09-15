typedef struct {
	float Kp;
	float Ki;
	float Kd;
	float integral;//MaxIntegral is generally a bad idea, I think.
	float prevErr;//For calculating derivative.
} PID;

/*
Usage:
Initialize with initPID(float Kp, float Ki, float Kd, float gain) [returns a new PID pidstruct]
Update with updatePID(PID pidstruct, float error) [returns float pid-adjusted error, to put into motors with appropriate gain.]

Notes: don't use any timer between initPID and updatePID.
Uses Timer 4 on the NXT.
*/

PID initPID(float p, float i, float d){
	PID pid;
	pid.Kp = p;
	pid.Ki = i;
	pid.Kd = d;
	pid.integral = 0;
	pid.prevErr = 0;
	ClearTimer(T4);//sketchy
	return pid;
}

float updatePID(PID& pid, float error) {
	float delT = time1[T4] / 1000.0; //Delta time, seconds.
	ClearTimer(T4);
	//If this presents problems, change it to "float delT = 1.0;" or something.
	
	pid.integral += 0.5 * (error + pid.prevErr) * delT; //Trapezoidal Approximation
	
	float pTerm = pid.Kp * error;
	float iTerm = pid.Ki * pid.integral;
	float dTerm = pid.Kd * (error - pid.prevErr) / delT; //Average Rate of Change
	
	pid.prevErr = error;
	
	return (pTerm + iTerm + dTerm);
}
