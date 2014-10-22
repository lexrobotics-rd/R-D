

#include "Nonviolence.c"

task main(){
	motor[motorA] = 0;
	wait10Msec(100);
	motor[motorA] = 100;
	wait10Msec(100);
	motor[motorA] = 0;
	wait10Msec(100);

	startTask(nonviolenceTask);

	nonviolence(motorA,100);
	wait10Msec(100);
	nonviolence(motorA,0);
	wait10Msec(100);

	nonviolenceMode("hannibal");

	nonviolence(motorA,100);
	wait10Msec(100);
	nonviolence(motorA,0);
	wait10Msec(100);
}
