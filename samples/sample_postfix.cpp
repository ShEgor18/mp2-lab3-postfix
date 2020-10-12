#include <iostream>
#include <string>
#include "postfix.h"


using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	string expression;
	cout << "Введите арифметическое выражение: ";
	cin >> expression;
	try
	{
		TPostfix postfix(expression);
		cout << "Арифметическое выражение: " << postfix.GetInfix() << endl;
		postfix.ToPostfix();
		cout << "Постфиксная форма: " << postfix.GetPostfix() << endl;
		cout << "Резульат: " << postfix.Calculate() << endl;
	}
	catch (const char* s)
	{
		cout << s << endl;
	}
	system("pause");
	return 0;
}
