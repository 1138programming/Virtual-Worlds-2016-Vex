#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    leftLight,      sensorLineFollower)
#pragma config(Sensor, in2,    middleLight,    sensorLineFollower)
#pragma config(Sensor, in3,    rightLight,     sensorLineFollower)
#pragma config(Sensor, in4,    wristPot,       sensorPotentiometer)
#pragma config(Sensor, in6,    gyro,           sensorGyro)
#pragma config(Sensor, dgtl7,  touchSensor,    sensorTouch)
#pragma config(Sensor, dgtl8,  sonarSensor,    sensorSONAR_cm)
#pragma config(Sensor, I2C_1,  rightEncoder,   sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  leftEncoder,    sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_3,  armEncoder,     sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_4,  extensionEncoder, sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_5,  wristEncoder,   sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           frontRightMotor, tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           rearRightMotor, tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port3,           frontLeftMotor, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           rearLeftMotor, tmotorVex393_MC29, openLoop, encoderPort, I2C_2)
#pragma config(Motor,  port6,           clawMotor,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           armMotor,      tmotorVex393_MC29, openLoop, encoderPort, I2C_3)
#pragma config(Motor,  port8,           leftExtendMotor, tmotorVex393_MC29, openLoop, encoderPort, I2C_4)
#pragma config(Motor,  port9,           rightExtendMotor, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          wristMotor,    tmotorVex393_HBridge, openLoop, encoderPort, I2C_5)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


//Date Modified: 26 October 2016


/*
This code is included in all of the files starting with "Main_File_Draft_..."
It consists of all of the functions for the base that are needed to run
the fantasticbot properly. These functions are (in order):
- moveBaseForTime
- moveBaseForwardForDistance
- moveBaseBackwardForDistance
- followLineForDistance
- stopAtLine
- turnRightWithGyro
- turnLeftWithGyro
- approachObjectWithUltrasound
NOTE: Any function that has to do with encoders (has "Distance" in the name)
is currently under maintenance. The encoder values currently do not reset properly.
NOTE: Any function that has to do with the gyro (has "Gyro" in the name)
is currently under maintenance. The gyro will not reset properly (still used in main code).
TODO: Figure out how to reset the encoders
*/


int fullspeed = 127; //Used to make a motor go at full speed forwards
int negativefullspeed = -127; //Used to make a motor go at full speed backwards
int halfspeed = 63; //Used to make a motor go at half speed forwards
int negativehalfspeed = -63; //Used to make a motor go at half speed backwards


//This function moves the base at a certain speed for a certain ammount of time, and then comes to a stop --------------------------------------
void moveBaseForTime(int leftpower, int rightpower, float time) //Power to left side of base, power to right side of base, time base moves
{
	motor[frontRightMotor] = rightpower;
	motor[frontLeftMotor] = leftpower;
	motor[rearLeftMotor] = leftpower;
	motor[rearRightMotor] = rightpower; //Move the base at a certain power
	wait1Msec(time*1000); //Keep moving until time is up
	motor[frontRightMotor] = 0;
	motor[frontLeftMotor] = 0;
	motor[rearLeftMotor] = 0;
	motor[rearRightMotor] = 0; //Stop the base
}


//This function moves the base forwards until the encoders on the base reach a certain ammount, and then comes to a stop -----------------------
void moveBaseForwardForDistance(int power, int distance) //Power to base, distance going forwards with encoders
{
	SensorValue[leftEncoder] = 0;
	SensorValue[rightEncoder] = 0; //Reset the encoder values on the base
	while(SensorValue[leftEncoder] < distance || SensorValue[rightEncoder] > -distance) //While the encoders have not reached a certain value
	{
		motor[frontLeftMotor] = power;
		motor[frontRightMotor] = power;
		motor[rearLeftMotor] = power;
		motor[rearRightMotor] = power; //Move the base at a certain speed
	}
	motor[frontLeftMotor] = 0;
	motor[frontRightMotor] = 0;
	motor[rearLeftMotor] = 0;
	motor[rearRightMotor] = 0; //Stop the base
}


//This function moves the base backwards until the encoders on the base reach a certain ammount, and then comes to a stop ----------------------
void moveBaseBackwardForDistance(int powerreversed, int negativedistance) //Power going to the base reversed, distance going backwards with encoders
{
	SensorValue[leftEncoder] = 0;
	SensorValue[rightEncoder] = 0; //Reset the encoder values on the base
	while(SensorValue[leftEncoder] > -negativedistance || SensorValue[rightEncoder] < negativedistance) //While the encoders have not reached a certain value
	{
		motor[frontLeftMotor] = -powerreversed;
		motor[frontRightMotor] = -powerreversed;
		motor[rearLeftMotor] = -powerreversed;
		motor[rearRightMotor] = -powerreversed; //Move the base at a certain speed
	}
	motor[frontLeftMotor] = 0;
	motor[frontRightMotor] = 0;
	motor[rearLeftMotor] = 0;
	motor[rearRightMotor] = 0; //Stop the base
}


