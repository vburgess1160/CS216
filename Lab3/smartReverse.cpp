/* 
 * File: smartReverse.cpp
 * Purpose: provide the implementation of the smartReverse class
 *
 * Author: Victoria Burgess
 *
 */

#include <stack>
#include "smartReverse.h"

// default constructor
smartReverse::smartReverse()
{
	str = "";
}

// constructor: initialize str with ini_str passing as a parameter
smartReverse::smartReverse(string ini_str)
{
	str = ini_str;
}

// return the current value of the private data member: str
string smartReverse::getString() const
{
	return str;
}

// set the value of str to be the passed in parameter input_str
void smartReverse::setString(string input_str)
{
	str = input_str;
}

// return a reversed string from str
// using a loop to implement
// Note that str has not been changed
string smartReverse::rev() const
{
	string rev;
	for (int i=str.length(); i>=0; i--)
	{
		rev = rev + str[i];
	}
	return rev;
}

// return a reversed string from str
// using recursion to implement
// Note that str has not been changed
string smartReverse::rev_recursive() const
{	
	smartReverse to_rev(str);

	if (str.length() == 1)
		return getString();
	else
	{
		to_rev.setString(str.substr(1));
		return to_rev.rev_recursive() + str[0];
	}	
}

// return a reversed string from str
// using a stack to implement
// Note that str has not been changed
string smartReverse::rev_stack() const
{
	stack<char> stck;
	string to_rev = getString();

	for (int i = 0; i < to_rev.length(); i++)
		stck.push(to_rev[i]);
	string rev;
	while (!stck.empty())
	{
		rev = rev + stck.top();
		stck.pop();
	}
	return rev;
}

