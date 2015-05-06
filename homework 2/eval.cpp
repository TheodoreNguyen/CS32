//Theodore Nguyen 704-156-701 W2015 CS32 homework 2

#include <iostream>
#include <string>
#include <cassert>
#include <stack>
#include <cctype>
using namespace std;

int precedence(char ch)			//assigns precedence to each of the three operators
{
	if (ch == '!')
		return 3;
	else if (ch == '&')
		return 2;
	else if (ch == '|')
		return 1;
	else 
		return -1;
}


int evaluate(string infix, const bool values[], string& postfix, bool& result)
{
	string nospaces = "";				//copies the infix string, except without spaces
	for(int i = 0; i != infix.size(); i++)
		if(infix[i] != ' ')
			nospaces += infix[i];

	//cerr << nospaces << endl;
	if (nospaces == "")			//return if the infix is the empty string
	{
		postfix = "";
		return 1;	
	}


	for(int i = 0; i != nospaces.size(); i++)	//whether or not the string has valid characters: !, &, |, #'s 0-9, or ( and 0.
		if(isdigit(nospaces[i]) || nospaces[i] == '|' || nospaces[i] == '&' || nospaces[i] == '!' ||
		 nospaces[i] == '(' || nospaces[i] == ')');
		else return 1;


	if(nospaces[0] == '|' || nospaces[0] == '&' || nospaces[nospaces.size()-1] == '!' ||
	   nospaces[nospaces.size()-1] == '|' || nospaces[nospaces.size()-1] == '&' ||
	   nospaces[nospaces.size()-1] == '(' || nospaces[0] == ')')
		return 1;		//check if first and last string characters are valid		


	for(int i = 0; i != nospaces.size(); i++)	//checks that, if there is open paren, then there must be a closed parenthesis; if there is none found at we reach the end of the string, return 1
		if(nospaces[i] == '(')
			for(int j = i; j != nospaces.size(); j++)
				if(nospaces[j] == ')')
					break;
				else if(j == nospaces.size() - 1)
					return 1;
	
	//having two operators in a row is invalid, besides the ! operator.
	//having the operator then a parethesis blocking it is also invalid
	for(int i = 1; i != nospaces.size(); i++)
		if(nospaces[i] == '&' || nospaces[i] == '|')
			if(nospaces[i-1] == '&' || nospaces[i-1] == '|' || nospaces[i-1] == '(')
				return 1;
			else if(nospaces[i] == ')' && ( nospaces[i-1] == '&' || nospaces[i-1] == '|' || nospaces[i-1] == '!'))
				return 1; 
	
	
	//no two digits in a row
	for(int i = 1; i != nospaces.size(); i++)
		if(isdigit(nospaces[i]))
			if(isdigit(nospaces[i-1]))
				return 1;
	

	//////////////////////
	//finished checking for conditions
	////////////////////////
	//
	//begin conversion of expression infix -> postfix
	///////////////////

	postfix = "";				//initialize postfix if havent already, initialize stack
	stack<char> operatorStack;
	char ch;
	for(int i = 0; i != nospaces.size(); i++)
	{
		ch = nospaces[i];		//if digit 0-9. adds itself to the postfix
		switch(ch)
		{
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			postfix += ch;
			break;
		case '(':
			operatorStack.push(ch);		//temporarily add the ( before finding )
			break;
		case ')':
			if(postfix.empty()) return 1;
			while(operatorStack.top() != '(')
			{
				postfix += operatorStack.top();		//pops items to the postfix in parenthesis
				operatorStack.pop();
			}
			operatorStack.pop(); //remove the '('
			break;
		case '!':
			operatorStack.push(ch);	//unlike the other operators, must add adjacent to digit, diff case
			break;
		case '&':
		case '|':
			while(!operatorStack.empty() && operatorStack.top() != '(' && operatorStack.top() != ')' &&( precedence(ch) <= precedence(operatorStack.top())))
			{
				postfix += operatorStack.top();
				operatorStack.pop();
			}	
			operatorStack.push(ch);
			break;
		}
	}
	while(!operatorStack.empty())
	{
		postfix += operatorStack.top();
		operatorStack.pop();
	}

//cerr << postfix << endl;


//////////////////////////
//evaluation of postfix expresssion
///////////



	stack<bool> operand;
	for(int i = 0; i != postfix.size(); i++)	
	{
		char ch;
		ch = postfix[i];
		if(ch == '(' || ch == ')') // for some reason i had a parenthesis in the postfix for some cases
			return 1;
		if(isdigit(ch))
			operand.push(values[ch - '0']);
		else if(operand.empty())
			return 1;
		else if (ch == '!')
		{
			bool value = operand.top();
			operand.pop();
			operand.push(!value);
		}
		else if(ch == '&' || ch == '|')
		{
			bool operand2 = operand.top();
			operand.pop();
			bool operand1 = operand.top();
			operand.pop();
			if (ch == '&')
				operand.push(operand1 && operand2);
			else if(ch == '|')
				operand.push(operand1 || operand2);
		}
	}
	bool endvalue = operand.top();
	operand.pop();
	if(!operand.empty())
		return 1;
	result = endvalue;
	return 0;					
}


/*
  int main()
        {
            bool ba[10] = {
            
                true,  true,  true,  false, false, false, true,  false, true,  false
            };
            string pf;
            bool answer;
            assert(evaluate("2| 3", ba, pf, answer) == 0  &&  pf == "23|" &&  answer);
            assert(evaluate("8|", ba, pf, answer) == 1);
            assert(evaluate("4 5", ba, pf, answer) == 1);
            assert(evaluate("01", ba, pf, answer) == 1);
            assert(evaluate("()", ba, pf, answer) == 1);
            assert(evaluate("2(9|8)", ba, pf, answer) == 1);
            assert(evaluate("2(&8)", ba, pf, answer) == 1);
            assert(evaluate("(6&(7|7)", ba, pf, answer) == 1);
            assert(evaluate("4  |  !3 & (0&3) ", ba, pf, answer) == 0
                                   &&  pf == "43!03&&|"  &&  !answer);
            assert(evaluate("", ba, pf, answer) == 1);
            assert(evaluate(" 9  ", ba, pf, answer) == 0  &&  pf == "9"  &&  !answer);
            ba[2] = false;
            ba[9] = true;
            assert(evaluate("((9))", ba, pf, answer) == 0  &&  pf == "9"  &&  answer);
            assert(evaluate("2| 3", ba, pf, answer) == 0  &&  pf == "23|" &&  !answer);
            cout << "Passed all tests" << endl;
        }
*/
