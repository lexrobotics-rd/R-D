#pragma config(Hubs,  S1, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Servo,  srvo_S1_C1_1,    winch1,               tServoStandard)
#pragma config(Servo,  srvo_S1_C1_2,    winch2,               tServoStandard)
#pragma config(Servo,  srvo_S1_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main(){
	servo[winch1] = 100000; //Sensor port 1, controller 1, port 1

	servo[winch2] = -100000; //Sensor port 1, controller 1, port 2

	//yay it's continuous apparently?
	//very negative values to turn in negative direction (CCW looking down)
	//very positive is CW looking down onto

	for(;;);
}
