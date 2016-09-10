/**Implementation of the functions said to be implemetned in the .h file, nothing exclusive to the
* RPN calculator is here.
 * @author		Johnny Ceja
 * Course		CS 41
 * Created		Sept. 1 2016
 * Source File:	LinkedList.cpp
 */
#include <iostream>
using namespace std;
/**Implementation of the functions said to be implemetned , nothing exclusive to the
* RPN calculator is here.
*/
template <typename T>
void LinkedList<T>::printAll()
{
    Node *ptr = head;
	while(ptr)
	{
		cout << ptr->data << " -> ";
		ptr = ptr->next;
	}
	cout << "END\n";
}

/**
*Returns the size of the linked list since function is conventionally included in linked lists.
*/
template <typename T>
int LinkedList<T>::sizeOf()
{
	return size;
}
/**
* Pops the top of the stack and returns it as a string sicne that is how it was entered.
*/
template <typename T>
string LinkedList<T>::pop()
{
	string tempStr;
	Node *ptr = head;
	Node *tempPtr;
	if(size >= 2) //since we need ptr two behind the last node, do this  normal thing if size > 2
	{
		while(ptr->next->next != 0)
		{
			ptr = ptr->next;
		}
		tempStr = ptr->next->data;
		tempPtr = ptr->next;
		ptr->next = 0;
		--size;
		delete tempPtr;
	}
	else //if link size < 2 the above would crash the program since it would try to access random memory
	{
		--size;
		tempStr = ptr->data;
		ptr->next = 0;
		ptr->data = "";
		return tempStr;
	}
}
/**
*Adds node to the end of the list like a stack would.
*/
template <typename T>
void LinkedList<T>::push(T num)
{

	Node *ptr = head;
	if(size == 0) //first thing entered is initially pointed by the ptr, just enter data directly
	{
		ptr->data = num;
	}
	else
	{
		while (ptr->next) //in order to get ptr to point to last node
		{
			ptr = ptr->next;
		}
		if(ptr->next == 0) //once it is pointing at last node...
		{
			Node *newNode = new Node;
			newNode->data = num;
			newNode->next = ptr->next;
			ptr->next = newNode;
		}
	}
	++size;
}
/**
*Destructor to remove all the nodes once the program ends.
*/
template <typename T> //if linkedlist object is created without this... error
LinkedList<T>::~LinkedList()
{
	Node *ptr = head;
	Node *ptr2;
	while(ptr != 0)
	{
		ptr2 = ptr;
		ptr = ptr->next;
		delete ptr2;
	}
	size = 0;
}
