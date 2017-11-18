void strum(Line A, Line G)
{
	bool aIsRunning = false;
	bool bIsRunning = false;

	if(A.currentNote != '-')
	{
		motor[A.strummingMotor] = A.parity * MOTOR_TEMPO;
		switchParity(A);
		aIsRunning = true;
	}
	if(G.currentNote != '-')
	{
		motor[G.strummingMotor] = G.parity * MOTOR_TEMPO;
		switchParity(G);
		bIsRunning = true;
	}
	while((aIsRunning && abs(nMotorEncoder[A.strummingMotor]) < DEGREE_OF_ROTATION) || bIsRunning && abs(nMotorEncoder[G.strummingMotor]) < DEGREE_OF_ROTATION)
	{
		if(abs(nMotorEncoder[A.strummingMotor]) >= DEGREE_OF_ROTATION)
		{
			motor[A.strummingMotor] = 0;
		}
		if(abs(nMotorEncoder[G.strummingMotor]) >= DEGREE_OF_ROTATION)
		{
			motor[G.strummingMotor] = 0;
		}
	}

	motor[A.strummingMotor] = motor[G.strummingMotor] = 0;

	resetMotorEncoder(A.strummingMotor);
	resetMotorEncoder(G.strummingMotor);
}

void muted_reset(Line&A, Line&G)
{
	const int ANGLE_OF_MUTE_ROTATION = 20;
	resetMotorEncoder(A.strummingMotor);
	resetMotorEncoder(G.strummingMotor);
	bool aIsRight = false;
	bool gIsRight = false;
	if (A.parity < 0)
	{
		motor[A.strummingMotor] = A.parity*MOTOR_TEMPO;
		switchParity(A);
		aIsRight = true;
	}
	if (G.parity < 0)
	{
		motor[G.strummingMotor] = G.parity*MOTOR_TEMPO;
		switchParity(G);
		gIsRight = true;
	}
	while(aIsRight && (abs(nMotorEncoder[A.strummingMotor]) < DEGREE_OF_ROTATION) || gIsRight && (abs(nMotorEncoder[G.strummingMotor]) < DEGREE_OF_ROTATION))
	{
		if(abs(nMotorEncoder[A.strummingMotor]) >= DEGREE_OF_ROTATION)

			{		motor[A.strummingMotor] = 0;
			}
			if(abs(nMotorEncoder[G.strummingMotor]) >= DEGREE_OF_ROTATION)
			{
				motor[G.strummingMotor] = 0;
			}
		}
			resetMotorEncoder(A.strummingMotor);
			resetMotorEncoder(G.strummingMotor);
			motor[A.strummingMotor] = A.parity*MOTOR_TEMPO;
			motor[G.strummingMotor] = G.parity*MOTOR_TEMPO;


			switchParity(A);
			switchParity(G);
			while (abs(nMotorEncoder[A.strummingMotor]) <= ANGLE_OF_MUTE_ROTATION || abs(nMotorEncoder[G.strummingMotor]) <= ANGLE_OF_MUTE_ROTATION)
			{
				if (abs(nMotorEncoder[A.strummingMotor]) >= ANGLE_OF_MUTE_ROTATION)
				{
					motor[A.strummingMotor] = 0;
				}
				if (abs(nMotorEncoder[G.strummingMotor]) >= ANGLE_OF_MUTE_ROTATION)
				{
					motor[G.strummingMotor] = 0;
				}
			}

	}