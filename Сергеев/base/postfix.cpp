#include "postfix.h"
#include "stack.h"
#include <cmath>
bool TPostfix::ErrorChecking(string &Str)
{
	return 1;
}
int priority(string &Str, string* ArifmOperations,char* OperationsPriority)
{
	int i = 0;
	while (Str != ArifmOperations[i])
		i++;
	return OperationsPriority[i];
}
int IsOperation(string &Str, int &i, string* ArifmOperations)
{
	int j;
	for (j = 0; j<8; j++)
		if (Str[i] == ArifmOperations[j][0])
		{
			if (j == 4)
				if (Str.substr(i, 3) == "sin")
					return 4;
				else
					continue;
			if (j == 5)
				if (Str.substr(i, 3) == "cos")
					return 5;
					else 
						continue;
			return j;
		}
	return -1;
}
string TPostfix::ToPostfix(string &Str)
{
	TStack<string> OperationsStack;
	string result;
	string now, OperTop;
	int i,p,m, OperIndex;
	int size = Str.size();
	for (i=0;i<size;i++)
	{
		if (Str[i] == '(')
		{
			OperationsStack.Push("(");
			continue;
		}
		if (Str[i] == ')')
		{
			now = OperationsStack.Pop();
			while (now != "(")
			{
				result += now;
				now = OperationsStack.Pop();
			}
			continue;
		}
		OperIndex = IsOperation(Str, i, ArifmOperations);
		if (OperIndex > -1)
		{
			if (OperIndex > 3)
				i = i + 2;
			if (OperationsStack.IsEmpty())
			{
				OperationsStack.Push(ArifmOperations[OperIndex]);
				continue;
			}
			now = ArifmOperations[OperIndex];
			OperTop = OperationsStack.Pop();
			while (priority(now, ArifmOperations, OperationsPriority) <= priority(OperTop, ArifmOperations, OperationsPriority))
			{
				result += OperTop;
				if (OperationsStack.IsEmpty())
					break;
				OperTop = OperationsStack.Pop();
			}
			if (priority(now, ArifmOperations, OperationsPriority) > priority(OperTop, ArifmOperations, OperationsPriority))
				OperationsStack.Push(OperTop);
			OperationsStack.Push(now);
		}
		else
		{
			p = 0;
			m = i;
			do
			{
				p++;
				m++;
				OperIndex = IsOperation(Str, m, ArifmOperations);
				if (m == size)
					break;
			} while (OperIndex == -1);
			result += Str.substr(i, p) + " ";
			i = i + p - 1;
		}
	}
	while (!OperationsStack.IsEmpty())
		result += OperationsStack.Pop();
  return result;
}
double FromStringToDouble (string& Str)
{
	double result=0;
	int size = Str.size();
	double k,j,n;
	n = size;
	for (int i=0; i < size; i++)
	{
		k = 1;
		for (j = 1; j < n; j++)
			k *= 10;
		if (Str[i] == '1')
			result += 1 * k;
		else if (Str[i] == '2')
			result += 2 * k;
		else if (Str[i] == '3')
			result += 3 * k;
		else if (Str[i] == '4')
			result += 4 * k;
		else if (Str[i] == '5')
			result += 5 * k;
		else if (Str[i] == '6')
			result += 6 * k;
		else if (Str[i] == '7')
			result += 7 * k;
		else if (Str[i] == '8')
			result += 8 * k;
		else if (Str[i] == '9')
			result += 9 * k;
		else if (Str[i] == '0');
		else
			return -1;
		n--;
	}
	return result;
}
double TPostfix::Calculate()
{
	TStack<double> CalculatingStack;
	double Var1,Var2;
	int i, p, j, check;
	int amount = 0;
	int Operation;
	string Str;
	string MassiveOfVariables[5000];
	double MassiveOfValues[5000];
	int size = postfix.size();
	for (i = 0; i < size; i++)
	{
		Operation = IsOperation(postfix, i, ArifmOperations);
		if (Operation == -1)
		{
			p = 0;
			do
			{
				p++;
				if (i+p == size)
					break;
			} while (postfix[i+p]!=' ');
			check = 0;
			for (j = 0; j < amount; j++)
				if (postfix.substr(i, p) == MassiveOfVariables[j])
					check = 1;
			Var1 = FromStringToDouble(postfix.substr(i, p));	
			if (check == 0)
			{
				if (Var1 == -1)
				{
					cout << "Введите значение переменной " << postfix.substr(i, p) << " ";
					cin >> MassiveOfValues[amount];
					MassiveOfVariables[amount] = (postfix.substr(i, p));
					amount++;
				}
				else
				{
					MassiveOfValues[amount] = Var1;
					MassiveOfVariables[amount] = (postfix.substr(i, p));
					amount++;
				}
			}
			i = i + p;
		}
		if (Operation > 3)
			i = i + 2;
	}
	for (i = 0; i < size; i++)
	{
		Operation = IsOperation(postfix, i, ArifmOperations);
		if (Operation == -1)
		{
			p = 0;
			do
			{
				p++;
				if (i + p == size)
					break;
			} while (postfix[i + p] != ' ');
			Str = postfix.substr(i, p);
			j = 0;
			while (Str != MassiveOfVariables[j])
					j++;
			CalculatingStack.Push(MassiveOfValues[j]);
			i = i + p;
		}
		else
		{
			Var1 = CalculatingStack.Pop();
			if (Operation == 4)
			{
				i = i + 2;
				CalculatingStack.Push(sin((Var1*3.14159265)/180));
				continue;
			}
			if (Operation == 5)
			{
				i = i + 2;
				CalculatingStack.Push(cos((Var1*3.14159265) / 180));
				continue;
			}
			Var2 = CalculatingStack.Pop();
			switch (Operation)
			{
			case 0:
			{
				Var1 += Var2;
				CalculatingStack.Push(Var1);
				break;
			}
			case 1:
			{
				Var1 = Var2 - Var1;
				CalculatingStack.Push(Var1);
				break;
			}
			case 2:
			{
				Var1 *= Var2;
				CalculatingStack.Push(Var1);
				break;
			}
			case 3:
			{
				Var1 = Var2/Var1;
				CalculatingStack.Push(Var1);
				break;
			}
			}
		}
	}
	return CalculatingStack.Pop();
}
