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
		return 1;

	//removing space characters
	for (int i = 0; i < infix.size(); i++)
	{
		if (infix[i] == ' ')
		{
			infix = infix.substr(0,i) + infix.substr(i+1);
			i--;
		}
	}

	//initialize postfix to empty
	postfix = "";
	
	//initialize the operator stack to empty
	stack<char> op;

	//infix to postfix conversion step
	for (int i = 0; i< infix.size(); i++)
	{
		switch (infix[i])
		{
			default:
				postfix += infix[i];
				break;
			case '(':
				op.push(infix[i]);
				break;
			case ')':
				// pop stack until matching '('
				while (op.top() != '(')
				{
					postfix += op.top();
					op.pop();
				}
				op.pop(); //remove the '('
				break;
			case '&':
			case '|':
			case '!':
				while (!op.empty() && op.top() != '(')
				{
					int precedenceInfix;
					int precedenceTop;

					if (infix[i] == '!')
						precedenceInfix = 3;
					else if (infix[i] == '&')
						precedenceInfix = 2;
					else if (infix[i] == '|')
						precedenceInfix = 1;

					if (op.top() == '!')
						precedenceTop = 3;
					else if (op.top() == '&')
						precedenceTop = 2;
					else if (op.top() == '|')
						precedenceTop = 1;

					if (precedenceInfix <= precedenceTop)
					{
						postfix += op.top();
						op.pop();
					}
				}

				op.push(infix[i]);
				break;
		}
	}

	while (!op.empty())
	{
		postfix += op.top();
		op.pop();
	}

	//initialize the operator stack to empty
	stack<bool> operand;

	//evaluation of postfix expression
	for (int i = 0; i < postfix.size(); i++)
	{
		if (isalpha(postfix[i]))
		{
			if (trueValues.contains(postfix[i]) && !falseValues.contains(postfix[i]))
				operand.push(true);
			else if (falseValues.contains(postfix[i]) && !trueValues.contains(postfix[i]))
				operand.push(false);
			else if (trueValues.contains(postfix[i]) && falseValues.contains(postfix[i]))
				return 2;
			else
				return 3;

		}
		else
		{
			if (postfix[i] == '!')
			{
				bool temp = operand.top();
				operand.pop();

				operand.push(!temp);
				continue;
			}

			bool operand2 = operand.top();
			operand.pop();

			bool operand1 = operand.top();
			operand.pop();

			if (postfix[i] == '&')
				operand.push(operand1 && operand2);
			else if (postfix[i] == '|')
				operand.push(operand1 || operand2);
		}
	}

	if (operand.size() != 1)
		return 1;

	result = operand.top();

	return 0;
}

bool isValid(string infix)
{	
	//removing space characters
	for (int i = 0; i < infix.size(); i++)
	{
		if (infix[i] == ' ')
		{
			infix = infix.substr(0,i) + infix.substr(i+1);
			i--;
		}
	}

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
				if (!islower(infix[i]))
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