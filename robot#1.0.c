#pragma config(Sensor, in1,    liftRight,      sensorPotentiometer)
#pragma config(Sensor, in2,    liftLeft,       sensorPotentiometer)
#pragma config(Sensor, in3,    flipPotent,     sensorPotentiometer)
#pragma config(Sensor, in4,    ballIntake,     sensorLineFollower)
#pragma config(Sensor, dgtl1,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  rightEncoder,   sensorQuadEncoder)
#pragma config(Motor,  port1,           lift,        tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           intake,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           right3,        tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port4,           right2,        tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port5,           right1,        tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port6,           left1,         tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port7,           left2,         tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port8,           left3,         tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port9,           puncher,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          flipper,       tmotorVex393HighSpeed_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)

// SmartMotorLibrary
#include "jpearman/SmartMotorLib.c"

//auton vars
//Left
float  pid_Kp = 0.7;
float  pid_Ki = 0.09;
float  pid_Kd = 0.9;

//Right
float  pd_Kp = 1.1;
float  pd_Ki = 0.02;
float  pd_Kd = 0.5;

/*
float  pid_Lift_Kp = 2;
float  pid_Lift_Ki = 0.04;
float  pid_Lift_Kd = 0.5;
*/

// Other files
#include "functions.c"
#include "leftPID.c"

#include "Vex_Competition_Includes.c"  // Main competition background code...do not modify!
#pragma systemFile

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

// Main competition background code...do not modify!

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton()
{
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks
	// running between Autonomous and Driver controlled modes. You will need to
	// manage all user created tasks if set to false.
	bStopTasksBetweenModes = false;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
	// Enable smart motor library
	SmartMotorsInit();

	// Define motors plugged into power expander
	// SmartMotorsAddPowerExtender( motorA, motorB, motorC, motorD );

	// Link motors

	// Drive motors
	SmartMotorLinkMotors(left1,left2);
	SmartMotorLinkMotors(left1,left3);
	SmartMotorLinkMotors(right1,right2);
	SmartMotorLinkMotors(right1,right3);
	// Current monitor
	SmartMotorCurrentMonitorEnable();
	// Smart motor start
	SmartMotorRun();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task autonomous()
{
	//(find in leftPID.c)
	auton();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

// User control code here, inside the loop

// This is the main execution loop for the user control program.
// Each time through the loop your program should update motor + servo
// values based on feedback from the joysticks.

// ........................................................................
// Insert user code here. This is where you use the joystick values to
// update your motors, etc.
// ........................................................................

task usercontrol(){
	bLCDBacklight = true;									// Turn on LCD Backlight

	startTask(lcd);   //(find in leftPID.c)

	resetEncoders();  //(find in functions.c)

	// Drive program
	while(true){
		// drive program (find in functions.c)
		drive();

/*		if( nVexRCReceiveState & 0x02 )
		{
			// second joystick is connected
			// Intake program
			if (vexRT[Btn6UXmtr2]==1){
				motor[intake]=127;
				}else if (vexRT[Btn6DXmtr2]==1){
				motor[intake]=-127;
				} else{
				motor[intake]=0;
			}
			if(vexRT[Btn7UXmtr2]==1){
				auton();
			}
			// Puncher program
			if (vexRT[Btn5UXmtr2]==1){
				motor[puncher1]=127;
				motor[puncher2]=127;
				} else{
				motor[puncher1]=0;
				motor[puncher2]=0;
			}
		}else{
			// Intake program
			if (vexRT[Btn5UXmtr2]==1){
				motor[puncher1]=127;
				motor[puncher2]=127;
				}else{
				motor[puncher1]=0;
				motor[puncher2]=0;
			}
*/

			bool intakeToggle = false;

			//lift program (find in functions.c)
			if(vexRT[Btn5UXmtr2]==1){
				if(intakeToggle==false){
					waitUntil(vexRT[Btn5DXmtr2]==0);
					intakeFunc(127);
					intakeToggle=true;
				} else if(intakeToggle==true){
					waitUntil(vexRT[Btn5DXmtr2]==0);
					intakeFunc(0);
					intakeToggle=false;
				}
			}else if (vexRT[Btn5DXmtr2]==1){
				if(intakeToggle==true){
					waitUntil(vexRT[Btn5UXmtr2]==0);
					intakeFunc(0);
					intakeToggle=false;
					delayFunc(500);
					intakeFunc(127);
					intakeToggle=true;
				}else if(intakeToggle==false){
					waitUntil(vexRT[Btn5UXmtr2]==0);
					intakeToggle=true;
					intakeFunc(-127);
				}
			}else{
				intakeFunc(0);
			}
/*
			//flipper
			if(vexRT[Btn8R]==1){
				flipperFunc(127);
			}else if (vexRT[Btn8L]==1){
				flipperFunc(-127);
			}else{
				flipperFunc(0);
			}
*/
			// Puncher program (find in functions.c)
			if (vexRT[Btn6UXmtr2]==1){
					startTask(puncherOn);
					delayFunc(1000);
					stopTask(puncherOn);
					startTask(puncherOff);
					stopTask(puncherOff);
			}else{
				puncherFunc(0);
			}
/*
			if(vexRT[Btn5U]==1){
				liftFunc(127);
			}else if(vexRT[Btn5D]==1){
				liftFunc(-127);
			} else {
				liftFunc(0);
			}
*/

			//reverse drive so that you can easily flip caps (find in functions.c)
			if(vexRT[Btn8D]==1){
				if(driveReverse==false){
					waitUntil(vexRT[Btn8D]==0);
					driveReverse=true;
					delayFunc(500);
				}else if(driveReverse==true){
					waitUntil(vexRT[Btn8D]==0);
					driveReverse=false;
					delayFunc(500);
				}
			}

			//reverse drive so that you can easily flip caps (find in functions.c)
			if(vexRT[Btn8DXmtr2]==1){
				if(driveReverse==false){
					waitUntil(vexRT[Btn8D]==0);
					driveReverse=true;
					delayFunc(500);
				}
				else if(driveReverse==true){
					waitUntil(vexRT[Btn8D]==0);
					driveReverse=false;
					delayFunc(500);
				}
			}

			//if button pressed run auton (auton is in leftPID.c)
			if(vexRT[Btn7U]==1){
				auton();
			}

			//if button pressed reset Encoders (to find this function look at functions.c)
			if(vexRT[Btn7D]==1){
				resetEncoders();
			}

		delayFunc(20);

	}
}
