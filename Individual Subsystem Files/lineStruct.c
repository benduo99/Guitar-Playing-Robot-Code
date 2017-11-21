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

void updateCurrentNote(Line & object_A, Line & object_B, char note_A, char note_B)
{
	object_A.currentNote = note_A;
	object_B.currentNote = note_B;
}

void updateCurentPosition(Line & object_A, Line & object_B)
{
	if(object_A.currentNote != '-')
		object_A.currentPosition = object_A.currentNote;

	if(object_B.currentNote != '-')
		object_B.currentPosition = object_B.currentNote
}

void initializeLine (Line & object, tMotor pulleyMotor, tSensors touchPort, tMotor strummingMotor)
{
	object.pulleyMotor = pulleyMotor;
	object.touchPort = touchPort;
	object.currentNote = '-';
	object.currentPosition = 'A';
	object.strummingMotor = strummingMotor;
	object.parity = 1;
}

void switchParity (Line & object)
{
	object.parity *= -1;
}

