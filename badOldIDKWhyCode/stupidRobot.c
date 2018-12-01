#pragma config(Motor,  port1,           a,             tmotorVex393HighSpeed_HBridge, openLoop)
#pragma config(Motor,  port2,           b,             tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port3,           left1,         tmotorVex393HighSpeed_MC29, openLoop, driveLeft, encoderPort, None)
#pragma config(Motor,  port4,           left2,         tmotorVex393HighSpeed_MC29, openLoop, driveLeft, encoderPort, None)
#pragma config(Motor,  port5,           left3,         tmotorVex393HighSpeed_MC29, openLoop, driveLeft, encoderPort, None)
#pragma config(Motor,  port6,           right1,        tmotorVex393HighSpeed_MC29, openLoop, driveRight, encoderPort, None)
#pragma config(Motor,  port7,           right2,        tmotorVex393HighSpeed_MC29, openLoop, driveRight, encoderPort, None)
#pragma config(Motor,  port8,           right3,        tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port9,           c,             tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port10,          dab,           tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main(){
	while(true){
		if(vexRT[Btn5D]==1){
			motor[a]=127;
			motor[b]=127;
			motor[c]=127;
			motor[dab]=127;
			motor[right2]= 127;
			motor[right3]= 127;
			motor[left1] = 127;
			motor[left2] = 127;
			motor[left3] = 127;
			motor[right1]= 127;
			} else{
			motor[a]=0;
			motor[b]=0;
			motor[c]=0;
			motor[dab]=0;
			motor[right2]= 0;
			motor[right3]= 0;
			motor[left1] = 0;
			motor[left2] = 0;
			motor[left3] = 0;
			motor[right1]= 0;
		}
	}
}
