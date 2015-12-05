#pragma config(Motor,  port1,           Chain,         tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           frontLeft,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           backLeft,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           backRight,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           frontRight,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           Launcher,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          Roller,        tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task shoot()
{
	while(true)
	{
		motor[Launcher] = vexRT[Ch2Xmtr2];
	}
}

task scoop()
{
	while(true)
	{
		motor[Chain] = vexRT[Ch3Xmtr2];
	}
}
task drive()
{
	while(true)
	{
		motor[frontRight] = vexRT[Ch3] - vexRT[Ch1] - vexRT[Ch4];
    motor[backRight] =  vexRT[Ch3] - vexRT[Ch1] + vexRT[Ch4];
    motor[frontLeft] = -vexRT[Ch3] - vexRT[Ch1] - vexRT[Ch4];
    motor[backLeft] =  -vexRT[Ch3] - vexRT[Ch1] + vexRT[Ch4];

	}

}

task main()
{
	startTask(scoop);
	startTask(shoot);
	startTask(drive);

	while(true)
	{
		motor[Roller] = 127;
	}
}
