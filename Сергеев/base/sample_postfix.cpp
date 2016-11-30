#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
  string expression;
  double res;

  setlocale(LC_ALL, "Russian");
	  cout << "Введите африфмитическиое выражение" << endl;
	  cin >> expression;
	 TPostfix Postfix(expression);
	 if (Postfix.ErrorChecking())
	 {
		 Postfix.ToPostfix();
		 cout << "Арифметическое выражение: " << Postfix.GetInfix() << endl;
		 cout << "Постфиксная форма: " << Postfix.GetPostfix() << endl;
		 res = Postfix.Calculate();
		 cout << res << endl;
	 }
  return 0;
}
