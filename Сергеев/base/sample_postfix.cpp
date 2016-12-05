#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
  string expression;
  double res;

  setlocale(LC_ALL, "Russian");
  cout << "                Лабораторная работа №3" << endl;
  cout << "          Вычисление арифметических выражений" << endl;
  cout << endl;
  cout << "Введите африфмитическое выражение" << endl;
  cin >> expression;
  TPostfix Postfix(expression);
  if (Postfix.ErrorChecking())
  {
	  Postfix.ToPostfix();
	  cout << "Арифметическое выражение: " << Postfix.GetInfix() << endl;
	  cout << "Постфиксная форма: " << Postfix.GetPostfix() << endl;
	  res = Postfix.Calculate();
	  cout <<"Ответ:  "<< res << endl;
  }
  return 0;
}
