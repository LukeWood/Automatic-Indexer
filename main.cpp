#include "vector.h"
#include "wordinfo.h"
#include "simile.h"
#include <cstring>
#include <stdlib.h>
#include <iostream>
#include <fstream>
using std::cout;
using std::ifstream;
using std::ofstream;

//I use a small piece of this from cplusplus.com
void alphalower(char*& toconvert)
{
	int dif = 'A'-'a';
	int count = 0;
	for(int i = 0; i < strlen(toconvert); i++)
	{
		if(isalpha(toconvert[i]))
		{
			count++;
		}
	}
	char* temp = new char[count+1];
	int j = 0;
	for(int i = 0; i < strlen(toconvert);i++)
	{
		if(isalpha(toconvert[i]))
		{
			if(toconvert[i] >= 'A' && toconvert[i] <='Z')
			{
				temp[j] = toconvert[i]  - dif;
			}
			else
			{
				temp[j] = toconvert[i];
			}
			j++;
		}
	}
	temp[count] = '\0';
	delete[] toconvert;
	toconvert = temp;
}

void extractLine(char*& toChange,std::istream& in)
{	
	if(toChange != NULL)
	{
		delete[] toChange;
	}
	char tempchar='a';
	char* line = new char[30];
	int size = 30;
	int index = 0;
	while(!in.eof()&&tempchar !='\n'&&tempchar!='\0')
	{
		tempchar = in.get();
		if(tempchar == '\n')
		{
			line[index] = '\0';
		}
		else
		{
		line[index] = tempchar;
		}
		index++;
		if(index == size)
		{
			char* ctemp = new char[size+50];
			for(int i = 0; i < size; i++)
			{
				ctemp[i] = line[i];
			}
			size+=50;
			delete[] line;
			line = ctemp;
		}
	}
	if(index < size)
	{
		line[index] ='\0';
	}
	else
	{
	char* ctemp = new char[size+1];
        for(int i = 0; i < size; i++)
        {
        	ctemp[i] = line[i];
        }
	ctemp[size] = '\0';

	delete[] line;
	line = ctemp;
	}	
	toChange = line;
}

char** splitline(char*& line, char toSplit, int& size)
{
	size = 1;
	char** words;
	for(int i = 0; i < strlen(line); i++)
	{
		if(line[i] == toSplit)
		{
			size++;
		}
	}
	words = new char*[size];
	for(int i = 0; i < size; i++)
	{
		words[i] = NULL;
	}
	int wordnum = 0;
	int index = 0;
	for(int i = 0; i < strlen(line); i++)
	{
		if(line[i] == toSplit)
		{
			words[wordnum] = new char[i-index+1];
			int cnum = 0;
			for(int j = index; j < i; j++)
			{
				words[wordnum][cnum] = line[j];
				cnum++;
			}
			words[wordnum][i-index] = '\0';
			index = i+1;
		//	cout<<words[wordnum]<<" "<<strlen(words[wordnum])<<'\n';
			wordnum++;
		}
	}
	words[size-1] = new char[strlen(line)-index+1];
	for(int i = index; i < strlen(line); i++)
	{
		words[size-1][i-index] = line[i];
	}
	words[size-1][strlen(line)-index] = '\0';
	for(int i = 0; i < size; i++)
	{
		alphalower(words[i]);
	}
	return words;
}



//Prints the index to an ostream
void printIndex(vector<wordinfo> &words, vector<simile>&similes,std::ostream& os)
{
	//SORTVECTORSALPHABETICALLY
	int flen = words.size() + similes.size();
	char** fullindex = new char*[flen];
	for(int i = 0; i < words.size(); i++)
	{
		fullindex[i] = words[i].strVal();	
	}
	for(int i = 0; i < similes.size(); i++)
	{
		//TODO CHECK THIS
		fullindex[i+words.size()] = similes[i].strVal();
	}
	
	cout<<fullindex[flen-1];
	char* hold;
	for(int i = 0; i < flen-1; i++)
	{
		for(int j = 0; j < flen-1; j++)
		{
			if(strcmp(fullindex[j],fullindex[j+1])>0)
			{
				hold = fullindex[j];
				fullindex[j] = fullindex[j+1];
				fullindex[j+1] = hold;
			}
		}
	}
	
	for(int i = 0; i < flen; i++)
	{
		wordinfo w(fullindex[i]);
		if(words.find(w) == -1)
		{
			os<<fullindex[i];
		}
		else
		{
			os<<words[words.find(w)];
		}
	}
	
	for(int i = 0; i < flen; i++)
	{
		delete[] fullindex[i];
	}	
	delete[] fullindex;
}


