const float TOL = 2;

int setAngleToMuteA(Line const & A)
{
	if(A.parity == -1)
	{
		return 34;
	}

	return 40;
}

int setAngleToMuteB(Line const & B)
{
	if(B.parity == -1)
	{
		return 35;
	}

	return 42;
}
		
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
	while((aIsRunning && abs(nMotorEncoder[A.strummingMotor]) < DEGREE_OF_ROTATION) || (bIsRunning && abs(nMotorEncoder[B.strummingMotor]) < DEGREE_OF_ROTATION))
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
//called RIGHT after zero function
void initial_unmute (Line & A, Line & B)
{
	resetMotorEncoder(A.strummingMotor);
	resetMotorEncoder(B.strummingMotor);
	
	motor[A.strummingMotor] = A.parity*MOTOR_TEMPO;
	switchParity(A);
	
	motor[B.strummingMotor] = B.parity*MOTOR_TEMPO;
	switchParity(B);

	while ((abs(nMotorEncoder[A.strummingMotor]) < ANGLE_OF_MUTE_ROTATION) || (abs(nMotorEncoder[B.strummingMotor]) < ANGLE_OF_MUTE_ROTATION))
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
	motor[A.strummingMotor] = 0;
	motor[B.strummingMotor] = 0;

	resetMotorEncoder(A.strummingMotor);
	resetMotorEncoder(B.strummingMotor);
}

void mute(Line&A, Line&B)
{
	int angleToMoveA = 0;
	int angleToMoveB = 0;
	resetMotorEncoder(A.strummingMotor);
	resetMotorEncoder(B.strummingMotor);
	if (A.currentNote != '-')
	{
		angleToMoveA = setAngleToMuteA(A);
		motor[A.strummingMotor] = A.parity*MOTOR_TEMPO;
		switchParity(A);
	}
	if (B.currentNote != '-')
	{
		angleToMoveB = setAngleToMuteB(B);
		motor[B.strummingMotor] = B.parity*MOTOR_TEMPO;
		switchParity(B);
	}


	while ((A.currentNote != '-' && abs(nMotorEncoder[A.strummingMotor]) < angleToMoveA) || (B.currentNote != '-' && abs(nMotorEncoder[B.strummingMotor]) < angleToMoveB))
	{
		if (abs(nMotorEncoder[A.strummingMotor]) >= angleToMoveA)
		{
			motor[A.strummingMotor] = 0;
		}
		if (abs(nMotorEncoder[B.strummingMotor]) >= angleToMoveB)
		{
			motor[B.strummingMotor] = 0;
		}
	}
	motor[A.strummingMotor] = 0;
	motor[B.strummingMotor] = 0;
}
//mute then unmute should be called BEFORE strumming
void unmute(Line&A, Line&B)
{

	int angleToMoveA = 0;
	int angleToMoveB = 0;

	resetMotorEncoder(A.strummingMotor);
	resetMotorEncoder(B.strummingMotor);

	if (A.currentNote != '-')
	{
		angleToMoveA = setAngleToMuteA(A);	
		motor[A.strummingMotor] = A.parity*MOTOR_TEMPO;
		switchParity(A);
	}
	if (B.currentNote != '-')
	{
		angleToMoveB = setAngleToMuteB(B);
		motor[B.strummingMotor] = B.parity*MOTOR_TEMPO;
		switchParity(B);
	}

	while ((A.currentNote != '-' && abs(nMotorEncoder[A.strummingMotor]) < angleToMoveA) || (B.currentNote != '-' && abs(nMotorEncoder[B.strummingMotor]) < angleToMoveB))
	{
		if (abs(nMotorEncoder[A.strummingMotor]) >= angleToMoveA)
		{
			motor[A.strummingMotor] = 0;
		}
		if (abs(nMotorEncoder[B.strummingMotor]) >= angleToMoveB)
		{
			motor[B.strummingMotor] = 0;
		}
	}
	motor[A.strummingMotor] = 0;
	motor[B.strummingMotor] = 0;
	
	if(A.currentNote != '-' || B.currentNote != '-')
	{
		wait1Msec(200);
	}

	resetMotorEncoder(A.strummingMotor);
	resetMotorEncoder(B.strummingMotor);

}


void muted_reset(Line&A, Line&B)
{
	resetMotorEncoder(A.strummingMotor);
	resetMotorEncoder(B.strummingMotor);
	updateCurrentNote(A,B,'|','|');

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
	motor[A.strummingMotor] = 0;
	motor[B.strummingMotor] = 0;
	mute(A,B);
}
