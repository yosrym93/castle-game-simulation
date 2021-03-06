#pragma once
#include <iostream>
#include "..\Exceptions\PrecondViolatedExcep.h"
using namespace std;
template <class T>
class Array
{
	T** arr;								//Array of pointers to Template.
	int size;								//Array size.
	int capacity;							//Array capacity.
	void swap(T*&f, T*&s);					//Swaps two elements in sorting.
	void quickSort(int start, int pivot);	//Sorts using quicksort technique.
	void updateCapacity();					//Adjusts array's capacity based on needed size.
	void reverseOrder();					//Flips the array (reverses its order)

public:
	Array();								//Constructor for the array.
	int getCount() const;					//Returns size.
	void insert(T* x);						//Adds new element to the array.
	void sort();							//Sorts the array.
	bool remove(T*);						//Removes a specific pointer from the array.
	void clear();							//Clears and deletes all the pointers from the array.
	bool isEmpty();							//Checks whether the array is empty.
	void importOther(Array&);				//Empties another array in the current array
	T* Export();							//Returns the last element then removes it from the list
	T* pickRand();							//Returns a random enemy from the array or NULL if it's empty.
	T* get(int) throw (PrecondViolatedExcep);//Gets an item using it's index if it exists.

	template<typename S>
	void condtionalRemove(bool (S::*conditionFn)());	//traverses through the list and removes an element if conditionFn is true
														//(without deletion)

	template<typename S>
	void condtionalRemove(bool (S::*conditionFn)(T*), S &fnCaller);		//traverses through the list and removes an element if conditionFn
																		//is true (without deletion), func is called from fnCaller
	
	template<typename S>
	void sort(double (S::*sortFn)());						//Sorts elements according to the value of sortFn (ascending)

	template<typename S>
	void sortDesc(double (S::*sortFn)());						//Sorts elements according to the value of sortFn (descending)

	template<typename S>
	void quickSort(int start, int pivot, double (S::*sortFn)());	//Sorts elements according to the value of sortFn (ascending).

	template<typename S>
	void traverse(void (S::*func)());				//traverses through the list and calls a function for each object

	template<typename S>
	void traverse(void (S::*func)(T*), S &fnCaller);	//traverses through the list and calls a function from object fnCaller
														//that takes an element in the list as its parameter

	template<typename S>
	void traverse(void (S::*func)(T*), S &fnCaller, int n);	//traverses through the first n elements and calls a function from
															//object fnCaller that takes an element in the list as its parameter

	template<typename S1, typename S2>
	void traverse(void (S1::*func)(S2), S2 &fnParameter);	//traverses through the list and calls a function from each element
															//that takes fnParameter in the list as its parameter

	~Array();
};


template <class T>
Array<T>::Array()
{
	arr = nullptr;
	size = 0;
	capacity = 0;
}

template<class T>
void Array<T>::swap(T*&f, T*&s)
{
	T* temp = f;
	f = s;
	s = temp;
}

template<class T>
T* Array<T>::pickRand()
{
	if (size == 0)
		return nullptr;
	return arr[rand() % size];
}
template<class T>
void Array<T>::quickSort(int start, int pivot)
{
	if (start >= pivot)
		return;
	int current = start;
	int wall = start;
	while (current != pivot)
		if (*arr[current] > *arr[pivot])
		{
			current++;
		}
		else
		{
			swap(arr[current], arr[wall]);
			current++;
			wall++;
		}
	swap(arr[wall], arr[pivot]);
	quickSort(start, wall - 1);
	quickSort(wall + 1, pivot);

}
template<class T>
void Array<T>::updateCapacity()
{
	if (size == capacity)
		if (capacity == 0)
		{
			capacity = 1;
			arr = new T*[capacity];
		}
		else
		{
			capacity *= 2;
			T** temp = arr;
			arr = new T*[capacity];
			for (int i = 0; i < size; i++)
			{
				arr[i] = temp[i];
			}
			delete[]temp;

		}
}

template <class T>
void Array<T>::reverseOrder() {
	for (int i = 0; i < size / 2; i++) {
		swap(arr[i], arr[size - 1 - i]);
	}
}

template <class T>
int Array<T>::getCount() const
{
	return size;
}


template<class T>
void Array<T>::insert(T * x)
{
	updateCapacity();
	arr[size] = x;
	size++;
}

template<class T>
void Array<T>::sort()
{
	quickSort(0, size - 1);
}

