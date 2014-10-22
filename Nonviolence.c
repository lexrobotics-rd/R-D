/*
Nonviolence.c
"Together, we CAN stop motor abuse."
A function to alleviate instant, jerky velocity changes in motors, instead gradually accelerating them to speed.

LastUpdatedOn: 10-20-14
LastUpdatedBy: Nathaniel+Clive
Status: Reviewed and compiled. But who knows what'll happen when it runs?
*/


/* HOW TO USE IT
Beginning of program:
	startTask(nonviolence_task);

When moving:
	nonviolence(motorsLeft, 100);
(instead of motor[motorsLeft] = 100;)

Note that this uses a task. The NXT is (evidently) limited to 5 tasks, so be careful of this limit!
Note also that the NXT is not thread-safe, even though it has multiple "threads" running "concurrently."
*/


// STUFF YOU MIGHT WANT TO DEFINE
const int NV_trans = 500; //Imagine it's like a CSS transition, except with motor velocity. Milliseconds.
const int NV_wait = 50;//Milliseconds, how long to wait between adjustments. High = faster NXT program but choppier.


// STUFF YOU SHOULDN'T TOUCH
const float NV_incfactor = ((float)NV_wait) / ((float)NV_trans); //the constant increment used to scale acceleration.
typedef short motorType;
const int numMotors = kNumbOfTotalMotors;

bool NV_mode_nonviolent = true;

motorType NV_mtrs[numMotors];  //declares array of motor numbers ("motorsLeft" and "motorsRight" are actually stored as integers)
int NV_targets[numMotors]; //declares array of target speeds for each motor
int NV_incs[numMotors];  //declares array of speed increments for each motor

void nonviolence(motorType newInputMotor, int target){	//this function is called in order to add a motor to the next
	for(int i = 0; i < numMotors; i++){ 										//available slot in the nonviolenceTask process queue
		if(newInputMotor == NV_mtrs[i] || NV_mtrs[i] == -1){
			NV_mtrs[i] = newInputMotor;
			NV_targets[i] = target;
			NV_incs[i] = (target - motor[newInputMotor]) * NV_incfactor;
			break;
		}
	}
}

void nonviolenceMode(string s){
	if(s=="gandhi")NV_mode_nonviolent = true;
	else if(s=="hannibal")NV_mode_nonviolent = false;
}

task nonviolenceTask{
	for(int i = 0; i < numMotors; i++){ //--------Initializes Nonviolence data arrays-------//
		NV_mtrs[i] = -1;//Sentinel for the NV_mtrs[] array. Considered an empty value.
		NV_targets[i] = 0;//Target will be set by nonviolence() anyway.
		NV_incs[i] = 0;//Inc will also be set by nonviolence().
	}

	float diff;
	while(true){
		for(int i = 0; i < numMotors; i++){//Check on all the motors, inc if necessary.
			if(NV_mtrs[i] == -1) break; //Ok, we've reached the sentinel -- all the remaining empty spots are filled with -1s too

			if(!NV_mode_nonviolent) motor[NV_mtrs[i]] = NV_targets[i]; //If we've set nonviolent mode to off, just set the motor directly.

			diff = NV_targets[i] - motor[NV_mtrs[i]];
			if(abs(diff) < abs(NV_incs[i]))
				motor[NV_mtrs[i]] = NV_targets[i]; //Done if the difference is less than inc (abs because targets may be less than current)
			else
				motor[NV_mtrs[i]] += NV_incs[i]; //Otherwise, change the speed of the motor by the set increment.
		}//end for loop
		wait1Msec(NV_wait);
	}//end while loop
}
