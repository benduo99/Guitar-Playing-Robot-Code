#include <fstream>
#include <cstdlib>
#include <iostream>

using namespace std;

const int MAX_SIZE = 10000;

bool getTab(string &e, string &B, string &G, string &D,
		string &A, string &E, string (&tuning)[6], string fileName);

void array_init(char e[],char B[], char G[], char D [], char A[],
		 char E[]);
		 
void string2array(char are[],char arB[], char arG[], char arD [], char arA[], 
		char arE[], string e, string B, string G, string D, string A, string E);

void encodeArray(char ar[]);	

char encodeNums(string number);	

string array2string(char ar[]);

void string_init(string &e, string &B, string &G, string &D,string &A, 
		string &E, string rawe, string rawB, string rawG, string rawD, 
		string rawA, string rawE, char are[],char arB[], char arG[], 
		char arD [], char arA[], char arE[]);
		
string removeBarLines(string line);		
				 

int main()
{
	string rawe = "|", rawB = "|", rawG= "|", rawD= "|", rawA= "|", rawE= "|";
	string tuning [6];
	string fileName = "Happy Birthday";
	
	getTab(rawe, rawB, rawG, rawD, rawA, rawE, tuning, fileName);
	
	char are[MAX_SIZE], arB[MAX_SIZE], arG[MAX_SIZE], arD[MAX_SIZE], arA[MAX_SIZE], arE[MAX_SIZE];
	
	string e, B, G, D, A, E;
	
	string_init(e,B,G,D,A,E,rawe,rawB,rawG,rawD,rawA,rawE,are, arB, arG,arD,arA,arE);
	
	cout << e<<endl<<B<<endl<<G<<endl<<D<<endl<<A<<endl<<E   ;
				
	return EXIT_SUCCESS;
}

bool getTab(string &e, string &B, string &G, string &D,
		string &A, string &E, string (&tuning)[6],string fileName)
	{
		
	string readFile = fileName+ ".txt";
	ifstream fin(readFile.c_str());	

	//ifstream fin(fileName);
		
	if(!fin)
	{
		cout << "File not found";
		return false;
	}	
	
	char note;
	int stringnum = 0;
	int stringPitch =0;
	
	while(fin>>note)
	{	
		if(note == '[')
		{
			while(note!=']') //ignore [intro] completely
			{
				fin>>note;
			}
			fin>>note;
		}
	
		if(stringPitch < 6) //get string pitch
		{
			while(note!='|')
			{
				tuning[stringPitch] += note;
				fin>>note;
			}
			stringPitch++;			
		}
		else
		{		
			fin>>note;
		}
		
		if(note=='|')
		{
			string str = "";
			getline(fin,str);
		
			switch(stringnum+1) 
			{
				case 1 : e += str;
				break;
				case 2 : B += str;
			    break;
			    case 3 : G += str;
			    break;
			    case 4 : D +=  str;
			    break;
			    case 5 : A +=  str;
			    break;
			    case 6 : E += str;
			    break;
			}
				
			if(stringnum!=5) //next string
			{	
				stringnum++;				
			}
			else
			{
				stringnum = 0;
			}				
		}	
	}
	return true;				
}

void array_init(char e[],char B[], char G[], char D [], char A[], char E[])
{
	for(int i=0; i< MAX_SIZE; i++)
	{
		e[i]=B[i]=G[i]=D[i]=A[i]=E[i]='#';
	}
}

void string2array(char are[],char arB[], char arG[], char arD [], char arA[], 
		char arE[], string e, string B, string G, string D, string A, string E)
{
	for(int i=0; i<e.length(); i++)
	{
	int position =i; //compiler issue
	are[position]=e[position];
	arB[position]=B[position];
	arG[position]=G[position];
	arD[position]=D[position];
	arA[position]=A[position];
	arE[position]=E[position];
	}
}	

void encodeArray(char ar[])
{
	//0 is 48, 9 is 57
	int position=0;
	while(ar[position]!='#')
	{
		if(ar[position]>=48&&ar[position]<=57)//if position is number
		{
			string note="";
			note=ar[position];
			
			if(ar[position+1]>=48&&ar[position+1]<=57) 
			{
				note += ar[position+1];
				ar[position+1] ='-';	
			}
			
		ar[position] = encodeNums(note);
		
		}
		position++;
	}
	
}

char encodeNums(string number)
{
	char note;
	int value = atoi(number.c_str());
	// A is 65, B is 66 ...
	if(value>0&&value<=12)
		note = (char)value + 64;
	else if (value>12&&value<=24)
		note = (char)value +52;
	else if (value == 0)
		note = 'L';		
	else
		note = '-';
	return note;	
}

string array2string(char ar[])
{
	int count = 0;
	string notes ="";
	while(ar[count]!='#')
	{
		notes +=ar[count];
		count++;
	}
	
	return notes;
}

void string_init(string &e, string &B, string &G, string &D,string &A, 
		string &E, string rawe, string rawB, string rawG, string rawD, 
		string rawA, string rawE, char are[],char arB[], char arG[], 
		char arD [], char arA[], char arE[])
{
	array_init(are, arB, arG, arD, arA, arE);
	string2array(are, arB, arG, arD, arA, arE, rawe, rawB, rawG, rawD, rawA, rawE);
		
	encodeArray(are);
	encodeArray(arB);
	encodeArray(arG);
	encodeArray(arD);
	encodeArray(arA);
	encodeArray(arE);
		
	e = removeBarLines(array2string(are));
	B = removeBarLines(array2string(arB));
	G = removeBarLines(array2string(arG));
	D = removeBarLines(array2string(arD));
	A = removeBarLines(array2string(arA));
	E = removeBarLines(array2string(arE));
	
}

string removeBarLines(string line)
{
	for(int count =0; count <line.length()-1;count++)
	{
		if(line[count]=='|')
			line[count] ='-';
	}
	return line;
}



