#pragma once
#include "Node.h"
#include "..\Exceptions\PrecondViolatedExcep.h"
template <typename T>
class List {
	Node<T>* head;
	Node<T>* tail;
	int count;
public:
	List(); 
	void push(const T&);							//pushes an item to the end of the list
	bool remove(const T&);							//removes an item by its value, returns false if value not in the list
	bool remove(int pos);							//removes an item by its position, returns false if position is out of range
	T get(int pos) throw (PrecondViolatedExcep);	//returns an item at a certain position,  
	void importOther(List&);						//Empties another array in the current array
	T Export();										//Returns the last element then removes it from the list
													//throws an exceptions if pos is out of range
	template<typename S>
	void traverse(void (S::*func)());				//traverses through the list and calls a function for each object

	template<typename S>
	void traverse(void (S::*func)(T), S &fnCaller);	//traverses through the list and calls a function from object 
													//fnCaller that takes an element in the list as its parameter

	template<typename S>
	void traverse(void (S::*func)(T), S &fnCaller, int n);	//traverses through the first n elements and calls a function from
															//object fnCaller that takes an element in the list as its parameter

	template<typename S1, typename S2>
	void traverse(void (S1::*func)(S2), S2 &fnParameter);	//traverses through the list and calls a function from each element
															//that takes fnParameter in the list as its parameter

	template<typename S>
	void condtionalRemove(bool (S::*conditionFn)());		//traverses through the list and removes an element if conditionFn
															//is true (without deletion)

	template<typename S>
	void condtionalRemove(bool (S::*conditionFn)(T), S &fnCaller);		//traverses through the list and removes an element if conditionFn
																		// is true (without deletion), func is called from fnCaller

	void clear();									//deletes all items in the list
	bool isEmpty() const;
	int getCount() const;

	T pickRand();								//picks a random element and kill it(by setting the health = 0), for phase 1

	~List();
};


/*********************************************************************************************************/
/******************************************** Implementations ********************************************/
/*********************************************************************************************************/

template <typename T>
List<T>::List() {
	head = nullptr;
	tail = nullptr;
	count = 0;
}

//pushes an element to the end of the list
template <typename T>
void List<T>::push(const T& newItem) {
	Node<T>* newNode = new Node<T>(newItem);
	if (head == nullptr) { //empty queue
		head = newNode;
		tail = newNode;
		count++;
	}
	else {
		tail->setNext(newNode);
		tail = tail->getNext();
		count++;
	}
}
//removes an element by its value, returns true if found and removed, otherwise false.
template <typename T>
bool List<T>::remove(const T& val) {
	Node<T>* tempDeleted;
	while (head != nullptr && head->getData() == val) {
		tempDeleted = head;
		head = head->getNext();
		delete tempDeleted;
		count--;
	}

	if (head == nullptr) return;

	Node<T>* ptr = head;
	bool found = false;

	while (ptr->getNext() != NULL) {
		if (ptr->getNext()->getData() == val) {
			tempDeleted = ptr->getNext();
			ptr->setNext(tempDeleted->getNext());
			delete tempDeleted;
			found = true;
			count--;
		}
		else {
			ptr = ptr->getNext();
		}
	}
	return found;
}
//removes an element by its position (starts at 0), returns false if position is out of range
template<typename T>
bool List<T>::remove(int pos) {
	if (pos < 0 || pos >= count) 
		return false;
	else if (pos == 0)
	{
		Node<T>*temp = head;
		head = head->getNext();
		delete temp;
		count--;
		return true;
	}
	Node<T>* ptr = head;
	for (int i = 0; i < pos - 1; i++)
		ptr = ptr->getNext();
	Node<T>* tempDeleted = ptr->getNext();
	ptr->setNext(tempDeleted->getNext());
	delete tempDeleted;
	count--;
	return true;
}
//gets an element by its position (starting 0), throws an exception if position is out of range
template <typename T>
T List<T>::get(int pos) {
	if (pos < 0 || pos >= count) {
		string message = "get() called with a pos out of range";
		throw (new PrecondViolatedExcep(message));
	}
	Node<T>* ptr = head;
	for (int i = 0; i < pos; i++)
		ptr = ptr->getNext();
	return ptr->getData();
}

template<typename T>
inline void List<T>::importOther(List &other)
{
	while (!other.isEmpty())
		push(other.Export());
}

