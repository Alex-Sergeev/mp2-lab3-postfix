#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include "stack.h"
#include <iostream>

using namespace std;

class TPostfix
{
  string infix;
  string postfix;
  string ToPostfix(string Str);
public:
  TPostfix()
  {
	  string Str;
	  do
	  {
		  cin >> Str;
	  }
	  while (!ErrorChecking(Str));
	  infix = Str;
	  postfix = ToPostfix(Str);
  }
  bool ErrorChecking(string Str);
  string GetInfix() { return infix; }
  string GetPostfix() { return postfix; }
  double Calculate(); // Ввод переменных, вычисление по постфиксной форме
};

#endif
