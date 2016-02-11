//Sadly I put the full implementation in this class because of the way templates work
//also I figured this file was small enough that it would just be easier to leave it like this.
#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>
using std::cout;
//generic vector class for use in all my of my future projects.
template<typename T> class vector
{
	public:
		void push(T);
		vector<T>();
		~vector<T>();
		T& operator[](int);
		vector<T>& operator=(const vector<T>&);
		int size();
		int find(T&) const;
	private:
		int curr;
		int _size;
		T* data;			
		void resize();
};
//
//CLASS DEFINITION END
//

//
//CLASS IMPLEMENTATION BEGIN
//
 
template<typename T> vector<T>& vector<T>::operator=(const vector<T> &toCopy)
{
	if(this != toCopy)
	{	
		curr = toCopy.curr;
		size = toCopy._size;
		data = new T[size];
		for(int i = 0; i < size; i++)
		{
			data[i] = toCopy[i];
		}
	}
	return *this;
}

template<typename T> int vector<T>::find(T& tofind) const
{
	int toret = -1;
	for(int i = 0; i < curr; i++)
	{
		if(data[i] == tofind)
		{
			toret = i;
		}
	}
	return toret;
}

//getter for size
template<typename T> int vector<T>::size()
{
	return curr;	
}

//operator to get an item at index.
template<typename T> T& vector<T>::operator[](int index)
{
	if(index < curr)
	{
		return data[index];
	}
	else
	{
		return data[0];
	}
}

//constructor.
template<typename T> vector<T>::vector()
{
	curr = 0;
	_size = 50;
	data = new T[_size];
}

//deconstructor to delete dynamic allocations
template<typename T> vector<T>::~vector()
{
	cout<<"Inside vector destructor\n";
	if(data != NULL)
	{
	delete[] data;
	}
	cout<<"Finish vector destructor\n";
}

//basic push function, only really want pushback.
template<typename T> void vector<T>::push(T item)
{
	data[curr] = item;
	curr++;
	if(curr>=_size)
	{
		resize();
	}
}

//private resize function.
template<typename T> void vector<T>::resize()
{
	T* tdata = new T[_size+50];
	for(int i = 0; i < _size; i++)
	{
		tdata[i] = data[i];
	}
	_size +=50;
	delete[] data;
	data = tdata;
}

#endif
