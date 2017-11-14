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
	char NoteSeqA[];
	char NoteSeqG[];
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
	const int degree_of_rotation = 45;
	bool aIsRunning = false;
	bool bIsRunning = false;
	if(A.currentNote != '-')
	{
		motor[A.strummingMotor] = A.parity * 75;
		switchParity(A);
		aIsRunning = true;
	}
	if(G.currentNote != '-')
	{
		motor[G.strummingMotor] = G.parity * 75;
		switchParity(G);
		bIsRunning = true;
	}
	while((aIsRunning && abs(nMotorEncoder[A.strummingMotor]) < degree_of_rotation) || bIsRunning && abs(nMotorEncoder[G.strummingMotor]) < degree_of_rotation)
	{
		if(abs(nMotorEncoder[A.strummingMotor]) >= degree_of_rotation)
		{
			motor[A.strummingMotor] = 0;
		}
		if(abs(nMotorEncoder[G.strummingMotor]) >= degree_of_rotation)
		{
			motor[G.strummingMotor] = 0;
		}
	}

	motor[A.strummingMotor] = motor[G.strummingMotor] = 0;

	resetMotorEncoder(A.strummingMotor);
	resetMotorEncoder(G.strummingMotor);
}


task main()
{
	// assume we recieved the string
	song_info Song_2;
	//blur reference
	Line A;
	Line G;
	Song_2.NoteSeqA[] = "enter-string-A-sequence-as-a-string-here0";
	Song_2.NoteSeqG[] = "enter-string-G-sequence-as-a-string-here0";


	initializeLine(A, 1, 1, motorA);
	initializeLine(G, 2, 2, motorB);

	while(!getButtonPress(buttonAny))
	{}
	while(getButtonPress(buttonAny))
	{}
	displayString(0,"%s",song_info.song_name);
	while (Song_2.NoteSeqA[current] && Song_2.NoteSeqG[current])
	//the end of the file is going to change the | to a 0
	{
		updateNote(A, G, Song_2.NoteSeqA[current], Song_2.NoteSeqG[current);
		strum (A,G);
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


}
