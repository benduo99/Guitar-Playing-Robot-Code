const int MOTOR_TEMPO = 75;
const int DEGREE_OF_ROTATION = 45;
const int ANGLE_OF_MUTE_ROTATION = 20;
const int STRUM_TIME = 0;

#include "EV3_FileIO.c"
#include "lineStruct.c"
#include "strummer.c"
#include "fretter.c"

typedef struct
{
	//notes for string A
	string song_name;
	//asssume that can output number of notes including dashes to play
}song_info;

task main()
{
	const int LONG_TAB = 100;
	TFileHandle fin_A;
	TFileHandle fin_B;
	bool fileOkayA = openReadPC(fin_A, "Play_me_A.txt");
	bool fileOkayB = openReadPC(fin_B, "Play_me_B.txt");
	if(!fileOkayA || !fileOkayB)
	{
		displayString(0, "Failed to Open File");

		//open file and read  (file is in a string)
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
	Line B;
	char NoteSeqA[LONG_TAB];
	char NoteSeqB[LONG_TAB];
	for(int i = 0; i < LONG_TAB; i++)
	{
		NoteSeqA[i] = 0;
		NoteSeqB[i] = 0;
	}

	for (int seqIndex = 0; seqIndex < LONG_TAB; seqIndex++)
	{
		readCharPC(fin_A, NoteSeqA[seqIndex]);
		readCharPC(fin_B, NoteSeqB[seqIndex]);
	}

	initializeLine(A, motorC, S1, motorA);
	initializeLine(B, motorD, S2, motorB);
	//activatePID(A, B);
	zero(A,B);
	initial_unmute(A,B);
	while(!getButtonPress(buttonAny))
	{}
	while(getButtonPress(buttonAny))
	{}

	eraseDisplay();
	displayString(0, "Now Playing:");
	displayString(1,"%s",Song_2.song_name);

	int current = 0;

	while (current < LONG_TAB && NoteSeqA[current] != '|' && NoteSeqB[current] != '|')
	//the end of the file is going to return null which is false as a character
	{
		updateCurrentNote(A, B, NoteSeqA[current], NoteSeqB[current]);
		moveFrets(A,B);
		//strum (A,B);
		waitForButtonPress1();

		updateCurrentPosition(A,B);

		displayBigTextLine(3,"%c %d",NoteSeqA[current]);
		displayBigTextLine(6,"%c %d",NoteSeqB[current]);

		current++;
	}


	displayString(0, "That is the end of the song:");
	displayString(2, "Feel free to terminate me now", Song_2.song_name);

	while(!getButtonPress(buttonAny))
	{}
	while(getButtonPress(buttonAny))
	{}

	muted_reset (A,B);

	motor[A.strummingMotor] = motor[B.strummingMotor] = 0;

	displayString(0,"Thanks :)");

	wait1Msec(5000);
}
