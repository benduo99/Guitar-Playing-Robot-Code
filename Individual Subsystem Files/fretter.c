float const WHEEL_RADIUS = 2.5;

//get actual measurement

//segment of code, using structs and parts from other pieces of code.

//written by Ben Duo

void zero(Line & A, Line & B)
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

	nMotorEncoder[A.pulleyMotor] = nMotorEncoder[B.pulleyMotor] = 0;

	motor[A.pulleyMotor]=motor[B.pulleyMotor]=-20;
	while(nMotorEncoder[A.pulleyMotor]<(1.74498/WHEEL_RADIUS*360) && nMotorEncoder[B.pulleyMotor]<(1.74498/WHEEL_RADIUS*360))
	{
		if(nMotorEncoder[A.pulleyMotor] == (1.74498/WHEEL_RADIUS*360))
			motor[A.pulleyMotor] = 0;
		if(nMotorEncoder[B.pulleyMotor] == (1.74498/WHEEL_RADIUS*360))
			motor[B.pulleyMotor] = 0;
	}
}

int conversion(char note)
{
	return (int)note - 64;
}

//finds distance in terms of degrees
void noteDist(Line & A, Line & B, float & dist_A, float & dist_B)
{
	//accessing the array with the distances
	dist_A = ((DISTANCE[(conversion(A.currentNote))] - DISTANCE[(conversion(A.previousNote))])*360/WHEEL_RADIUS);
	dist_B = ((DISTANCE[conversion(B.currentNote)] - DISTANCE[conversion(B.previousNote)])*360/WHEEL_RADIUS);
}

void moveFrets(Line & A, Line & B)
{
	time1[T1] = 0;
	float dist_A = 0, dist_B = 0;
	noteDist(A, B, dist_A, dist_B);
	nMotorEncoder[A.pulleyMotor] = nMotorEncoder[B.pulleyMotor] = 0;

	//if both fingers need to be moved to a higher pitch

	motor[A.pulleyMotor] = motor[B.pulleyMotor] = 100; //whatever the power is to pull the finger to a higher fret

	while(abs(nMotorEncoder[A.pulleyMotor]) <= fabs(dist_A) || abs(nMotorEncoder[B.pulleyMotor]) <= fabs(dist_B))
	{
		if(abs(nMotorEncoder[A.pulleyMotor]) >= fabs(dist_A))
			motor[A.pulleyMotor] = 0;

		if(abs(nMotorEncoder[B.pulleyMotor]) >= fabs(dist_B))
			motor[B.pulleyMotor] = 0;
	}
	motor[A.pulleyMotor] = motor[B.pulleyMotor] = 0;
	while (time1[T1] <= STRUM_TIME)
	{}
}
