/*
Mecanum.c
A basic testfile for Mecanum stuff. Hopefully to be used on Wednesday 11/12, if the axles come in.

LastUpdatedOn: 11/12 [like 12AM what am I doing]
LastUpdatedBy: Clive
*/


/*
MOUNTING THE WHEELS:
-----Critically, the rollers must be parallel to the slashes in the diagram.-----
[//]   [fwd]    [\\]
[//]            [\\]
[//]            [\\]
                    
[left]       [right]
                    
[\\]            [//]
[\\]            [//]
[\\]   [back]   [//]
*/



#include "JoystickDriver.c"

task main(){
  //Normalize it so it'll never go out of range of the motor and thus mess up the movement. [MAY MAKE IT SLOWISH]
  //  Joystick values are from -128 to 128, and there are three that can add up together.
  //  Motor values are from -100 to 100.
  float factor = 100.0 / 128.0 / 3.0;
  int fwd, side, rot;
  
  while(1){
    getJoystickSettings(joystick); //Get joystick settings and put them into variable "joystick". (not needed for joybtns I don't think)
    
    //Each between -128 and 128.
    fwd = joystick.joy1_y1; //Moves forward/backward based on the left-side joystick forward/backward direction.
    side = joystick.joy1_x1; //Moves side-to-side based on the left-side joystick sideways direction.
    //rot = joystick.joy1_x2; //Rotates based on the right-side joystick sideways direction.
    rot = 0; //Test with just translational motion first! Then replace this with the above line.
    
    //Make sure drift is not allowed
    if(abs(fwd) < 10) fwd = 0;
    if(abs(side) < 10) side = 0;
    if(abs(rot) < 10) rot = 0;
    
    //The magic Mecanum additions and subtractions, derived via lots of diagrams and logic.
    //  Fwd is obvious - all the wheels have to go forward.
    //  Side is because if you spin front wheels in opposite directions, they will move to the side,
    //    and you must spin the back wheels in the opposite opposite directions to move to the same side.
    //  Rotation is similar - to move the front wheels and back wheels to different sides, move them in the same opposite directions.
    //    It's probably quite difficult to quantify with encoders etc. exactly what's going on with rotation, so gyros are good.
    //    Come to think of it quantifying diagonal translation may also be awkward.
    motor[motorFrontLeft] = factor * (fwd + side + rot);
    motor[motorFrontRight] = factor * (fwd - side - rot);
    motor[motorBackLeft] = factor * (fwd - side - rot);
    motor[motorBackRight] = factor * (fwd + side + rot);
  }
}
