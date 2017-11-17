#include "EV3_FileIO.c"
const int MOTOR_TEMPO = 75;
const int DEGREE_OF_ROTATION = 45;
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


	task main()
	{
		const int LONG_TAB = 300;
	//open file and read  (file is in a string)
TFileHandle fin_A;
TFileHandle fin_G;
bool fileOkayA = openReadPC(fin_A, "Play_me_A.txt");
bool fileOkayG = openReadPC(fin_G, "Play_me_G.txt");
if(!fileOkayA || !fileOkayG)
{
	displayString(0, "Failed to Open File");
	displayString(1, "I'm not going to let you go on");
	displayString(2, "Force terminate me plz");
	while(true)
	{}
}
	// assume we recieved the string
		song_info Song_2;
		Song_2.song_name = "Complex a$$ song!!!";
	//blur reference
		Line A;
		Line G;
		char NoteSeqA[LONG_TAB];
		char NoteSeqG[LONG_TAB];
		for(int i = 0; i < LONG_TAB; i++)
		{
			NoteSeqA[i] = 0;
			NoteSeqG[i] = 0;
		}



		for (int seqIndex = 0; seqIndex < LONG_TAB; seqIndex++)
		{
			readCharPC(fin_A, NoteSeqA[seqIndex]);
		}


		for (int seqIndex = 0; seqIndex < LONG_TAB; seqIndex++)
		{
			readCharPC(fin_G, NoteSeqG[seqIndex]);
		}


		initializeLine(A, 1, 1, motorA);
		initializeLine(G, 2, 2, motorB);

		while(!getButtonPress(buttonAny))
		{}
	while(getButtonPress(buttonAny))
	{}
eraseDisplay();
displayString(0, "Now Playing:");
displayString(1,"%s",Song_2.song_name);

for(int i = 0; i < 5; i++)
{
	int current = 0;
while (NoteSeqA[current] != '|' && NoteSeqG[current] != '|')
	//the end of the file is going to return null which is false as a character
{
	updateNote(A, G, NoteSeqA[current], NoteSeqG[current]);
	strum (A,G);
	displayBigTextLine(3,"%c",NoteSeqA[current]);
	displayBigTextLine(6,"%c",NoteSeqG[current]);
	wait1Msec(100);
	current ++;
}
}
displayString(0, "That is the end of the song:");
displayString(2, "Feel free to terminate me now", Song_2.song_name);
while(!getButtonPress(buttonAny))
{}
while(getButtonPress(buttonAny))
{}
muted_reset (A,G);
motor[A.strummingMotor] = motor[G.strummingMotor] = 0;
displayString(0,"Thanks :)");
wait1Msec(5000);
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
