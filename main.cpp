/**Contains the main function for the reverse polish notation calculator. Has most of the code
* that has the error checking, handling of the things that pop off the stack, adding to stack... etc 
 * @author		Johnny Ceja
 * Course		COMP B12
 * Created		Sept. 1 2016
 * Source File:	main.cpp
 */
#include <iostream>
#include <stdlib.h> //ascii to float function, string to float is not working for me
#include <sstream> //float to string function
#include "LinkedList.h"
using namespace std;

int main(void)
{
	LinkedList<string> list; //string and not float since we need to push operator & num onto it
	int nsize = 0; //keep track of floats in stack
	int counter = 0; //to see if legal operations
	stringstream ss; //converts the float to string
	float answer, temp; //first pop in temp, second on answer so division can work nicely
	const char * c; // for string -> c-string -> ascii conversion
	bool needStuff = true; // allows for us to not loop if division by 0 is found
	string cache = "empty"; //on the 1/1000000 chance random memory value assigned to this has = string
	/*cin >> cache;
	++counter;
	++nsize;*/
	/**
	* below has 2 big if loops, 1st executes if there is enough numbers in stack
	* to do math in (at least 2 ), does the actual math part of the program
	* below is mainly for accepting input and pushing it to the stack
	*/
	while (cache != "=")
	{
		if (counter < 0)
		{
			cache = "="; //if at ANY point it is -1... illegal
			needStuff = false;
		}
		if(nsize >= 2)
		{
			if (cache == "+")
			{
				list.pop();//pops the "+"
				temp = atof((list.pop()).c_str()); // list.pop is string, this is converted to c-string then float
				answer = atof((list.pop()).c_str()) + temp;
				ss.str(""); //if i do not do this and code below the answer is appended to the previous answer
				ss.clear(); // ^^ for example if answer is 12 and previous answer is 9, ss would have 912 and push that to stack
				ss << answer;
				list.push(ss.str()); //push answer back to stack
				--nsize; //in the end stack is 1 less number
			}
			else if (cache == "-")
			{
				list.pop();//pops the "+"
				temp = atof((list.pop()).c_str());
				answer = atof((list.pop()).c_str()) - temp;
				ss.str("");
				ss.clear();
				ss << answer;
				list.push(ss.str());
				--nsize;
			}
			else if (cache == "*")
			{
				list.pop();//pops the "+"
				temp = atof((list.pop()).c_str());
				answer = atof((list.pop()).c_str()) * temp;
				ss.str("");
				ss.clear();
				ss << answer;
				list.push(ss.str());
				--nsize;
			}
			else if (cache == "/")
			{
				list.pop();//pops the "+" //pop this first so we can take out the + ...
				temp = atof((list.pop()).c_str()); //^^so then we can see if the we are dividing by 0...
				if (temp != 0) //if not division by 0...
				{
					answer = atof((list.pop()).c_str()) / temp;
					ss.str("");
					ss.clear();
					ss << answer;
					list.push(ss.str());
					--nsize;
				}
				else //if divison by 0... 
				{
					counter = -1000; ///sentinal value, means division by 0
					cache = "="; //breaks out of the  big while loop
					needStuff = false; // in case division by 0 is in the middle of a math calculation, stop accepting input
				}
			}
		}
		if(needStuff) //2nd big if loop
		{
			cin >> cache;
			c = cache.c_str();
			/*
				FOR BELOW IF LOOP EXPLANATION
				condition 1:  44   normal number
				condition 2: -44   negative number checks second index
				condition 3: -.44  negative decimal checks third index, negative decimal like -0.44 is covered by 2nd*/
			if ((c[0] >= '0' && c[0] <= '9') || 
				(c[1] >= '0' && c[1] <= '9') || (c[2] >= '0' && c[2] <= '9')) //easier to do this than == string for all 10 cases
			{ //also note worthy is this if loop is before the other one because negative number can be mistaken for operation
				++counter;
				++nsize;
				list.push(cache);
			}
			else if (cache == "+" || cache == "-" || //then checks if entered thing is token
				cache == "/" || cache == "*")
			{
				--counter;
				list.push(cache);
			}
		}
	}
	if (counter == 1)
	{
		cout << "ANSWER: " << answer << endl;
	}
	else if (counter == -1000) //this is before < 1 because -1000 is < 1 so it would give wrong error code
	{
		cout << "ERROR: DIVING BY ZERO" << endl;
	}
	else if (counter < 1)
	{
		cout << "TOO MANY OPERATORS / NOT ENOUGH NUMBERS " << endl;
	}
	else if (counter > 1)
	{
		cout << "TOO MANY NUMBERS / NOT ENOUGH OPERATORS" << endl;
	}
	return 0;
}
