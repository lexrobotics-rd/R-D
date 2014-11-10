/*
Nonviolence.h
"Together, we CAN stop motor abuse."
A function to alleviate instant, jerky velocity changes in motors, instead gradually accelerating them to speed.

LastUpdatedOn: 10-29-14
LastUpdatedBy: Clive
Status: Major edits - modes and struct - untested.

Todo next possibly:
Generalize for anything - smoothly move from point A to point B. Maybe callbacks - LOLZ ROBOTC DOESN'T SUPPORT THEM. Maybe reference variables.
Does this integrate nicely? Is the distance consistent? Is there a way to apply this to encoder counts rather than speeds? (test it with encoders!)
*/


/* HOW TO USE IT
Beginning of program:
	startTask(nonviolenceTask);

When moving: (instead of motor[motorsLeft] = 100;)
	nonviolence(motorsLeft, 100);//Default (NV_DEFAULT_MODE) is (at the time of this writing) NV_MODE_LINEAR.
	nonviolence(motorsLeft, 100, NV_MODE_STEP); //Steps it directly to the target speed, with total violence. Just like motor[motorsLeft] = 100;.
	nonviolence(motorsLeft, 100, NV_MODE_LINEAR); //Linearly ramps it up/down to the target speed.
	nonviolence(motorsLeft, 100, NV_MODE_LOGISTIC); //Logistically ramps it up/down to the target speed.

Note that this uses a task. The NXT is (apparently) limited to 5 tasks, so be careful of this limit!
Note also that the NXT is not actually thread-safe, even though it has multiple "threads" running "concurrently."
This also has a ton of global constants, all prefixed with NV_.
This also contains a function, and if you ever run up against the ROBOTC 256-function limit... what are you even doing?
*/


// STUFF YOU MIGHT WANT TO DEFINE
//Must both be positive.
const int NV_tick = 10; //Milliseconds per clocktick of the Nonviolence task.
const int NV_acc = 3; //How much to increase/decrease the motor per NV_tick milliseconds. Serves as maximum acceleration for nonlinear modes.

// STUFF YOU SHOULDN'T TOUCH
//# of motors
const int numMotors = kNumbOfTotalMotors;

//Constants for nonviolence modes.
const int NV_MODE_STEP = 0;
const int NV_MODE_LINEAR = 1;
const int NV_MODE_LOGISTIC = 2; //Logistic! Read about it on Wikipedia.
const int NV_DEFAULT_MODE = NV_MODE_LINEAR;

//Logistic "close enough we'll just pretend it's zero"
const int NV_LOGISTIC_CLOSEENOUGH = 2;

//Motor Properties variable structure
typedef struct{
	signed int motor; //motor number ("motorsLeft" and "motorsRight" are actually stored as integers)
	signed int initial; //Initial speed
	signed int target; //Target speed
	signed int mode; //Mode - see above
	bool active;
}NV_motorproperties;

/*
The "NV" Motor Queue
This queue will store the motors being acted upon. Doesn't do anything until you start calling nonviolence().
When you call nonviolence(), it adds a motor to that queue, with all the properties of the path it will follow. (motornumber, initial position, target, path mode)
Next time you call nonviolence(), that motor is already in the queue, so it'll just be modified.
When nonviolenceTask runs (once every NV_tick milliseconds), it will look at all the "active" motors in the queue and increment them along their journey.

Why do we need it? To support multiple motors running at once.
Also, because there is no way to access the list of motor numbers currently available, so they must be added on sight.
Mainly, because ROBOTC is really annoying.
*/
NV_motorproperties NV[numMotors]; //declares array of motors (called "NV") of NV_motorproperties's.

void nonviolence(tMotor newInputMotor, int target, int mode = NV_DEFAULT_MODE){
	//Make sure we're not doing weird stuff with over-100 values.
	target = min(target, 100);
	target = max(target, -100);
	
	for(int i = 0; i < numMotors; i++)
		if(NV[i]->motor == newInputMotor || NV[i]->active == false){ //Unnecessarily initializes some motors. But it works perfectly well.
			NV[i]->motor = newInputMotor;
			NV[i]->initial = motor[newInputMotor];
			NV[i]->target = target;
			NV[i]->mode = mode;
			NV[i]->active = true;
			break;
		}
}

task nonviolenceTask{
	for(int i = 0; i < numMotors; i++) //Initializes Nonviolence motor array
		NV[i]->active = false; //By default, none of the queued motors are active.
	
	while(true){
		for(int i = 0; i < numMotors; i++){//Check on all the motors, inc if necessary.
			if(!NV[i]->active) continue; //This queued motor isn't active. Skip.
			
			float initVal = NV[i]->initial;
			float currVal = motor[NV[i]->motor];
			float target = NV[i]->target;
			
			switch(NV[i]->mode){ //Figure out what mode is being used.
				case NV_MODE_STEP: //Go directly to target.
					motor[NV[i]->motor] = NV[i]->target;
					NV[i]->active = false;
					break;
				case NV_MODE_LINEAR: //Goes directly toward target, at acceleration of NV_acc.
					if(abs(target - currVal) <= NV_acc){ //If it's so close who cares?
						motor[NV[i]->motor] = target; //Just set it to the target.
						NV[i]->active = false;
					}
					else{ //If we're appreciably above/below the target
						motor[NV[i]->motor] += NV_acc * ((currVal < target)?1:-1); //Increase/decrease the speed of the motor by NV_acc.
					}
					break;
				case NV_MODE_LOGISTIC: //Goes in a logistic curve (slow first, faster in middle, slow down as reaching it)
					if(abs(currVal - initVal) < NV_LOGISTIC_CLOSEENOUGH){//Get it off the ground, since the logistic formula will return zero if we start at zero.
						motor[NV[i]->motor] = currVal + NV_LOGISTIC_CLOSEENOUGH * ((currVal > initVal)?1:-1);
					}
					else if(abs(target - currVal) < NV_LOGISTIC_CLOSEENOUGH){//If it's close to endpoint, let's stop.
						motor[NV[i]->motor] = target;
						NV[i]->active = false;
					}
					else{ //Differential equation: dy/dx = maxSpeed(diff_from_end)(diff_from_beginning)/(end - start)
						float change = (currVal - initVal) * (target - currVal) / (target - initVal);
						change *= NV_acc * (target - initVal) / 4; //Normalize it so that the highest accel (in the very middle) is exactly NV_acc
						motor[NV[i]->motor] += change;
					}//Could this result in oscillation, with high enough acc and proper conditions??
					break;
				default:
					NV[i]->mode = NV_DEFAULT_MODE; //Set it to default and wait until next time to do anything.
					break;
			}
		}//end for loop
		wait1Msec(NV_tick);
	}//end while loop
}
