#include <fstream>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

bool getTab(string &e, string &B, string &G, string &D,
		string &A, string &E, string (&tuning)[6], string fileName);

int main()
{
	string e = "|", B = "|", G= "|", D= "|", A= "|", E= "|";
	string tuning [6];
	string fileName = "Happy Birthday";
	
	if(getTab(e, B, G, D, A, E, tuning, fileName))
		{
				
		cout << e <<endl << B << endl << G << endl << D << endl << A <<endl 
			<< E <<endl;
			
		for(int i = 0; i<6; i++)
		{
			cout <<tuning[i] << " ";
		}
	}
	else
	{
		cout<<"error";
	}
	
	
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
