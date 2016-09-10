/**Contains the main function for the reverse polish notation calculator. Has most of the code
* that has the error checking, handling of the things that pop off the stack, adding to stack... etc 
 * @author		Johnny Ceja
 * Course		CS 41
 * Created		Sept. 1 2016
 * Source File:	main.cpp
 */
#include <iostream>
#include <stdlib.h>
#include "LinkedList.h"
using namespace std;

int main(void)
{
	LinkedList<string> list; //string and not float since we need to push operator & num onto it
	int nsize = 0, counter = 0; //keep track of floats in stack, counter aids in error correction
	stringstream ss; //converts the float to string
	float answer = 0, temp = 0; //first pop in temp, second on answer so division can work nicely
	const char * c; // for string -> c-string -> ascii conversion
	//bool needStuff = true; // allows for us to not loop if division by 0 is found
	string cache = "empty"; //on the 1/1000000 chance random memory value assigned to this has = string
	bool programTermination = false, error = false;
	char str; 
	int errorCode;
	/**
	* below has 2 big if loops, 1st executes if there is enough numbers in stack
	* to do math in (at least 2 ), does the actual math part of the program
	* below is mainly for accepting input and pushing it to the stack
	*/
	while(!programTermination)
    {
        counter = 0, nsize = 0, errorCode = 0;
        cache = "empty";
        answer = 0, temp = 0;
		error = false;
        while (cache != "=")
        {
                cin >> cache;
                c = cache.c_str();
                if (counter == 0 && cache == "0")
                {
					cin.get(str);
					if (str == '\n')
					{
						error = true;
						programTermination = true;
						cache = "=";
					}
                }
                /*
                    BELOW IF LOOP EXPLANATION
                    condition 1:  44   normal number
                    condition 2: -44   negative number checks second index
                    condition 3: -.44  negative decimal checks third index, negative decimal like -0.44 is covered by 2nd*/
                if ((c[0] >= '0' && c[0] <= '9') ||
                    (c[1] >= '0' && c[1] <= '9') || (c[2] >= '0' && c[2] <= '9')) //easier to do this than == string for all 10 cases
                {
                    ++counter;
                    ++nsize;
                    list.push(cache);
                }
                else if (cache == "+" || cache == "-" || //then checks if entered thing is token
                    cache == "/" || cache == "*")
                {
					if (nsize <= 1)
					{
						error = true;
						errorCode = 1;
					}
                    --counter;
                    list.push(cache);
                }
            if (counter < 0)
            {
				error = true; //can accept all stuff entered just make sure to not print 
				errorCode = 1; //too many operators
            }
			if (counter >= 2 && cache == "=") //if expression terminated (usually this is case when it ends with operator)
			{ //^^ or too many numbers / not enough operators
				error = true;
				errorCode = 2;
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
						errorCode = 3; 
						error = true;
                    }
                }
            }
        }
        if (counter == 1 && !error)
        {
            cout << "ANSWER: " << answer << endl;
        }
        else if (errorCode == 3) 
        {
            cout << "ERROR: DIVIDING BY ZERO" << endl;
        }
        else if (errorCode == 1)
        {
            cout << "TOO MANY OPERATORS / NOT ENOUGH NUMBERS " << endl;
        }
        else if (errorCode == 2)
        {
            cout << "TOO MANY NUMBERS / NOT ENOUGH OPERATORS" << endl;
		}
        while (list.sizeOf() >= 1) //clear stack for next run
        {
            list.pop();
        }
    }
	return 0;
}