template<typename T>
inline T List<T>::Export()
{
	if (!head) 
	{
		string message = "Export called for an empty list";
		throw (new PrecondViolatedExcep(message));
	}
	Node<T>*temp = head;
	if (tail == head)
		tail = head->getNext();
	head = head->getNext();
	T exported = temp->getData();
	delete temp;
	count--;
	return exported;
}

//traverses through the list and calls a function for each object
template <typename T>
template <typename S>
void List<T>::traverse(void (S::*func)()) {
	Node<T>* ptr = head;
	while(ptr != nullptr) {
		(ptr->getData()->*func)();
		ptr = ptr->getNext();
	}
}

//traverses through the list and calls a function from
//object fnCaller that takes an element in the list as its parameter
template <typename T>
template <typename S>
void List<T>::traverse(void (S::*func)(T), S &fnCaller) {
	Node<T>* ptr = head;
	while (ptr != nullptr) {
		(fnCaller.*func)(ptr->getData());
		ptr = ptr->getNext();
	}
}
//traverses through the first n elements and calls a function from
//object fnCaller that takes an element in the list as its parameter
template <typename T>
template <typename S>
void List<T>::traverse(void (S::*func)(T), S &fnCaller, int n) {
	Node<T>* ptr = head;
	if (n > count)
		n = count;
	int i = 0;
	while (ptr != nullptr && i < n) {
		(fnCaller.*func)(ptr->getData());
		ptr = ptr->getNext();
		i++;
	}
}


//traverses through the list and calls a function from each element
//that takes fnParameter in the list as its parameter
template<typename T>
template<typename S1, typename S2>
void List<T>::traverse(void (S1::*func)(S2), S2 &fnParameter) {
	Node<T>* ptr = head;
	while (ptr != nullptr) {
		(ptr->getData()->*func)(fnParameter);
		ptr = ptr->getNext();
	}
}


//traverses through the list and removes an element if conditionFn is true (without deletion)
template<typename T>
template<typename S>
void List<T>::condtionalRemove(bool(S::* conditionFn)())
{
	Node<T>* temp;
	while (head != nullptr && (head->getData()->*conditionFn)()) {
		if (tail == head)
			tail = head->getNext();
		head = head->getNext();
		count--;
	}

	if (head == nullptr) return;

	Node<T>* ptr = head;
	bool found = false;

	while (ptr->getNext() != NULL) {
		if ((ptr->getNext()->getData()->*conditionFn)()) {
			temp = ptr->getNext();
			if (tail == temp)
				tail = ptr;
			ptr->setNext(temp->getNext());
			count--;
		}
		else {
			ptr = ptr->getNext();
		}
	}
}

//traverses through the list and removes an element if func is true (without deletion), conditionFn is called from fnCaller
template<typename T>
template<typename S>
void List<T>::condtionalRemove(bool (S::*conditionFn)(T), S &fnCaller) {
	Node<T>* temp;
	while (head != nullptr && (fnCaller.*conditionFn)(head->getData())) {
		if (tail == head)
			tail = head->getNext();
		head = head->getNext();
		count--;
	}

	if (head == nullptr) return;

	Node<T>* ptr = head;
	bool found = false;

	while (ptr->getNext() != NULL) {
		if ((fnCaller.*conditionFn)(ptr->getNext()->getData())) {
			temp = ptr->getNext();
			if (tail == temp)
				tail = ptr;
			ptr->setNext(temp->getNext());
			count--;
		}
		else {
			ptr = ptr->getNext();
		}
	}
}

//deletes all elements in the list
template <typename T>
void List<T>::clear() {
	Node<T>* temp;
	while (head != nullptr) {
		temp = head;
		head = head->getNext();
		delete temp;
	}

	count = 0;
	head = nullptr;
	tail = nullptr;
}
//returns the number of elements in the list
template<typename T>
int List<T>::getCount() const {
	return count;
}
//is the list empty?
template<typename T>
bool List<T>::isEmpty() const {
	if (head == nullptr)
		return true;
	return false;
}
//picks a random element from the list, throws an exception if it's empty
template<typename T>
T List<T>::pickRand() {
	if (count == 0) {
		string message = "pickRand() called with an empty list";
		throw (new PrecondViolatedExcep(message));
	}
	else {
		return get(rand() % count);
	}
}

template <typename T>
List<T>::~List() {
	clear();
}

