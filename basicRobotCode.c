#pragma config(Motor,  port1,           left1,         tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           left2,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           right1,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           right2,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           lift1,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           lift2,         tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	//Code written by Michael Jones 6 September 2018
	//If you have comments or questions contact me at acetousk@gmail.com or (614) 883-8446s
	while(true) {
		//Make sure that the left side motor(s) are attached to ports 1 and 2
		motor[port1] = vexRT[Ch3];
		motor[port2] = vexRT[Ch3];

		//And that right side motor(s) are attached to ports 3 and 4
		motor[port3] = vexRT[Ch2];
		motor[port4] = vexRT[Ch2];

		//Lift code: If 6U button is pressed, make lift go up
		if(vexRT[Btn6D] == true) {
			motor[port5] = 127;
			motor[port6] = 127;
		}
		//otherwise, if 6D button is pressed, make lift go down
		else if(vexRT[Btn6D] == true){
			motor[port5] = -127;
			motor[port6] = -127;
		}
		//if all the rest of them are not pressed, make motors not move
		else{
			motor[port5] = 0;
			motor[port6] = 0;
		}
	}
}
