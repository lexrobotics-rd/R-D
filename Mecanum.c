#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     motorFrontLeft, tmotorTetrix, PIDControl)
#pragma config(Motor,  mtr_S1_C1_2,     motorBackLeft, tmotorTetrix, PIDControl)
#pragma config(Motor,  mtr_S1_C2_1,     motorBackRight, tmotorTetrix, PIDControl, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     motorFrontRight, tmotorTetrix, PIDControl, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
Mecanum.c
A basic testfile for Mecanum stuff. Hopefully to be used on Wednesday 11/12, if the axles come in.

LastUpdatedOn: 12/3
LastUpdatedBy: DaveyWavey
*/


/*
MOUNTING THE WHEELS:
-----Critically, the rollers must be parallel to the slashes in the diagram.-----
-----Or maybe not so critically??-----
[\\]   [fwd]    [//]
[\\]            [//]
[\\]            [//]

[left]       [right]

[//]            [\\]
[//]            [\\]
[//]   [back]   [\\]
*/



#include "JoystickDriver.c"

float normalize10(float x){
	if(abs(x) < 10) return 0;
	else return x;
}

task main(){
  //Normalize it so it'll never go out of range of the motor and thus mess up the movement. [MAY MAKE IT SLOWISH]
  //  Joystick values are from -128 to 128, and there are three that can add up together, so divide by 3 to normalize.
  //  Motor values are from -100 to 100.
  float factor = 100.0 / 128.0 / 3.0;
  int fwd, side, rot;

  while(1){
    getJoystickSettings(joystick); //Get joystick settings and put them into variable "joystick". (not needed for joybtns I don't think)

    //(Each joystick value is between -128 and 128.)
    //Normalize to make sure drift doesn't happen when joystick values are slightly off.
	fwd = normalize10(joystick.joy1_y1); //Moves forward/backward based on the left-side joystick forward/backward direction.
	side = normalize10(joystick.joy1_x1); //Moves side-to-side based on the left-side joystick sideways direction.
	rot = normalize10(joystick.joy1_x2); //Rotates based on the right-side joystick sideways direction.

    //The magic Mecanum additions and subtractions, derived via lots of diagrams and logic.
    //  Fwd is obvious - all the wheels have to go forward.
    //  Side is because if you spin front wheels in opposite directions, they will move to the side,
    //    and you must spin the back wheels in the opposite opposite directions to move to the same side.
    //  Rotation is similar - to move the front wheels and back wheels to different sides, move them in the same opposite directions.
    //    It's probably quite difficult to quantify with encoders etc. exactly what's going on with rotation, so gyros are good.
    //    Come to think of it quantifying diagonal translation may also be awkward.
	//  The Normalizes are necessary to prevent motor jerking back and forth on small values.
   	motor[motorFrontLeft] = normalize10(factor * (fwd + side - rot));
    motor[motorFrontRight] = normalize10(factor * (fwd - side + rot));
    motor[motorBackLeft] = normalize10(factor * (fwd - side - rot));
   	motor[motorBackRight] = normalize10(factor * (fwd + side + rot));
  }
}
