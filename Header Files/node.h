#pragma once
template<typename T>
struct node 
{   //Represents a node of VisitList
	T *m_data;  //A pointer to the data that the node contains.
	node<T> *next;  // A pointer to the node it points to.
	node()
	{
		m_data = nullptr;
		next = nullptr;
	}
	node(T *visit) 
	{
		m_data = visit;
		next = nullptr;
	}
};