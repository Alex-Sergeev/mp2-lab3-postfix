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
  string *ArifmOperations;
  char* OperationsPriority;
public:
  TPostfix(string Str)
  {
	  OperationsPriority = new char[8];
	  OperationsPriority[0] = 1;
	  OperationsPriority[1] = 1;
	  OperationsPriority[2] = 2;
	  OperationsPriority[3] = 2;
	  OperationsPriority[4] = 3;
	  OperationsPriority[5] = 3;
	  OperationsPriority[6] = 0;
	  OperationsPriority[7] = 0;
	  ArifmOperations = new string[8];;
	  ArifmOperations[0] = '+';
	  ArifmOperations[1] = '-';
	  ArifmOperations[2] = '*';
	  ArifmOperations[3] = '/';
	  ArifmOperations[4] = "sin";
	  ArifmOperations[5] = "cos";
	  ArifmOperations[6] = "(";
	  ArifmOperations[7] = ")";
	  infix = Str;
	  postfix = "Not Exist";
  }
  bool ErrorChecking();
  void ToPostfix();
  string GetInfix() { return infix; }
  string GetPostfix() { return postfix; }
  double Calculate(); // Ввод переменных, вычисление по постфиксной форме
};

#endif
