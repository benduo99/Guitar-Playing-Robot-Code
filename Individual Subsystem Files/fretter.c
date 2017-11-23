float const WHEEL_RADIUS = 1.2;
float const PULLEY_POWER = 100;

//get actual measurement

//segment of code, using structs and parts from other pieces of code.

//written by Ben Duo

int direction(int a)
{
	if(a == 0)
	{
		return 0;
	}
	return -a/abs(a);
}
void waitForButtonPress1()
{
	while(!getButtonPress(buttonAny))
	{}
	while(getButtonPress(buttonAny))
	{}
}

void zero(Line & A, Line & B)
{
	//test for motor direction and motor slot

	motor[A.pulleyMotor]=motor[B.pulleyMotor] = 20;
	motor[A.strummingMotor] = A.parity * 20;
	motor[B.strummingMotor] = B.parity * 20; 
	time1[T2] = 0;
	// The time delay has to be determined experimentally. NOT DONE YET. 
	while(SensorValue[A.touchPort] == 0 || SensorValue[B.touchPort] == 0 || time1[T2] < 2000)
	{
		if(SensorValue[A.touchPort] == 1)
			motor[A.pulleyMotor] = 0;

		if(SensorValue[B.touchPort] == 1)
			motor[B.pulleyMotor] = 0;
		
		if(time1[T2] >= 2000)
			motor[A.strummingMotor] = motor[B.strummingMotor]  = 0;

	}
	motor[A.pulleyMotor] = motor[B.pulleyMotor] = 0;

	switchParity(A);
	switchParity(B);
}

int conversion(char note)
{
	return (int)note - 65;
}

//finds distance in terms of degrees
void noteDist(Line & A, Line & B, float & dist_A, float & dist_B)
{
	// accessing the array with the distances
	if(A.currentNote != '-')
	{
		dist_A = ((DISTANCE[conversion(A.currentNote)] - DISTANCE[conversion(A.currentPosition)])*360/(2*PI*WHEEL_RADIUS));
	}
	else
	{
		dist_A = 0;
	}
	if(B.currentNote != '-')
	{
		dist_B = ((DISTANCE[conversion(B.currentNote)] - DISTANCE[conversion(B.currentPosition)])*360/(2*PI*WHEEL_RADIUS));
	}
	else
	{
		dist_B = 0;
	}
}

void moveFrets(Line & A, Line & B)
{
	time1[T1] = 0;
	mute(A,B);
	float dist_A = 0, dist_B = 0;
	noteDist(A, B, dist_A, dist_B);
	displayBigTextLine(0, "%.2f     %.2f", dist_A, dist_B);
	// waitForButtonPress1();
	nMotorEncoder[A.pulleyMotor] = nMotorEncoder[B.pulleyMotor] = 0;

	//if both fingers need to be moved to a higher pitch

	motor[A.pulleyMotor] = direction(dist_A) * PULLEY_POWER;
	motor[B.pulleyMotor] = direction(dist_B) * PULLEY_POWER;

	while(abs(nMotorEncoder[A.pulleyMotor]) < fabs(dist_A) || abs(nMotorEncoder[B.pulleyMotor]) < fabs(dist_B))
	{
		if(abs(nMotorEncoder[A.pulleyMotor]) >= fabs(dist_A))
			motor[A.pulleyMotor] = 0;

		if(abs(nMotorEncoder[B.pulleyMotor]) >= fabs(dist_B))
			motor[B.pulleyMotor] = 0;
	}
	
	motor[A.pulleyMotor] = motor[B.pulleyMotor] = 0;
	unmute(A,B);
	while (time1[T1] <= STRUM_TIME)
	{}
}
