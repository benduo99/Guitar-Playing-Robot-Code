// Niel Mistry
typedef struct
{
	// Fretting Stuff
	tMotor pulleyMotor;
	tSensors touchPort;
	char currentNote;
	char currentPosition;

	// Strumming Stuff
	tMotor strummingMotor;
	int parity;			// Left relative to motor while looking at it from behind
} Line;

// Niel Mistry
void updateCurrentNote(Line & object_A, Line & object_B, char note_A, char note_B)
{
	object_A.currentNote = note_A;
	object_B.currentNote = note_B;
}

// Niel Mistry
void updateCurrentPosition(Line & object_A, Line & object_B)
{
	if(object_A.currentNote != '-')
		object_A.currentPosition = object_A.currentNote;

	if(object_B.currentNote != '-')
		object_B.currentPosition = object_B.currentNote;
}

// Niel Mistry
void initializeLine (Line & object, tMotor pulleyMotor, tSensors touchPort, tMotor strummingMotor)
{
	object.pulleyMotor = pulleyMotor;
	object.touchPort = touchPort;
	object.currentNote = '-';
	object.currentPosition = 'A';
	object.strummingMotor = strummingMotor;
	object.parity = -1;
}

void switchParity (Line & object)
{
	object.parity *= -1;
}

// Ben Duo
void zero(Line & A, Line & B)
{
	//test for motor direction and motor slot
	
	const int MUTE_POWER = 20;
	motor[A.pulleyMotor]=motor[B.pulleyMotor] = MUTE_POWER;
	motor[A.strummingMotor] = A.parity * MUTE_POWER;
	motor[B.strummingMotor] = B.parity * MUTE_POWER;
	time1[T2] = 0;
	const int TIME_DELAY = 1000; 
	// The time delay has to be determined experimentally. NOT DONE YET.
	while(SensorValue[A.touchPort] == 0 || SensorValue[B.touchPort] == 0 || time1[T2] < TIME_DELAY)
	{
		if(SensorValue[A.touchPort] == 1)
			motor[A.pulleyMotor] = 0;

		if(SensorValue[B.touchPort] == 1)
			motor[B.pulleyMotor] = 0;

		if(time1[T2] >= TIME_DELAY)
			motor[A.strummingMotor] = motor[B.strummingMotor]  = 0;

	}
	motor[A.pulleyMotor] = motor[B.pulleyMotor] = 0;

	switchParity(A);
	switchParity(B);
}
