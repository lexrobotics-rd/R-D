/*
Nonviolence.c
"Together, we CAN stop motor abuse."
A function to alleviate instant, jerky velocity changes in motors, instead gradually accelerating them to speed.

LastUpdatedOn: 10-15-14
LastUpdatedBy: Clive
Status: it compiles, but who knows what'll happen when it runs?
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
const float NV_incfactor = ((float)NV_wait) / ((float)NV_trans); //What you have to multiply the difference by to get the per-loop increment.
typedef short mtr;
const int numMtrs = kNumbOfTotalMotors;

mtr NV_mtrs[numMtrs];
int NV_targets[numMtrs];
int NV_incs[numMtrs];

void nonviolence(mtr m, int target){
	for(int i=0;i<numMtrs;i++){ //RobotC may not support sizeofs.
		if(m == NV_mtrs[i] || m == -1){
			NV_mtrs[i] = m;
			NV_targets[i] = target;
			NV_incs[i] = (target - motor[m]) * NV_incfactor;
			break;
		}
		//Loops through all of the known motors, and assigns targets and increments as necessary.
	}
}


task nonviolenceTask{
	for(int i=0;i<numMtrs;i++){ //Fill up the array with initial values.
		NV_mtrs[i] = -1; //----------chk that this is indeed an invalid motor number-----------//
		NV_targets[i] = 0;
		NV_incs[i] = 0;
	}

	float diff;
	while(1){
		for(int i=0;i<numMtrs;i++){//Check on all the motors, inc if necessary.
			if(NV_mtrs[i] == -1) break; //Ok, we've reached the end -- all the remaining empty spots are filled with -1s

			diff = NV_targets[i] - motor[NV_mtrs[i]];
			if(abs(diff) < abs(NV_incs[i])){ //Done if the difference is less than inc (abs because targets may be less than current)
				motor[NV_mtrs[i]] = NV_targets[i];
				continue;
			}
			motor[NV_mtrs[i]] += NV_incs[i]; //Otherwise, change the
		}
		wait1Msec(NV_wait);
	}
}