template<class T>
bool Array<T>::remove(T *ptr)
{
	T*temp;
	for (int i = 0; i < size; i++)
	{
		if (ptr == arr[i])
		{
			temp = ptr;
			swap(arr[i], arr[size - 1]);
			size--;
			delete temp;
			temp = nullptr;
			return true;
		}
	}
	return false;
}

template<class T>
void Array<T>::clear()
{
	if (arr) {
		for (int i = 0; i < size; i++)
			delete arr[i];

		delete []arr;
		arr = nullptr;
	}
	size = 0;
	capacity = 0;
}

template<class T>
bool Array<T>::isEmpty()
{
	return (size == 0);
}

template<class T>
inline void Array<T>::importOther(Array &other)
{
	for (int i = 0; i < other.size;)
		insert(other.Export());
}

template<class T>
inline T * Array<T>::Export()
{
	if (size == 0)
		return NULL;
	T* exported = arr[size - 1];
	size--;
	return exported;
}

template<class T>
T* Array<T>::get(int ind) throw(PrecondViolatedExcep)
{
	if (ind >= size || ind < 0)
	{
		string error = "get() called with an invalid index.";
		throw (new PrecondViolatedExcep(error));
	}
	else return arr[ind];
}

//traverses through the list and removes an element if conditionFn is true (without deletion)
template<typename T>
template<typename S>
void Array<T>::condtionalRemove(bool(S::* conditionFn)())
{
	for (int i = 0; i < size; i++)
	{
		if ((arr[i]->*conditionFn)())
		{
			swap(arr[i], arr[size - 1]);
			i--;
			size--;
		}
	}
}

//traverses through the list and removes an element if conditionFn is true (without deletion), conditionFn is called from fnCaller
template<typename T>
template<typename S>
void Array<T>::condtionalRemove(bool (S::*conditionFn)(T*), S &fnCaller)
{
	for (int i = 0; i < size; i++)
	{
		if ((fnCaller.*conditionFn)(arr[i]))
		{
			swap(arr[i], arr[size - 1]);
			size--;
			i--;
		}
	}
}

//Sorts elements according to the value of sortFn (ascending)
template<typename T>
template<typename S>
void Array<T>::sort(double (S::*sortFn)())
{
	quickSort(0, size - 1, sortFn);
}

//Sorts elements according to the value of sortFn (descending)
template<typename T>
template<typename S>
void Array<T>::sortDesc(double (S::*sortFn)()) {
	quickSort(0, size - 1, sortFn);
	reverseOrder();
}

//Sorts elements according to the value of sortFn (ascending) using quicksort.
template<typename T>
template<typename S>
void Array<T>::quickSort(int start, int pivot, double (S::*sortFn)())
{
	if (start >= pivot)
		return;
	int current = start;
	int wall = start;
	while (current != pivot)
		if ((arr[current]->*sortFn)() > (arr[pivot]->*sortFn)())
		{
			current++;
		}
		else
		{
			swap(arr[current], arr[wall]);
			current++;
			wall++;
		}
	swap(arr[wall], arr[pivot]);
	quickSort(start, wall - 1, sortFn);
	quickSort(wall + 1, pivot, sortFn);

}

//traverses through the list and calls a function for each object
template <typename T>
template <typename S>
void Array<T>::traverse(void (S::*func)())
{
	for (int i = 0; i < size; i++)
		(arr[i]->*func)();

}

//traverses through the list and calls a function from object fnCaller
//that takes an element in the list as its parameter
template <typename T>
template <typename S>
void Array<T>::traverse(void (S::*func)(T*), S &fnCaller) {
	traverse(func, fnCaller, size);
}

//traverses through the first n elements and calls a function from object fnCaller
//that takes an element in the list as its parameter
template <typename T>
template <typename S>
void Array<T>::traverse(void (S::*func)(T*), S &fnCaller, int n) {
	if (n > size)
		n = size;
	for (int i = 0; i < n; i++)
		(fnCaller.*func)(arr[i]);
}

//traverses through the list and calls a function from each element
//that takes fnParameter in the list as its parameter
template <typename T>
template<typename S1, typename S2>
void Array<T>::traverse(void (S1::*func)(S2), S2 &fnParameter) {
	for (int i = 0; i < size; i++)
		(arr[i]->*func)(fnParameter);
}

template<class T>
Array<T>::~Array()
{
	clear();
}