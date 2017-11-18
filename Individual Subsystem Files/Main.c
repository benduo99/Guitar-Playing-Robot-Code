#include "EV3_FileIO.c"
#include "lineStruct.c"
#include "strummer.c"
const int MOTOR_TEMPO = 75;
const int DEGREE_OF_ROTATION = 45;
typedef struct
{
	//notes for string A
	char NoteSeqA[100];
	char NoteSeqG[100];
	string song_name;
	//asssume that can output number of notes including dashes to play
}song_info;

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

	while (NoteSeqA[current] != '|' && NoteSeqG[current] != '|')
	//the end of the file is going to return null which is false as a character
	{
		updateNote(A, G, NoteSeqA[current], NoteSeqG[current]);

		strum (A,G);

		displayBigTextLine(3,"%c",NoteSeqA[current]);
		displayBigTextLine(6,"%c",NoteSeqG[current]);

		wait1Msec(100);

		current++;
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
