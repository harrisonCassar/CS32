#include "Set.h"  // with ItemType being a type alias for char
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
using namespace std;

bool isValid(string infix); //checking syntax of inputted infix string

int evaluate(string infix, const Set& trueValues, const Set& falseValues, string& postfix, bool& result)
{
	if (!isValid(infix))
		return 1;

	//removing space characters
	for (int i = 0; i < infix.size(); i++)
	{
		if (infix[i] == ' ')
		{
			infix = infix.substr(0, i) + infix.substr(i + 1);
			i--;
		}
	}

	//initialize postfix to empty
	postfix = "";

	//initialize the operator stack to empty
	stack<char> op;

	//infix to postfix conversion step
	for (int i = 0; i < infix.size(); i++)
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
				else
					break;
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
			else if (!trueValues.contains(postfix[i]) && !falseValues.contains(postfix[i]))
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

/*int main()
{
	string trueChars = "tywz";
	string falseChars = "fnx";
	Set trues;
	Set falses;
	for (int k = 0; k < trueChars.size(); k++)
		trues.insert(trueChars[k]);
	for (int k = 0; k < falseChars.size(); k++)
		falses.insert(falseChars[k]);

	string pf;
	bool answer;
	assert(evaluate("w| f", trues, falses, pf, answer) == 0 && pf == "wf|" &&  answer);
	assert(evaluate("y|", trues, falses, pf, answer) == 1);
	assert(evaluate("n t", trues, falses, pf, answer) == 1);
	assert(evaluate("nt", trues, falses, pf, answer) == 1);
	assert(evaluate("()", trues, falses, pf, answer) == 1);
	assert(evaluate("y(n|y)", trues, falses, pf, answer) == 1);
	assert(evaluate("t(&n)", trues, falses, pf, answer) == 1);
	assert(evaluate("(n&(t|7)", trues, falses, pf, answer) == 1);
	assert(evaluate("", trues, falses, pf, answer) == 1);
	assert(evaluate("f  |  !f & (t&n) ", trues, falses, pf, answer) == 0 && pf == "ff!tn&&|" && !answer);
	assert(evaluate(" x  ", trues, falses, pf, answer) == 0 && pf == "x" && !answer);
	trues.insert('x');
	assert(evaluate("((x))", trues, falses, pf, answer) == 3);
	falses.erase('x');
	assert(evaluate("((x))", trues, falses, pf, answer) == 0 && pf == "x"  &&  answer);
	trues.erase('w');
	assert(evaluate("w| f", trues, falses, pf, answer) == 2);
	falses.insert('w');
	assert(evaluate("w| f", trues, falses, pf, answer) == 0 && pf == "wf|" && !answer);
	cout << "Passed all tests" << endl;
}*/

//implementation for isValid syntax-checking helper function for infix expressions
bool isValid(string infix)
{
	if (infix == "")
		return false;

	//removing space characters
	for (int i = 0; i < infix.size(); i++)
	{
		if (infix[i] == ' ')
		{
			infix = infix.substr(0, i) + infix.substr(i + 1);
			i--;
		}
	}

	//checking the front and the end for invalid locations of '|' and '&'
	if (infix[0] == '&' || infix[0] == '|' || infix[infix.size() - 1] == '&' || infix[infix.size() - 1] == '|')
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
			if (infix[i] == infix[i - 1])
				return false;
		}

		//if first character in pair as '!'
		if (infix[i - 1] == '!' && (infix[i] == '&' || infix[i] == '|'))
			return false;

		//if first character in pair is '|' or '&'
		if (infix[i - 1] == '|' || infix[i - 1] == '&')
		{
			if (infix[i] == '&' || infix[i] == '|' || infix[i] == ')')
				return false;
		}

		//if first character in pair is '('
		if (infix[i - 1] == '(')
		{
			if (infix[i] == '|' || infix[i] == '&')
				return false;
		}

		//if first character in pair is ')'
		if (infix[i - 1] == ')')
		{
			if (infix[i] == '!')
				return false;
		}
	}

	return true;
}