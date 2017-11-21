void strum(Line & A, Line & B)
{
	bool aIsRunning = false;
	bool bIsRunning = false;

	if(A.currentNote != '-')
	{
		motor[A.strummingMotor] = A.parity * MOTOR_TEMPO;
		switchParity(A);
		aIsRunning = true;
	}
	if(B.currentNote != '-')
	{
		motor[B.strummingMotor] = B.parity * MOTOR_TEMPO;
		switchParity(B);
		bIsRunning = true;
	}
	while((aIsRunning && abs(nMotorEncoder[A.strummingMotor]) < DEGREE_OF_ROTATION) || bIsRunning && abs(nMotorEncoder[B.strummingMotor]) < DEGREE_OF_ROTATION)
	{
		if(abs(nMotorEncoder[A.strummingMotor]) >= DEGREE_OF_ROTATION)
		{
			motor[A.strummingMotor] = 0;
		}
		if(abs(nMotorEncoder[B.strummingMotor]) >= DEGREE_OF_ROTATION)
		{
			motor[B.strummingMotor] = 0;
		}
	}

	motor[A.strummingMotor] = motor[B.strummingMotor] = 0;

	resetMotorEncoder(A.strummingMotor);
	resetMotorEncoder(B.strummingMotor);

	wait1Msec(500);
}

void muted_reset(Line&A, Line&B)
{
	const int ANGLE_OF_MUTE_ROTATION = 20;
	resetMotorEncoder(A.strummingMotor);
	resetMotorEncoder(B.strummingMotor);

	bool aIsRight = false;
	bool bIsRight = false;

	if (A.parity < 0)
	{
		motor[A.strummingMotor] = A.parity*MOTOR_TEMPO;
		switchParity(A);
		aIsRight = true;
	}
	if (B.parity < 0)
	{
		motor[B.strummingMotor] = B.parity*MOTOR_TEMPO;
		switchParity(B);
		bIsRight = true;
	}
	while(aIsRight && (abs(nMotorEncoder[A.strummingMotor]) < DEGREE_OF_ROTATION) || bIsRight && (abs(nMotorEncoder[B.strummingMotor]) < DEGREE_OF_ROTATION))
	{
		if(abs(nMotorEncoder[A.strummingMotor]) >= DEGREE_OF_ROTATION)
		{
			motor[A.strummingMotor] = 0;
		}
		if(abs(nMotorEncoder[B.strummingMotor]) >= DEGREE_OF_ROTATION)
		{
			motor[B.strummingMotor] = 0;
		}
	}

	resetMotorEncoder(A.strummingMotor);
	resetMotorEncoder(B.strummingMotor);

	motor[A.strummingMotor] = A.parity*MOTOR_TEMPO;
	motor[B.strummingMotor] = B.parity*MOTOR_TEMPO;

	switchParity(A);
	switchParity(B);

	while (abs(nMotorEncoder[A.strummingMotor]) <= ANGLE_OF_MUTE_ROTATION || abs(nMotorEncoder[B.strummingMotor]) <= ANGLE_OF_MUTE_ROTATION)
	{
		if (abs(nMotorEncoder[A.strummingMotor]) >= ANGLE_OF_MUTE_ROTATION)
		{
			motor[A.strummingMotor] = 0;
		}
		if (abs(nMotorEncoder[B.strummingMotor]) >= ANGLE_OF_MUTE_ROTATION)
		{
			motor[B.strummingMotor] = 0;
		}
	}

}
