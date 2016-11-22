#include "postfix.h"
#include "stack.h"
bool TPostfix::ErrorChecking(string Str)
{
	return 1;
}
int priority(string Str)
{
	string ArifmOperations[8];
	ArifmOperations[0] = '+';
	ArifmOperations[1] = '-';
	ArifmOperations[2] = '*';
	ArifmOperations[3] = '/';
	ArifmOperations[4] = "sin";
	ArifmOperations[5] = "cos";
	ArifmOperations[6] = "(";
	ArifmOperations[7] = ")";
	char OperationsPriority[8];
	OperationsPriority[0] = 1;
	OperationsPriority[1] = 1;
	OperationsPriority[2] = 2;
	OperationsPriority[3] = 2;
	OperationsPriority[4] = 3;
	OperationsPriority[5] = 3;
	OperationsPriority[6] = 0;
	OperationsPriority[7] = 0;
	int i = 0;
	while (Str != ArifmOperations[i])
		i++;
	return OperationsPriority[i];
}
int IsOperation(string Str, int i)
{
	string ArifmOperations[8];
	ArifmOperations[0] = '+';
	ArifmOperations[1] = '-';
	ArifmOperations[2] = '*';
	ArifmOperations[3] = '/';
	ArifmOperations[4] = "sin";
	ArifmOperations[5] = "cos";
	ArifmOperations[6] = "(";
	ArifmOperations[7] = ")";
	int j;
	for (j = 0; j<6; j++)
		if (Str[i] == ArifmOperations[j][0])
		{
			if (j == 4)
				if (Str.substr(i, 4) == "sin(")
					return 4;
				else
					continue;
			if (j == 5)
				if (Str.substr(i, 4) == "cos(")
					return 5;
					else 
						continue;
			return j;
		}
	return -1;
}
string TPostfix::ToPostfix(string Str)
{
	string ArifmOperations[8];
	ArifmOperations[0] = '+';
	ArifmOperations[1] = '-';
	ArifmOperations[2] = '*';
	ArifmOperations[3] = '/';
	ArifmOperations[4] = "sin";
	ArifmOperations[5] = "cos";
	ArifmOperations[6] = "(";
	ArifmOperations[7] = ")";
	TStack<string> OperationsStack;
	string result;
	string now, prev;
	int i,p,j;
	int size = Str.size();
	for (i=0;i<size;i++)
	{
		if (Str[i] == '(')
		{
			result = result + "(";
			continue;
		}
		if (Str[i] == ')')
		{
			while (!OperationsStack.IsEmpty())
				result = result + OperationsStack.Pop();
			result = result + ")";
			continue;
		}
		j = IsOperation(Str, i);
		if (j > -1)
		{
			if (j > 3)
				i = i + 2;
			if (OperationsStack.IsEmpty())
			{
				OperationsStack.Push(ArifmOperations[j]);
				continue;
			}
			now = ArifmOperations[j];
			while (true)
			{
				prev = OperationsStack.Pop();
				if (priority(now) <= priority(prev))
				{
					result = result + prev;
				}
				else
				{
					OperationsStack.Push(now);
					break;
				}
				if (!OperationsStack.IsEmpty())
					now = prev;
				else
				{
					OperationsStack.Push(now);
					break;
				}
			}
		}
		else
		{
			j = 1;
			while (true)
			{
				if (Str[i + j] == ArifmOperations[0][0])
					break;
				if (Str[i + j] == ArifmOperations[1][0])
					break;
				if (Str[i + j] == ArifmOperations[2][0])
					break;
				if (Str[i + j] == ArifmOperations[3][0])
					break;
				if (Str[i + j] == ArifmOperations[6][0])
					break;
				if (Str[i + j] == ArifmOperations[7][0])
					break;
				if (Str[i + j] == 0)
					break;
				j++;
			}
			result = result + Str.substr(i, j) + ".";
			i = i + j - 1;
		}
	}
	while (!OperationsStack.IsEmpty())
		result = result + OperationsStack.Pop();
  return result;
}

double TPostfix::Calculate()
{
  return 0;
}
