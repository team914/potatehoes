#pragma config(UART_Usage, UART1, uartVEXLCD, baudRate19200, IOPins, None, None)
#pragma config(UART_Usage, UART2, uartNotUsed, baudRate4800, IOPins, None, None)
#pragma config(Motor,  port1,           frontLeft,     tmotorVex393HighSpeed_HBridge, openLoop)
#pragma config(Motor,  port2,           rearLeft,      tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port3,           rearRight,     tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port4,           frontRight,    tmotorVex393HighSpeed_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
* Radian to Holonomic Output Testing Code
*
* Licensend under the Lesser General Public License v3.0. http://goo.gl/fB9rz (c) 2013
*      Author: Elliot Berman
*/

// In order for the trigonometry functions to work correctly, all drivetrain motors
// should have a +PWM value corresponding to a clockwise rotation on the wheel.

#include "HolonomicRadians.h";

typedef enum {
	left = 1,
	center = 2,
	right = 4
} cLCDButtons;

task main()
{
	// Option 1: Full Joystick Control
	displayLCDCenteredString(0,"Testing Holonomic");
	displayLCDCenteredString(1,"loading...");
	wait1Msec(500);
	bLCDBacklight = true;
	if(nVexRCReceiveState & vrXmit1)
		// Jumper clip is plugged into digital port 1, and there is currenty a joystick connected
	{
		PolarJoystick joystick;
		displayLCDCenteredString(0,"Using Joystick");
		while(true)
		{
			clearLCDLine(1);
			getPolarJoy(&joystick.radians, &joystick.speed);
			HolonomicRadianOutput(joystick.radians, joystick.speed, vexRT[Ch4]);
			writeDebugStreamLine("r: %f , s: %f",joystick.radians,  joystick.speed);
			wait1Msec(10);
		}
	}
	//End of Option 1

	else // Jumper clip not plugged in and/or joystick is not connected
	{
		//Option 2: Use LCD Screen or Ch8 joystick buttons to cycle through all multiples of PI/4 for [0,2PI)
		bool leftLCDPressed = false;
		bool rightLCDPressed = false;
		bool leftJoyPressed = false;
		bool rightJoyPressed = false;
		bool centerLCDPressed = false;
		bool downJoyPressed = false;
		bool killSwitch = false;
		int radianMultiplier = 0;
		bLCDBacklight = true;
		while(true)
		{
			// Check the left LCD Button for changes
			if(nLCDButtons == left && !leftLCDPressed)
			{
				radianMultiplier--;
				leftLCDPressed = true;
			}
			else if(nLCDButtons != left) leftLCDPressed = false;

			// Check the right LCD button for changes
			if(nLCDButtons == right && !rightLCDPressed)
			{
				radianMultiplier++;
				rightLCDPressed = true;
			}
			else if(nLCDButtons != right) rightLCDPressed = false;

			// Check the left Ch 8 button for changes
			if(vexRT[Btn8L] && !leftJoyPressed)
			{
				radianMultiplier--;
				leftJoyPressed = true;
			}
			else if(!vexRT[Btn8L]) leftJoyPressed = false;

			// Check the right Ch 8 button for changes
			if((vexRT[Btn8R]) && !rightJoyPressed)
			{
				radianMultiplier++;
				rightJoyPressed = true;
			}
			else if(!vexRT[Btn8R]) rightJoyPressed = false;

			// Check the center LCD button for changes
			if(nLCDButtons == center && centerLCDPressed == false) {
				killSwitch = killSwitch ? false : true;
				centerLCDPressed = true;
			}
			else if(nLCDButtons != center) centerLCDPressed = false;

			// Check the right Ch8 Button for changes
			if(vexRT[Btn8D] && !downJoyPressed)
			{
				killSwitch = killSwitch ? false : true;
				downJoyPressed = true;
			}
			else if(!vexRT[Btn8D]) downJoyPressed = false;

			// We want the values to cycle, so when we go beyond bounds, go to the start of the opposite bound
			if(radianMultiplier > 7) radianMultiplier = 0;
			if(radianMultiplier < 0) radianMultiplier = 7;


			displayLCDCenteredString(0,"Cycling RadPI/4");
			switch(radianMultiplier)
			{
			case 0: displayLCDCenteredString(1,"Direction: 0"); 	 	break;
			case 1: displayLCDCenteredString(1,"Direction: PI/4"); 	break;
			case 2: displayLCDCenteredString(1,"Direction: PI/2"); 	break;
			case 3: displayLCDCenteredString(1,"Direction: 3PI/4"); break;
			case 4: displayLCDCenteredString(1,"Direction: PI"); 		break;
			case 5: displayLCDCenteredString(1,"Direction: 5PI/4"); break;
			case 6: displayLCDCenteredString(1,"Direction: 3PI/2"); break;
			case 7: displayLCDCenteredString(1,"Direction: 7PI/4"); break;
			default: displayLCDCenteredString(1,"ERROR");
			}
			if(!killSwitch) HolonomicRadianOutput(((float)radianMultiplier*(PI/4)),1,0); // the last 1,0 is optional, as it is defaulted to those vals
			else if(killSwitch)
			{
				motor[frontLeft] = 0;
				motor[frontRight] = 0;
				motor[rearRight] = 0;
				motor[rearLeft] = 0;
			}
		}
	}
	// End of Option 1


	// Debugging Option 3: Runs the "traditional" holonomic code (no trig function). Should be used for determining hardware vs software issues
	/*
	while(true) {
	motor[rearRight] = vexRT[Ch2] - vexRT[Ch4] - vexRT[Ch1];
	motor[frontRight] = vexRT[Ch2] - vexRT[Ch4] + vexRT[ch1];
	motor[frontLeft] = -vexRT[Ch2] + vexRT[Ch4] - vexRT[Ch1];
	motor[rearLeft] = -vexRT[Ch2] + vexRT[Ch4] + vexRT[Ch1];
	}
	*/
}
