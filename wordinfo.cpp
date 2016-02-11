#include "wordinfo.h"
#include <cstring>
#include "simile.h"
#include <iostream>

//basic constructor, only takes a word as a parameter.
wordinfo::wordinfo(const wordinfo& toCopy)
{
	if(this != &toCopy)
	{
		word = new char[strlen(toCopy.word)+1];
		for(int i = 0; i < strlen(toCopy.word); i++)
		{
			word[i] = toCopy.word[i];
		}
		word[strlen(toCopy.word)] = '\0';
		maxpages = toCopy.maxpages;
		numpages = toCopy.numpages;
		pagenums = new int[maxpages];
		numsimilies = toCopy.numsimilies;
		if(similies != NULL)
		{
			similies = new char*[numsimilies];
			for(int i = 0; i < numsimilies; i++)
			{
				similies[i] = toCopy.similies[i];
			}
		}
		for(int i = 0; i < numpages; i++)
		{
			pagenums[i] = toCopy.pagenums[i];
		}
	}
}

wordinfo::wordinfo(char* iword)
{
	word = new char[strlen(iword)+1];
	for(int i = 0; i < strlen(iword);i++)
	{
		word[i] = iword[i];	
	}
	word[strlen(iword)] = '\0';
	numpages = 0;
	maxpages = 50;
	numsimilies= 0;
	similies = NULL;
	pagenums = new int[50];
	pagenums[0] = 0;
}

wordinfo::wordinfo()
{
	similies = NULL;
	word = new char[1];
	numpages = 0;
	maxpages = 0;
	numsimilies = 0;
	pagenums = NULL;
}

//copy constructor
wordinfo& wordinfo::operator=(const wordinfo &toCopy)
{
	if(this != &toCopy)
	{
		if(pagenums != NULL)
		{
			delete[] pagenums;
		//	pagenums = NULL;
		}
		if(word != NULL)
		{
			delete[] word;
		//	word = NULL;
		}
		word = new char[strlen(toCopy.word)+1];
		for(int i = 0; i < strlen(toCopy.word); i++)
		{
			word[i] = toCopy.word[i];
		}
		word[strlen(toCopy.word)] = '\0';
		maxpages = toCopy.maxpages;
		numpages = toCopy.numpages;
		pagenums = new int[maxpages];
		numsimilies = toCopy.numsimilies;
		if(similies != NULL)
		{
			similies = new char*[numsimilies];
			for(int i = 0; i < numsimilies; i++)
			{
				similies[i] = toCopy.similies[i];
			}
		}
		for(int i = 0; i < numpages; i++)
		{
			pagenums[i] = toCopy.pagenums[i];
		}
	}
	return *this;
}


//overloaded equality operator for type char*
bool wordinfo::operator==(char*& toCheck)
{
	return (std::strcmp(word,toCheck)==0);
}

bool wordinfo::operator==(wordinfo& toCheck)
{
	return (std::strcmp(word,toCheck.word)==0);
}

//operator to insert an int into the wordinfo object.
wordinfo& operator<<(wordinfo& winfo, int topush)
{
	bool add = true;
	for(int i = 0; i < winfo.numpages; i++)
	{
		if(winfo.pagenums[i] ==topush)
		{
			add = false;	
		}
	}
	if(add)
	{
		winfo.pagenums[winfo.numpages] = topush;
		winfo.numpages++;
	}

	//TODO THIS NEEDS TO BE CHECKED AND FIXED IF ITS BROKEN.
	//if the pagenums ptr is too small, resize it.
	if(winfo.numpages >= winfo.maxpages)
	{
		int* tpagenums = new int[winfo.maxpages+50];
		for(int i = 0; i < winfo.maxpages; i++)
		{
			tpagenums[i] = winfo.pagenums[i];
		}
		delete[] winfo.pagenums;
		winfo.pagenums = NULL;
		winfo.pagenums = tpagenums;
		winfo.maxpages+=50;
	}
}
inline void wordinfo::sortNums()
{
	int hold;	
	for(int i = 0; i < numpages-1; i++)
	{
		for(int j = 0; j < numpages-1; j++)
		{
			if(pagenums[j]>pagenums[j+1])
			{
				hold = pagenums[j];
				pagenums[j] = pagenums[j+1];
				pagenums[j+1] = hold;
			}
		}	
	}
}

//operator to print the the wordinfo object to an ostream in the format specified by the project outline.
std::ostream& wordinfo::operator<<(std::ostream &os)
{
	os<<word<<": ";
	sortNums();
	for(int i = 0; i < numpages-1; i++)
	{
		os<<pagenums[i]<<", ";
	}	
	os<<pagenums[numpages-1]<<"\n";
	return os;
}

char* wordinfo::strVal()
{
	sortNums();
	char* toret = new char[strlen(word)+1];
	for(int i = 0; i < strlen(word); i++)
	{
		toret[i] = word[i];
	}
	toret[strlen(word)]='\0';
	return toret;
}

char* wordinfo::getword()
{
	return word;
}

std::ostream& operator<<(std::ostream& os, const wordinfo& toprint)
{
	os<<toprint.word<<": ";
	for(int i = 0; i < toprint.numpages-1; i++)
	{
		os<<toprint.pagenums[i]<<", ";
	}	
	if(toprint.numpages >=1)
	{
	os<<toprint.pagenums[toprint.numpages-1]<<"\n";
	}
	else
	{
		os<<" Not Found\n";
	}
	return os;
}

void wordinfo::addSimile(char* simile)
{
	char** nsimilies = new char*[numsimilies+1];

	for(int i = 0; i < numsimilies; i++)
	{
	nsimilies[i] = similies[i];
	}
	
	nsimilies[numsimilies] = simile;

	numsimilies++;
	if(similies != NULL)
	{
		delete[] similies;
		similies = NULL;
	}
	similies = nsimilies;
}

//deletes dynamically allocated memory
wordinfo::~wordinfo()
{
	if(word != NULL)
	{
	delete[] word;
	word = NULL;
	}
	if(pagenums!= NULL)
	{
	delete[] pagenums;
	pagenums = NULL;
	}
}
