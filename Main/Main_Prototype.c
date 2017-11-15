const int MOTOR_TEMPO = 75;
typedef struct
{
	// Fretting Stuff
	tMotor pulleyMotor;
	tSensors touchPort;
	char currentNote;

	// Strumming Stuff
	tMotor strummingMotor;
	int parity;    // Left relative to motor while looking at it from behind
}Line;

typedef struct
{
	//notes for string A
	char NoteSeqA[100];
	char NoteSeqG[100];
	string song_name;
	//asssume that can output number of notes including dashes to play
}song_info;

void switchParity(Line & object)
{
	object.parity *= -1;
}
void updateNote(Line & object_A, Line & object_G, char note_A, char note_G)
{
	object_A.currentNote = note_A;
	object_G.currentNote = note_G;
}

void initializeLine(Line & object, tMotor pulleyMotor, tSensors touchPort, tMotor strummingMotor)
{
	object.pulleyMotor = pulleyMotor;
	object.touchPort = touchPort;
	object.currentNote = '-';
	object.strummingMotor = strummingMotor;
	object.parity = 1;
}

void strum(Line A, Line G)
{
	const int DEGREE_OF_ROTATION = 45;
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
	if (A.parity < 0)
	{
		motor[A.strummingMotor] = MOTOR_TEMPO;
		switchParity(A);
	}
	if (G.parity < 0)
	{
		motor[G.strummingMotor] = MOTOR_TEMPO;
		switchParity(G);
	}
	motor[A.strummingMotor] = motor[G.strummingMotor] = MOTOR_TEMPO;
	if (A.parity < 0 && G.parity < 0)
	{
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
}


task main()
{
	// assume we recieved the string
	song_info Song_2;
	Song_2.song_name = "Complex a$$ song!!!";
	//blur reference
	Line A;
	Line G;
	char NoteSeqA[] = "e--1--2--3--4----5--6--6--7----8-8---8-8---8-8---8-8---8-8-8-8-8-8-88--8-88-8--80";
	char NoteSeqG[] = "e--1--2--3--4----5--6--6--7----8-8---8-8---8-8---8-8---8-8-8-8-8-8-88--8-88-8--80";


	initializeLine(A, 1, 1, motorA);
	initializeLine(G, 2, 2, motorB);

	while(!getButtonPress(buttonAny))
	{}
	while(getButtonPress(buttonAny))
	{}
	displayString(0,"%s",Song_2.song_name);
	int current = 0;
	while (NoteSeqA[current] && NoteSeqG[current])
	//the end of the file is going to change the | to a 0
	{
		updateNote(A, G, NoteSeqA[current], NoteSeqG[current]);
		strum (A,G);
		wait1Msec(100);
		current ++;
	}
	displayString(0, "That is the end of the song:");
	displayString(1, "Feel free to terminate me now", Song_2.song_name);
	while(!getButtonPress(buttonAny))
	{}
	while(getButtonPress(buttonAny))
	{}
	displayString(0,"Thanks :)");
	muted_reset (A,G);
	motor[A.strummingMotor] = motor[G.strummingMotor] = 0;
	}
//	while(getButtonPress(buttonAny))
//	{
//		if(getButtonPress(buttonEnter))
//		{
//			updateNote(A, 'G');
//		}
//		if(getButtonPress(buttonLeft))
//		{
//			updateNote(G, 'C');
//		}
//		if(getButtonPress(buttonRight))
//		{
//			updateNote(A, '-');
//		}
//		if(getButtonPress(buttonDown))
//		{
//			updateNote(G, '-');
//		}


//	strum(A, G);
