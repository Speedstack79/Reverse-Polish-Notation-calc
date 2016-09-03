/**Contains functions to be implemented along with brief description of what each functions
* is supposed to do. Although the calculator does all the calculation with a string, a template
* is used in case I want to add a different data type.
 * @author		Johnny Ceja
 * Course		COMP B12
 * Created		Sept. 1 2016
 * Source File:	LinkedList.h
 */
#include <stdlib.h>
#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

template <typename T> 
class LinkedList
{
private:
	struct Node
	{
		T data; //node will have pointer and space to store data (like all other linked lists)
		Node * next;
	};
	Node * head;


public:
int size;
float sum;
	LinkedList()
	{
		//"dummy" node removes need for some special cases does not store data in itself
		head = new Node;
		head->next = 0;
		size = 0;
		sum = 0;
	}
	~LinkedList();
	std::string pop(); //add to stack
	void push(T num); //since stack removes from top, this will remove only the most recent item
	int sizeOf();
	void printAll(); //for debugging;


};

#include "LinkedList.cpp"
#endif
