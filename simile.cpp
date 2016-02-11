#include "simile.h"
#include <cstring>
#include <iostream>

using std::cout;

simile::simile(char* iword, wordinfo &iwordinfo)
{
	word = new char[strlen(iword)+1];
	for(int i = 0; i < strlen(iword); i++)
	{
		word[i] = iword[i];
	}
	word[strlen(iword)] = '\0';
	info = &iwordinfo;
}
simile& simile::operator=(const simile& tocop)
{	
	if(word)
	{
		delete[] word;
	}
	word = new char[strlen(tocop.word)+1];
	for(int i = 0; i < strlen(tocop.word)+1; i++)
	{
		word[i] = tocop.word[i];
	}
	info = tocop.info;
	return *this;
}
simile::simile(const simile& tocop)
{
	word = new char[strlen(tocop.word)+1];
	for(int i = 0; i < strlen(tocop.word)+1; i++)
	{
		word[i] = tocop.word[i];
	}
	info = tocop.info;
}

simile::simile()
{
	 word = NULL;
	 info = NULL;
}

simile::~simile()
{
	if(word != NULL)
	{
		delete[] word;
		word = NULL;
	}
}

simile& simile::operator<<(int topush)
{
	if(info != NULL)
	{
		*info<<topush;
	}
	return *this;
}

std::ostream& operator<<(std::ostream& os, const simile& toprint)
{
	os<<toprint.word<<": see "<<toprint.info->getword()<<'\n';	
	return os;
}

char* simile::strVal() const
{
	char* toret = new char[strlen(word)+8+strlen(info->getword())];
	for(int i = 0; i < strlen(word); i++)
	{
		toret[i] = word[i];
	}
	for(int i = 0; i < 6; i++)
	{
	toret[strlen(word)+i] = ": see "[i];
	}
	for(int i = 0; i < strlen(info->getword());i++)
	{
		toret[strlen(word)+6+i] = info->getword()[i];	
	}
	toret[strlen(word)+strlen(info->getword())+6]='\n';
	toret[strlen(word)+strlen(info->getword())+7] = '\0';
	return toret;
}

bool simile::operator==(char* toCheck)
{
	bool toret = false;
	if(std::strcmp(word,toCheck)==0)
	{
		return true;
	}
}
bool simile::operator==(const simile& toCheck)
{
	return std::strcmp(word,toCheck.word)==0;
}
