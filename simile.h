#ifndef SIMILE_H
#define SIMILE_H
#include "wordinfo.h"
#include <iostream>
class simile
{
	public:
	simile(char*, wordinfo&);
	simile(const simile&);
	simile();
	~simile();
	simile& operator<<(int);
	simile& operator=(const simile&);

	char* strVal() const;

	bool operator==(char*);
	bool operator==(const simile&);
	friend std::ostream& operator<<(std::ostream&,const simile&);

	private:
	char* word;
	wordinfo* info;	
};
//#include "simile.cpp"
#endif
