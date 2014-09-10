typedef struct {
	float Kp;
	float Ki;
	float Kd;
	float integral;
	float maxIntegral;
	float prevPosition;
} PID;

float updatePID(PID &pid, float error, float position) {
	float pTerm = pid.Kp * error;
	if(pid.integral!=0 && sgn(error) != sgn(pid.integral))
		pid.integral = error;
	else
		pid.integral += error;

	if(pid.maxIntegral != -1 && abs(pid.integral) > pid.maxIntegral)
		pid.integral = sgn(pid.integral) * pid.maxIntegral;
	float iTerm = pid.Ki * pid.integral;
	float dTerm = pid.Kd * (position - pid.prevPosition);
	pid.prevPosition = position;

	return pTerm + iTerm - dTerm;
}
