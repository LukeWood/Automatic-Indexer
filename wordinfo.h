#ifndef WORDINFO_H
#define WORDINFO_H
#include <iostream>
class wordinfo
{
	friend wordinfo& operator<<(wordinfo&,int);
	public:
		wordinfo(char* iword);
		wordinfo();
		wordinfo(const wordinfo&);
		~wordinfo();
		void addSimile(char*);
		bool operator==(wordinfo&);
		bool operator==(char*&);
		wordinfo& operator=(const wordinfo&);
		char* getword();
		char* strVal();
		std::ostream& operator<<(std::ostream&);
		friend std::ostream& operator<<(std::ostream&,const wordinfo&);
	private:
		char* word;

		char** similies;
		int numsimilies;
		int maxsimilies;

		//pagenumber data
		int* pagenums;
		int numpages;
		int maxpages;
		
		inline void sortNums();

};
//#include "wordinfo.cpp"
#endif
