float const WHEEL_RADIUS = 1.2;
float const PULLEY_POWER = 90;
const float DISTANCEB[12] = {0, 3.644, 6.922, 9.844, 12.535, 15.363, 17.760, 20.546, 22.693, 24.640, 25.714, 28.651};
const float DISTANCEA[12] = {0, 4.671, 7.864, 10.409, 13.352, 15.855, 18.525, 20.975, 23.363, 25.290, 26.976, 29.133};

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

	motor[A.pulleyMotor]=motor[B.pulleyMotor]=20;
	while(SensorValue[A.touchPort] == 0 || SensorValue[B.touchPort] == 0)
	{
		if(SensorValue[A.touchPort] == 1)
			motor[A.pulleyMotor] = 0;

		if(SensorValue[B.touchPort] == 1)
			motor[B.pulleyMotor] = 0;

	}
	motor[A.pulleyMotor] = motor[B.pulleyMotor] = 0;
/*	nMotorEncoder[A.pulleyMotor] = nMotorEncoder[B.pulleyMotor] = 0;
	motor[A.pulleyMotor]=motor[B.pulleyMotor]=-20;

	// Move a cm bac to 0 pos
	while(abs(nMotorEncoder[A.pulleyMotor])<(360/(2 * PI * WHEEL_RADIUS)) || abs(nMotorEncoder[B.pulleyMotor])<(360/(2*PI*WHEEL_RADIUS)))
	{
		if(abs(nMotorEncoder[A.pulleyMotor]) >= (1.74498/(2 *  PI * WHEEL_RADIUS)*360))
			motor[A.pulleyMotor] = 0;
		if(abs(nMotorEncoder[B.pulleyMotor]) >= (1.74498/(2 *  PI * WHEEL_RADIUS)*360))
			motor[B.pulleyMotor] = 0;
	}

	motor[A.pulleyMotor] = motor[B.pulleyMotor] = 0;*/
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
		dist_A = ((DISTANCEA[conversion(A.currentNote)] - DISTANCEA[conversion(A.currentPosition)])*360/(2*PI*WHEEL_RADIUS));
	}
	else
	{
		dist_A = 0;
	}
	if(B.currentNote != '-')
	{
		dist_B = ((DISTANCEB[conversion(B.currentNote)] - DISTANCEB[conversion(B.currentPosition)])*360/(2*PI*WHEEL_RADIUS));
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

		// waitForButtonPress1();
		if(abs(nMotorEncoder[A.pulleyMotor]) >= fabs(dist_A))
			motor[A.pulleyMotor] = 0;

		if(abs(nMotorEncoder[B.pulleyMotor]) >= fabs(dist_B))
			motor[B.pulleyMotor] = 0;
	}
	displayString(6, "heyyyyy");
	motor[A.pulleyMotor] = motor[B.pulleyMotor] = 0;
	unmute(A,B);
	while (time1[T1] <= STRUM_TIME)
	{}
}
