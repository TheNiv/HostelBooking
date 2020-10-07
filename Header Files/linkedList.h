#pragma once
#include "node.h"
#include "Visit.h"
template<typename T>
class LinkedList 
{
public:
	node<T>  *tail, *head;
public:
	LinkedList()
	{
		tail = nullptr;  //Pointing to the first node of the list.
		head = nullptr;  //Pointing to the last node of the list.
	}
	void InsertFirst(T &value)
	{   //inserts the value at the start of the list
		node<T> *temp = new node<T>;
		temp->m_data = &value;
		temp->next = tail;
		tail = temp;
	}
	void InsertLast(T &value) 
	{  // inserts the value at the end of the list
		node<T> *temp = new node<T>;
		temp->m_data = &value;
		head->next = temp;
		head = temp;
	}
	void InsertAfter(node<T>* node1,T &value)  //NOTE: Need the refernce of value so it wont be destroyed after the end of the function.
	{   //inserts the value after the specified node.
		node<T> *temp = new node<T>;
		temp->m_data = &value;
		temp->next = node1->next;
		node1->next = temp;
	}
	void DeleteFirst() 
	{  //Deletes the first node of the list.
		node<T>* temp = tail;
		tail = tail->next;
		delete temp;
	}
	void PrintList()
	{   //prints all the Visits in the list.
		node<T>* tmp = tail;

		while (tmp != nullptr) 
		{
			std::cout << *(tmp->m_data) << std::endl;  // m_data is a pointer to a Visit instance
			tmp = tmp->next;
		}
	}

};