//This method analyzes a line of the catagory file creating similes for each word after the equals sign that refer to the relevant word in wordbank.
void analyzeCatLine(char* & line,vector<wordinfo>& wordbank, vector<simile>& similes)
{
	int size;
	char** words = splitline(line, ' ',size);
	if(size > 1)
	{
		wordinfo w(words[0]);
		int wordnum;
		if(wordbank.find(w) ==-1)
		{
			wordbank.push(w);
			wordnum = wordbank.size()-1;
		}
		else
		{
			wordnum = wordbank.find(w);
		}
		cout<<"The wordnum was "<<wordnum<<"\n";
		//i = 2 in order to ignore the equal sign.
		for(int i = 2; i < size; i++)
		{
			cout<<"Creating a simile for number "<<i<<" "<<words[i]<<" which is a simile for "<<wordbank[wordnum].getword()<<"\n";
			simile s(words[i],wordbank[wordnum]);
			similes.push(s);
			wordbank[wordnum].addSimile(words[i]);
		}	
	}
	//destroy dynamically allocated memory
	for(int i = 0; i < size; i++)
	{
		if(words[i] != NULL)
		{
			delete[] words[i];
			words[i] = NULL;
		}
	}
	if(words != NULL)
	{
		delete[] words;
		words = NULL;
	}
}

void analyzeInputLine(int pagenum,char*& line, vector<wordinfo>& wordbank, vector<simile>& similes)
{
	int size;
	char** words = splitline(line,' ',size);
	for(int i = 0; i < size; i++)
	{
		wordinfo w(words[i]);
		simile s(words[i],w);
		if(wordbank.find(w) == -1 && similes.find(s) == -1)
		{
			wordbank.push(w);
			wordbank[wordbank.size()-1]<<pagenum;
		}
		else
		{
			int snum = similes.find(s);
			if(!(snum == -1))
			{
				similes[snum]<<pagenum;
			}
			int wnum = wordbank.find(w);
			if(!(wnum==-1))
			{
				wordbank[wnum]<<pagenum;
			}
		}
	}
	for(int i = 0; i < size; i++)
	{
		if(words[i] != NULL)
		{
			delete[] words[i];
			words[i] = NULL;
		}
	}
	if(words != NULL)
	{
		delete[] words;
		words = NULL;
	}
}

void makeNumeric(char* &toChange)
{
	char* numericVersion;
	int count = 0;
	for(int i = 0; i < strlen(toChange); i++)
	{
		if(isdigit(toChange[i]))
		{
			count++;
		}
	}
	numericVersion = new char[count+1];
	int j=0;
	for(int i = 0; i < strlen(toChange); i++)
	{
		if(isdigit(toChange[i]))
		{
			numericVersion[j] = toChange[i];
			j++;
		}
	}
	numericVersion[count] = '\0';
	delete[] toChange;
	toChange = numericVersion;
}

//This is where almost everything happens.
void analyzeData(char** argv)
{
	char* inName = argv[1];
	char* catName = argv[2];
	char* outName = argv[3];	
	vector<wordinfo> words;
	vector<simile> similes;
	ifstream fileIn;
	
	//DETERMINE CATAGORIES
	
	fileIn.open(catName);
	if(!fileIn)
	{
		cout<<"Error opening file.";
		return;
	}

	while(!fileIn.eof())
	{
		char* temp = NULL;
		extractLine(temp,fileIn);
		analyzeCatLine(temp,words,similes);
		delete[] temp;
		//read in each catagory
	}
	fileIn.close();
	
	//parse the file.
	cout<<"Closed cat file.\n";
	fileIn.open(inName);
	cout<<"Opened input file\n";
	if(!fileIn)
	{
		cout<<"Error opening file\n";
		return;
	}
	while(!fileIn.eof())
	{
		bool endF = false;
		while(!fileIn.eof() || endF)
		{
			char* temp = NULL;
			char* temp2 = NULL;
			extractLine(temp,fileIn);
			int pnum= 0;
			while(temp[0] != '[' && !fileIn.eof())
			{
				delete[] temp;
				extractLine(temp,fileIn);
			}
			makeNumeric(temp);
			pnum = atoi(temp);
			extractLine(temp2,fileIn);
			if(pnum != -1)
			{
				analyzeInputLine(pnum,temp2,words,similes);
			}
			else
			{
				endF = true;
			}
			delete[] temp;
			delete[] temp2;
		}
	}
	fileIn.close();
	cout<<"Closed filein\n";

	ofstream fileout;
	fileout.open(outName);
	if(fileout.is_open())
	{
	printIndex(words,similes,fileout);
	cout<<"Printed index to fileout.\n";
	fileout.close();
	}
	else
	{
	cout<<"File out failed to open\n";
	}
}

int main(int argc, char** argv)
{
	if(argc != 4)
	{
		cout<<"Need 4 command line arguments\n";
		return 0;
	}
	analyzeData(argv);
	return 0;
}
