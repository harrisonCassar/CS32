#include "Set.h"  // with ItemType being a type alias for char
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
using namespace std;

bool isValid(string infix); //checking syntax of inputted infix string

//declarations of any additional functions you might have written
  //to help you evaluate an expression

int evaluate(string infix, const Set& trueValues, const Set& falseValues, string& postfix, bool& result)
{
	if (!isValid(infix))
		return false;

	

}
  // Evaluate a boolean expression
  //   If infix is a syntactically valid infix boolean expression whose
  //   only operands are single lower case letters (whether or not they
  //   appear in the values sets), then postfix is set to the postfix
  //   form of the expression.  If not, postfix might or might not be
  //   changed, result is unchanged, and the function returns 1.
  //
  //   If infix is a syntactically valid infix boolean expression whose
  //   only operands are single lower case letters:
  //
  //      If every operand letter in the expression appears in either
  //      trueValues or falseValues but not both, then result is set to the
  //      result of evaluating the expression (using for each letter in the
  //      expression the value true if that letter appears in trueValues or
  //      false if that letter appears in false values) and the function
  //      returns 0.
  //
  //      Otherwise, result is unchanged and the value the function returns
  //      depends on these two conditions:
  //        at least one letter in the expression is in neither the
  //            trueValues nor the falseValues sets; and
  //        at least one letter in the expression is in both the
  //            trueValues and the falseValues set.
  //      If only the first condition holds, the function returns 2; if
  //      only the second holds, the function returns 3.  If both hold
  //      the function returns either 2 or 3 (and the function is not
  //      required to return the same one if called another time with the
  //      same arguments).

bool isValid(string infix)
{	
	//checking the front and the end for invalid locations of '|' and '&'
	if (infix[0] == '&' || infix[0] == '|' || infix[infix.size()-1] == '&' || infix[infix.size()-1] == '|')
		return false;

	//checking for all characters being valid
	for (int i = 0; i < infix.size(); i++)
	{
		switch (infix[i])
		{
			case '&':
			case '|':
			case '!':
			case '(':
			case ')':
				break;
			default:
				if (!isLower(infix[i]))
					return false;
		}
	}

	//checking for parentheses mismatch
	stack<char> paren;

	for (int i = 0; i < infix.size(); i++)
	{
		if (infix[i] == '(')
			paren.push(infix[i]);
		
		if (infix[i] == ')')
		{
			if (!paren.empty())
				paren.pop();
			else
				return false;
		}
	}

	if (!paren.empty())
		return false;

	//checking for invalid operator/letter pair (except for !) next to each other (i.e. ||, or &&, or |&, or (), or aa)
	for (int i = 1; i < infix.size(); i++)
	{
		//if second character is not a character that can have multiple instances next to each other
		if (infix[i] != '!' && infix[i] != '(' && infix[i] != ')')
		{
			if (infix[i] == infix[i-1])
				return false;
		}

		//if first character in pair as '!'
		if (infix[i-1] == '!' && (infix[i] == '&' || infix[i] == '|'))
			return false;

		//if first character in pair is '|' or '&'
		if (infix[i-1] == '|' || infix[i-1] == '&')
		{
			if (infix[i] == '&' || infix[i] == '|' || infix[i] == ')')
				return false;
		}

		//if first character in pair is '('
		if (infix[i-1] == '(')
		{
			if (infix[i] == '|' || infix[i] == '&')
				return false;
		}

		//if first character in pair is ')'
		if (infix[i-1] == ')')
		{
			if (infix[i] == '!')
				return false;
		}
	}
}

// implementations of any additional functions you might have written
//   to help you evaluate an expression
//   a main routine to test your function