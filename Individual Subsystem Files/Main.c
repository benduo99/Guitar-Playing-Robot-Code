const int MOTOR_TEMPO = 75;
const int DEGREE_OF_ROTATION = 45;
float distance[12] = {0, 3.32486, 6.4008, 9.28243, 11.99515, 14.54658, 16.9164, 19.16557, 21.26996, 23.23211, 25.08504, 26.81224};


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
	const int LONG_TAB = 300;
	//open file and read  (file is in a string)
	TFileHandle fin_A;
	TFileHandle fin_B;
	bool fileOkayA = openReadPC(fin_A, "Play_me_A.txt");
	bool fileOkayB = openReadPC(fin_B, "Play_me_G.txt");
	if(!fileOkayA || !fileOkayB)
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
		// IF THIS BREAKS, NIEL COMBINED TWO FOR LOOPS INTO ONE.
		readCharPC(fin_A, NoteSeqA[seqIndex]);
		readCharPC(fin_B, NoteSeqB[seqIndex]);
	}

	initializeLine(A, 1, 1, motorA);
	initializeLine(B, 2, 2, motorB);

	while(!getButtonPress(buttonAny))
	{}
	while(getButtonPress(buttonAny))
	{}

	eraseDisplay();
	displayString(0, "Now Playing:");
	displayString(1,"%s",Song_2.song_name);

	int current = 0;
	while (NoteSeqA[current] != '|' && NoteSeqB[current] != '|')
	//the end of the file is going to return null which is false as a character
	{
		updateNote(A, B, NoteSeqA[current], NoteSeqB[current]);

		strum (A,B);

		displayBigTextLine(3,"%c",NoteSeqA[current]);
		displayBigTextLine(6,"%c",NoteSeqB[current]);

		wait1Msec(100);

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