//This function follows a line for a certain distance using the line followers, then comes to a complete stop ----------------------------------
void followLineForDistance(int speedwhencorrect, int linedistance) //Speed moving forward when following line, distance following line
{
	SensorValue[leftEncoder] = 0;
	SensorValue[rightEncoder] = 0; //Reset the encoder values on the base
	while(SensorValue[leftEncoder] < linedistance || SensorValue[rightEncoder] > -linedistance) //While the encoders have not reached a certain value
	{
		if(SensorValue[leftLight] > 500 && SensorValue[middleLight] > 500 && SensorValue[rightLight] < 500) //If tracking to the left
		{
			motor[frontLeftMotor] = 60;
			motor[frontRightMotor] = -40;
			motor[rearLeftMotor] = 60;
			motor[rearRightMotor] = -40; //Self-right to follow the line
		}
		else if(SensorValue[leftLight] < 500 && SensorValue[middleLight] > 500 && SensorValue[rightLight] > 500) //If tracking to the right
		{
			motor[frontLeftMotor] = -40;
			motor[frontRightMotor] = 60;
			motor[rearLeftMotor] = -40;
			motor[rearRightMotor] = 60; //Self-right to follow the line
		}
		else //If going forward perfectly and not tracking left or right
		{
			motor[frontLeftMotor] = speedwhencorrect;
			motor[frontRightMotor] = speedwhencorrect;
			motor[rearLeftMotor] = speedwhencorrect;
			motor[rearRightMotor] = speedwhencorrect; //Move forward at speed desired
		}
	}
	motor[frontLeftMotor] = 0;
	motor[frontRightMotor] = 0;
	motor[rearLeftMotor] = 0;
	motor[rearRightMotor] = 0; //Stop the base
}


//This function moves the base until the line on the field is sensed, then comes to a complete stop --------------------------------------------
void stopAtLine(int speed) //Speed of the base when approaching the line
{
	while(SensorValue[leftLight] > 500 || SensorValue[rightLight] > 500 || SensorValue[middleLight] > 500) //While line is not sensed
	{
		motor[frontLeftMotor] = speed;
		motor[frontRightMotor] = speed;
		motor[rearLeftMotor] = speed;
		motor[rearRightMotor] = speed; //Move the base at a certain value
	}
	motor[frontLeftMotor] = 0;
	motor[frontRightMotor] = 0;
	motor[rearLeftMotor] = 0;
	motor[rearRightMotor] = 0; //Stop the base
}


//This function makes a precise right turn using a value in the gyroscope ----------------------------------------------------------------------
void turnRightWithGyro(int speed, int turnradius) //Speed of the base when turning right, amount of turn
{
	SensorValue[gyro] = 0; //Reset the value of the gyro
	while(SensorValue[gyro] < turnradius*10) //While the gyro is not at the certain desired angle
	{
		motor[frontLeftMotor] = speed;
		motor[frontRightMotor] = -speed;
		motor[rearLeftMotor] = speed;
		motor[rearRightMotor] = -speed; //Turn right at a certain speed
	}
	motor[frontLeftMotor] = 0;
	motor[frontRightMotor] = 0;
	motor[rearLeftMotor] = 0;
	motor[rearRightMotor] = 0; //Stop the base
}


//This function makes a precise left turn using a value in the gyroscope -----------------------------------------------------------------------
void turnLeftWithGyro(int speedreversed, int turnradiusreversed) //Speed of the base when turning left, amount of turn
{
	SensorValue[gyro] = 0; //Reset the value of the gyro
	while(SensorValue[gyro] > turnradiusreversed*10) //While the gyro is not at the certain desired angle
	{
		motor[frontLeftMotor] = -speedreversed;
		motor[frontRightMotor] = speedreversed;
		motor[rearLeftMotor] = -speedreversed;
		motor[rearRightMotor] = speedreversed; //Turn left at a certain speed
	}
	motor[frontLeftMotor] = 0;
	motor[frontRightMotor] = 0;
	motor[rearLeftMotor] = 0;
	motor[rearRightMotor] = 0; //Stop the base
}


//This function approaches an object until a certain value on the ultrasound is reached --------------------------------------------------------
void approachObjectWithUltrasound(int speedapproaching, int distanceaway) //Speed of approaching the object, distance from object to stop at
{
	while(SensorValue[sonarSensor] > distanceaway) //While sonar is not reading desired value
	{
		motor[frontLeftMotor] = speedapproaching;
		motor[frontRightMotor] = speedapproaching;
		motor[rearLeftMotor] = speedapproaching;
		motor[rearRightMotor] = speedapproaching; //Move at a certain speed
	}
}
