#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     oneMotorToRuleThemAll, tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
NewMotorsTest.c
Just checkin out if the NeveRest 40 Motors from Andy Mark's website work as expected.
PID ftw?

LastUpdateOn: 10-29-14
LastUpdatedBy: David
Status: nothing to commit, working directory clean
*/

#include "lib\Nonviolence.h"

task main()
{
	startTask(nonviolenceTask);

	nMotorEncoder[oneMotorToRuleThemAll] = 0;

	const int w = 10000;// For some reason if we let the thing ramp all the way up and stay there,
											//and then bring it back down, it sputters on the way down.
	for(int i=100;;i--){//Even this experiences a sputter on the way down!
		motor[oneMotorToRuleThemAll]=i; //All the motor values are correct. It just doesn't actually happen.
		wait1Msec(1000);// The motor spin speed flatlines at ~50 then drops from ~50 to ~20, for unknown reasons
	}

	for(;;);

	playSound(soundBeepBeep);
	nonviolence(oneMotorToRuleThemAll,100);
	wait1Msec(w);
	displayCenteredTextLine(1, "%d", nMotorEncoder[oneMotorToRuleThemAll]);
	playSound(soundBeepBeep);
	nonviolence(oneMotorToRuleThemAll,0);
	wait1Msec(w);
	displayCenteredTextLine(2, "%d", nMotorEncoder[oneMotorToRuleThemAll]);
	playSound(soundBeepBeep);	playSound(soundBeepBeep);

	for(;;);

	stopTask(nonviolenceTask);
}