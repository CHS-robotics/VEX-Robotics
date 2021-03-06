#pragma config(Sensor, in1,    Gyro,           sensorGyro)
#pragma config(Motor,  port1,           RTurn,         tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port3,           UpArm,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           Claw,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           Wrist,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           RDrive,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           LDrive,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           RLowArm,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           LLowArm,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          LTurn,         tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

bool auto = false; //Bool containing if autopilot is enabled
int count = 50;
int count2 = 20;
int count3 = 50;
int value = 0;
int zero = 0;


/////////////////
//--Functions--//
/////////////////

void rotLeft()
{
	if(count < 127)
	{
		motor[LTurn]= -count;
		motor[RTurn]= -count;
		count++;
		delay(10);
	}

	else
	{
		motor[LTurn]= -127;
		motor[RTurn]= -127;
	}
}

void rotRight()
{
	if(count < 127)
	{
		motor[LTurn]= count;
		motor[RTurn]= count;
		count++;
		delay(10);
	}

	else
	{
		motor[LTurn]= 127;
		motor[RTurn]= 127;
	}
}

void wristLeft()
{
	if(count2 < 70)
	{
		motor[Wrist]= count2;
		count2++;
		delay(20);
	}

	else
	{
		motor[Wrist]= 70;
	}
}

void wristRight()
{
	if(count2 < 70)
	{
		motor[Wrist]= -count2;
		count2++;
		delay(20);
	}

	else
	{
		motor[Wrist]= -70;
	}
}

/////////////////
//----Tasks----//
/////////////////

task drive()
{
	int threshold = 10;	//Deadzone for joystick. Default=10

	while(true)
	{

		if(auto == false) //Check if autopilot is enabled
		{

			if(vexRT[Btn7UXmtr2] == 1)
			{
				motor[LDrive]= 70;
				motor[RDrive]= 70;
			}

			else if(vexRT[Btn7DXmtr2] == 1)
			{
				motor[LDrive]= -70;
				motor[RDrive]= -70;
			}

			else if(vexRT[Btn7RXmtr2] == 1)
			{
				motor[LDrive]= -40;
				motor[RDrive]= 50;
			}

			else if(vexRT[Btn7LXmtr2] == 1)
			{
				motor[LDrive]= 50;
				motor[RDrive]= -40;
			}

			else
			{
				if(abs(vexRT[Ch2]) > threshold || abs(vexRT[Ch3]) > threshold) //Check if the joystick is past the deadzone
				{
					motor[LDrive]= vexRT[Ch2];
					motor[RDrive]= vexRT[Ch3];
				}
				else
			  {
			    motor[LDrive]  = 0;
		      motor[RDrive]  = 0;
		      count3 = 0;
		    }
			}
		}
	}
}

task rot()
{
	while(true)
	{
		if(vexRT[Btn5U] == 1)
		{
			rotLeft();
		}

		else if(vexRT[Btn6U] == 1)
		{
			rotRight();
		}

		else if(vexRT[Btn5UXmtr2] == 1)
		{
			rotLeft();
		}

		else if(vexRT[Btn6UXmtr2] == 1)
		{
			rotRight();
		}

		else
		{
			motor[LTurn]= 0;
			motor[RTurn]= 0;
			count = 50;
		}
	}
}

task arm()
{
	while(true)
	{
		if(vexRT[Ch3Xmtr2] > 10)
		{
			motor[LLowArm] = -(vexRT[Ch3Xmtr2]/11.3)*(vexRT[Ch3Xmtr2]/11.3);
			motor[RLowArm] = -(vexRT[Ch3Xmtr2]/11.3)*(vexRT[Ch3Xmtr2]/11.3);
		}

		else if(vexRT[Ch3Xmtr2] < 10)
		{
			motor[LLowArm] = (vexRT[Ch3Xmtr2]/11.3)*(vexRT[Ch3Xmtr2]/11.3);
			motor[RLowArm] = (vexRT[Ch3Xmtr2]/11.3)*(vexRT[Ch3Xmtr2]/11.3);
		}

		else
		{
			{
			motor[LLowArm] = 0;
			motor[RLowArm] = 0;
		}
		}
	}
}

task wrist()
{
	while(true)
	{
		if(vexRT[Btn5DXmtr2] == 1 && abs(vexRT[Ch1Xmtr2]) < 10)
		{
			wristLeft();
		}

		else if(vexRT[Btn6DXmtr2] == 1 && abs(vexRT[Ch1Xmtr2]) < 10)
		{
			wristRight();
		}

		else if(abs(vexRT[Ch1Xmtr2]) > 10)
		{
			motor[Wrist]= -vexRT[Ch1Xmtr2]/2;
		}

		else
		{
			motor[Wrist]= 0;
			count2 = 20;
		}
	}
}

task claw()
{
	while(true)
	{
		if(vexRT[Btn8DXmtr2] == 1)
		{
			motor[Claw]= 127;
		}

		else if(vexRT[Btn8RXmtr2] == 1)
		{
			motor[Claw]= -127;
		}

		else
		{
			motor[Claw]= 0;
		}
	}
}

task angle()
{
	while(true)
	{

	}
}

//////////////////
//-----Main-----//
//////////////////

task main()
{
	startTask(drive);
	startTask(rot);
	startTask(arm);
	startTask(wrist);
	startTask(claw);
	startTask(angle);

	SensorType[Gyro] = sensorNone;
	wait1Msec(1000);
	//Reconfigure Analog Port 8 as a Gyro sensor and allow time for ROBOTC to calibrate it
	SensorType[Gyro] = sensorGyro;
	wait1Msec(2000);

	zero = SensorValue[Gyro];

	while(true)
	{

		motor[UpArm]= -vexRT[Ch2Xmtr2];
		if(abs(vexRT[Ch2Xmtr2]) > 10)
		{
			zero = SensorValue[Gyro];
		}

		value = SensorValue[Gyro];
		if(value<zero-30 && abs(vexRT[Ch2Xmtr2]) < 10)
		{
			motor[UpArm]= 80;
		}

		else if(value>zero+30 && abs(vexRT[Ch2Xmtr2]) < 10)
		{
			motor[UpArm]= -80;
		}

		else
		{
			motor[UpArm]= -20;
		}
	}
}
