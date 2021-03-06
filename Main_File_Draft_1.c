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


//Date Modified: 27 October 2016


/*
This file is the fourth draft of the Starstruck RVW Online Challenge.
NOTE: When using time, it is already converted to seconds instead of milliseconds.
See files included for more information.
NOTE: When using degrees, it is already converted to actual degrees instead
of degrees*10. See "Base.c" for more information.
*/


#include "Arm.c" //This includes all of the functions that involve the arm
#include "Base.c" //This includes all of the functions that involve the base
#include "Claw.c" //This includes all of the functions that involve the claw
#include "Extension.c" //This includes all of the functions that involve the extension
#include "Wrist.c" //This inclues all of the functions that involve the extension
#include "Multiple_Parts.c" //This includes all functions that involve multiple subsystems


/*
This program is organized by points and actions oriented with
stars and cubes. Each section scores points and completes
actions in some way, shape, or form. See the far right of the
screen for details of actions and points scored (theoretically,
of course). Keep in mind that all of this is subject to change
and may not work when tried out on robot virtual worlds.
NOTE: When the comments say things like "top left corner"
look down at the field from side robot is starting on.
*/


task main()
{
	stopAtLine(127); //Move to line
	moveBaseAndClaw(-127, -127, openclaw, 0.7); //Drop star and go backwards                                                                                                                                                                                                                                                                                                                                                                                                                                             DROP STAR
	turnLeftWithGyro(127, -85); //Face star in bottom left corner
	moveBaseForTime(127, 127, 0.58); //Move to star
	moveBaseAndClaw(-127, -127, closeclaw, 0.58); //Grab star and move back to starting position                                                                                                                                                                                                                                                                              GRAB STAR
	turnLeftWithGyro(127, -179); //Face away from wall
	moveBaseForTime(-126, -127, 2.65); //Move back to wall and push star under wall                                                                                                                                                                                                                                                                                                                                                                                                      SCORE STAR
	moveArmForRotationsUp(127, 800); //Move arm up and knock stars off of wall                                                                                                                                                                                                                                                                                                                                                                                                                           SCORE STARS
	moveBaseArmAndClaw(127, 127, -127, openclaw, 0.5); //Reset arm and drop star and move away from wall                                                                                                                                                                                                                        SCORE STAR
	moveArmForRotationsDown(127, 2); //Finish resetting arm

	turnRightWithGyro(127, -98); //Face star in top left corner
	moveBaseForTime(127, 127, 1); //Move to star
	moveClawForTime(closeclaw); //Grab star                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                GRAB STAR
	turnLeftWithGyro(127, -195); //Face away from wall
	moveBaseAndArm(-127, -127, 127, 0.5); //Move back towards wall and raise arm
	moveArmForRotationsUp(127, 800); //Finish raising arm and knock star over fence                                                                                                                                                                                                                                                                                                                                                                                                      SCORE STAR
	moveBaseArmAndClaw(127, 127, -127, openclaw, 1); //Reset arm drop star and move away from wall                                                                                                                                                                                                                                                                 SCORE STAR
	moveArmForRotationsDown(127, 2); //Finish resetting arm

	turnLeftWithGyro(127, -250); //Face cube in the middle of the field
	moveBaseForTime(127, 127, 2); //Move to cube
	moveBaseAndClaw(127, 127, closeclaw, 1); //Grab cube and move backwards                                                                                                                                                                                                                                                                                                                                                                                                                                                           GRAB CUBE
	turnRightWithGyro(127, -180); //Face away from wall
	moveBaseForTime(127, 127, 0.3); //Move away from wall
	moveArmForRotationsUp(127, 800); //Move arm up
	moveBaseAndExtension(-114, -115, 60, 1.8); //Move backwards while moving extension up and knock off stars                                                                                                                                                                                         SCORE STARS
	moveBaseArmAndClaw(127, 127, -127, openclaw, 0.5); //Reset arm drop cube and move away from wall                                                                                                                                                                                                                                                  SCORE CUBE
	moveBaseAndExtension(99, 101, -100, 1.8); //Move away from wall and reset extension
	moveArmForRotationsDown(127, 2); //Finish resetting arm

	turnLeftWithGyro(127, -240); //Turn to face cube in other starting tile
	moveBaseForTime(127, 127, 1); //Move to cube
	moveBaseAndClaw(-127, -127, closeclaw, 1.5); //Grab cube and move backwards                                                                                                                                                                                                                                                                                                                                                                                                                       GRAB CUBE
	turnRightWithGyro(127, -145); //Turn to face away from wall
	moveBaseForTime(-127, -115, 2.3); //Move to wall
	moveArmForRotationsUp(127, 800); //Move arm up and knock stars off of wall                                                                                                                                                                                                                                                                                                                                                                                                                           SCORE STARS
	moveBaseArmAndClaw(127, 127, -127, openclaw, 1); //Reset arm drop cube and move away from wall                                                                                                                                                                                                                                                                 SCORE CUBE
	moveArmForRotationsDown(127, 1); //Finish resetting arm

	turnLeftWithGyro(127, -238); //Turn to face star in bottom right corner
	moveBaseForTime(127, 127, 2.5); //Move to star
	moveBaseAndClaw(20, -100, closeclaw, 1.2); //Grab star and turn to face away from wall                                                                                                                                                                                                                                                                                                                                   GRAB STAR
	turnRightWithGyro(127, -180); //Finish turning from previous step
	moveBaseForTime(-127, -127, 2.2); //Move back to wall and push star under wall                                                                                                                                                                                                                                                                                                                                                                                         SCORE STAR
	moveArmForRotationsUp(127, 800); //Move arm up and knock off star                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      SCORE STAR
	moveBaseArmAndClaw(127, 127, -127, openclaw, 1); //Reset arm drop star and move away from wall                                                                                                                                                                                                                                                                 SCORE STAR
	moveArmForRotationsDown(127, 1); //Finish resetting arm
}
