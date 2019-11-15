#include <string>
#include <stack>

using namespace std;

class TPostfix
{
	string infix;
	string postfix;

	bool IsOperator(char v);
	bool IsNumeral(char v);
	bool CheckOperations();
	bool CheckBrackets();
	void SplitStr(string& str);
	int Priority(char a, char b);
public:
	string ToPostfix();
	double Calculate();
	string GetInfix() { return infix; }
	string GetPostfix() { return postfix; }
	TPostfix(string tmp = "")
	{
		infix = tmp;
		postfix = "";
	}
	TPostfix(TPostfix& v)
	{
		infix = v.infix;
		postfix = v.postfix;
	}
};