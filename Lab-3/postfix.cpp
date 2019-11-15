#include "postfix.h"
#include <vector>
#include <stack>
#include <iostream>

using namespace std;

bool TPostfix::IsOperator(char v)
{
	if (v == '~' || v == '-' || v == '+' || v == '/' || v == '*' || v == '^' || v == '(' || v == ')')
		return true;
	else
		return false;
}
bool TPostfix::IsNumeral(char v)
{
	if (int(v) >= 48 && int(v) <= 57)
		return true;
	return false;
}

bool TPostfix::CheckOperations()
{
	for(int i = 0; i < infix.size(); i++)
		if(!IsNumeral(infix[i]) && !IsOperator(infix[i]))
			return false;
	int Operands = 0, Operations = 0;
	for (int i = 0; i < infix.size(); i++)
	{
		if (infix[i] == '(' || infix[i] == ')')
		{
			i++;
			if (i == infix.size())
				break;
		}

		if (infix[i] == '-' || infix[i] == '+' || infix[i] == '/' || infix[i] == '*' || infix[i] == '^')
			Operations++;

		if (!IsOperator(infix[i]))
		{
			while (!IsOperator(infix[i]))
			{
				i++;
				if (i == infix.size())
					break;
			}
			i--;
			Operands++;
		}
	}
	if (Operands == Operations + 1)
		return true;
	else return false;
}

bool TPostfix::CheckBrackets()
{
	int LeftBrackets = 0, RightBrackets = 0;
	for (int i = 0; i < infix.size(); i++)
	{
		if (infix[i] == '(')
			LeftBrackets++;
		else if (infix[i] == ')')
			RightBrackets++;
		if (RightBrackets > LeftBrackets)
			throw "Error Brackets";
	}
	if (LeftBrackets == RightBrackets)
		return true;
	else return false;
}

int TPostfix::Priority(char a, char b)
{
	if (a == '~')
		return 1;
	if (b == '~')
		return -1;
	if (a == '^' && b != '~')
		return 1;
	if (b == '^' && a != '~')
		return -1;
	if ((a == '*' || a == '/') && (b == '*' || b == '/') || (a == '+' || a == '-') && (b == '+' || b == '-'))
		return 0;
	if ((a == '*' || a == '/') && (b == '+' || b == '-'))
		return 1;
	if ((a == '+' || a == '-') && (b == '*' || b == '/'))
		return -1;
	throw "not operation";
}

void TPostfix::SplitStr(string& str)
{
	if (str.empty())
		return;
	if (str.back() != ' ')
		str += ' ';
}

string TPostfix::ToPostfix()
{
	if (!CheckBrackets())
		throw "Error Brackets";
	for (int j = 0; j < infix.size(); j++)
	{
		if (infix[0] == '-')
			infix[0] = '~';
		if (infix[j] == '-' && (infix[j-1] == '(' || infix[j - 1] == '~'))
			infix[j] = '~';
	}
	int count = -1;
	stack<char> Oper;
	for (int i = 0; i < infix.size(); i++)
	{
		if (IsOperator(infix[i]))
		{
			if ((Oper.empty() || infix[i] == '(') && infix[i]!='~')
			{
				if (infix[i] != '(')
					SplitStr(postfix);
				Oper.push(infix[i]);
				count++;
				continue;
			}
			else if ((Oper.empty() || Oper.top() == '~') && infix[i] == '~')
			{
				Oper.push(infix[i]);
				count++;
				continue;
			}
			else if (infix[i] == ')')
			{
				while (Oper.top() != '(')
				{
					SplitStr(postfix);
					postfix += Oper.top();
					Oper.pop();
					count--;
				}
				Oper.pop();
				count--;
			}
			else if ((Oper.top()) == '(' || Priority(infix[i], Oper.top()) == 1)
			{
				Oper.push(infix[i]);
				SplitStr(postfix);
				count++;
			}
			else if (Priority(infix[i], Oper.top()) == -1)
			{
				SplitStr(postfix);
				while (!(Oper.empty()))
				{
					if (Oper.top() == '(')
						break;
					postfix += Oper.top();
					Oper.pop();
					SplitStr(postfix);
					count--;
				}
				Oper.push(infix[i]);
				count++;
			}
			else if (Priority(infix[i], Oper.top()) == 0)
			{
				SplitStr(postfix);
				postfix += Oper.top();
				Oper.pop();
				Oper.push(infix[i]);
				SplitStr(postfix);
			}
		}
		else
			postfix += infix[i];
		if (i == infix.size() - 1)
		{
			for (count; count >= 0; count--)
			{
				SplitStr(postfix);
				postfix += Oper.top();
				Oper.pop();
			}
		}
	}
	return postfix;
}

double TPostfix::Calculate()
{
	if (!CheckOperations() || postfix == "")
		throw "Error Operand";
	stack<double> Res;
	string str;
	for (int i = 0; i < postfix.size(); i++)
	{
		if (postfix[i] == ' ')
			continue;
		if (!IsOperator(postfix[i]))
		{
			while (postfix[i] != ' ')
			{
				str += postfix[i];
				i++;
			}
			Res.push(atof(str.c_str()));
			str = "";
		}
		else
		{
			if (postfix[i] == '~')
			{
				double a = Res.top();
				Res.pop();
				Res.push(-a);
				continue;
			}
			double a = Res.top();
			Res.pop();
			double b = Res.top();
			Res.pop();
			if (postfix[i] == '+')
				Res.push(b + a);
			else if (postfix[i] == '-')
				Res.push(b - a);
			else if (postfix[i] == '*')
				Res.push(b * a);
			else if (postfix[i] == '/')
			{
				if (a == 0.0)
					throw "Error Division";
				Res.push(b / a);
			}
			else if (postfix[i] == '^')
				Res.push(pow(b,a));
		}
	}
	return Res.top();
}