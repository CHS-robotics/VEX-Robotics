#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_3,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_4,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port2,           frontRight,    tmotorVex393_MC29, openLoop, encoderPort, I2C_3)
#pragma config(Motor,  port3,           backRight,     tmotorVex393_MC29, openLoop, encoderPort, I2C_4)
#pragma config(Motor,  port4,           frontLeft,     tmotorVex393_MC29, openLoop, encoderPort, I2C_1)
#pragma config(Motor,  port5,           backLeft,      tmotorVex393_MC29, openLoop, encoderPort, I2C_2)
#pragma config(Motor,  port6,           motor4,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           motor1,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           motor2,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           motor3,        tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task drive()
{
	int X2 = 0, Y1 = 0, X1 = 0, threshold = 15;

	while(true)
	{
		if(abs(vexRT[Ch3]) > threshold)
      Y1 = vexRT[Ch3];
    else
      Y1 = 0;
    //Create "deadzone" for X1/Ch4
    if(abs(vexRT[Ch4]) > threshold)
      X1 = vexRT[Ch4];
    else
      X1 = 0;
    //Create "deadzone" for X2/Ch1
    if(abs(vexRT[Ch1]) > threshold)
      X2 = vexRT[Ch1];
    else
      X2 = 0;



		//Remote Control Commands
    motor[frontRight] = -Y1 + X2 + X1;
    motor[backRight] =  -Y1 + X2 - X1;
    motor[frontLeft] = Y1 + X2 - X1;
    motor[backLeft] =  Y1 + X2 + X1;

	}

}

task launch()
{

}

task main()
{
	startTask(drive);
	{
	}

	startTask(launch);
	{
	}


	while(true)
	{

	motor[motor1] = 127;
	motor[motor2] = 127;
	motor[motor3] = 127;
	motor[motor4] = 127;

	}

}
