float const WHEEL_RADIUS = 2.5;
//get actual measurement

//segment of code, using structs and parts from other pieces of code.

//written by Ben Duo
void zero()
{
	//test for motor direction and motor slot
	motor[A.pulleyMotor]=motor[B.pulleyMotor]=20;
	while(SensorValue[A.touchPort] != 1 || SensorValue[B.touchPort] != 1)
	{
		if(SensorValue[A.touchPort] == 1)
			motor[A.pulleyMotor] = 0;

		if(SensorValue[B.touchPort] == 1)
			motor[B.pulleyMotor] = 0;
	}

	nMotorEncoder[A.pulleyMotor] = 0;
	wait1Msec(500);

	motor[A.pulleyMotor]=motor[B.pulleyMotor]=-20;
	while(nMotorEncoder[A.pulleyMotor]<(1.74498/2.5*360))
	{}
	motor[A.pulleyMotor] = motor[B.pulleyMotor] = 0;
}

int conversion(char note)
{
	return (int)note - 64;
}

//finds distance in terms of degrees
void noteDist(Line & object_A, Line & object_B, double & dist_A, double & dist_B)
{
	//accessing the array with the distances
	dist_A = (distance[conversion(object_A.currentNote)] - distance[conversion(object_A.previousNote)])*360/WHEEL_RADIUS;
	dist_B = (distance[conversion(object_B.currentNote)] - distance[conversion(object_B.previousNote);])*360/WHEEL_RADIUS;
}

void moveFrets(Line & object_A, Line & object_B)
{
	double dist_A = 0, dist_B = 0;
	noteDist(object_A, object_B, dist_A, dist_B);
	nMotorEncoder[A.pulleyMotor] = 0, nMotorEncoder[B.pulleyMotor] = 0;

	//if both fingers need to be moved to a higher pitch

	motor[A.pulleyMotor]=motor[B.pulleyMotor]=100; //whatever the power is to pull the finger to a higher fret

	while(fabs(nMotorEncoder[A.pulleyMotor]) < fabs(dist_A) && fabs(nMotorEncoder[B.pulleyMotor]) < fabs(dist_B))
	{
		if(nMotorEncoder[A.pulleyMotor] == dist_A)
			motor[A.pulleyMotor] = 0;

		if(nMotorEncoder[B.pulleyMotor] == dist_B)
			motor[B.pulleyMotor] = 0;
	}
}
