#include "postfix.h"
#include "stack.h"
#include <cmath>
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
					break;
			if (j == 5)
				if (Str.substr(i, 3) == "cos")
					return 5;
				else
					break;
			return j;
		}
	return -1;
}
bool TPostfix::ErrorChecking()
{
	string Str = infix;
	setlocale(LC_ALL, "Russian");
	string Str1;
	double tmp;
	char* Str2;
	int i,j,p,m,check;
	int amount = 0;
	char now;
	int OperationIndex;
	int OperationIndexj;
	int size = Str.size();
	for (i = 0; i < size; i++)
	{
		now = Str[i];
		if (!(((now > 39) && (now < 58)) || ((now > 64) && (now < 91)) || ((now > 96) && (now < 123))))
		{
			cout << "Введён недопустимый символ на " << i + 1 << " позиции" << endl;
			cout << "Допустимые символы 'a-z', 'A-Z', '.', ',', '0-9', '+' , '-' , '*' , '/' " << endl;
			return 0;
		}
		if (now == 46)
			Str[i] = ',';
	}
	infix = Str;
	OperationIndex = IsOperation(Str, i = 0, ArifmOperations);
	if ((OperationIndex > -1) && (OperationIndex < 4) || (OperationIndex == 7))
	{
		cout << "Неверная запись выражения" << endl;
		cout << "Запись не может начинатся с операций '+' '-' '*' '/' ')' " << endl;
		return 0;
	}
	for (i = 0; i < size; i++)
	{
		OperationIndex = IsOperation(Str, i , ArifmOperations);
		if (OperationIndex != -1)
		{
			OperationIndexj = IsOperation(Str, j = i + 1, ArifmOperations);
			if (OperationIndex < 4)
			{
				if (((OperationIndexj > -1) && (OperationIndexj < 4)) || (OperationIndexj == 7))
				{
					cout << "Неверная запись выражения" << endl;
					cout << "После операции не может быть операции или закрывающей скобки на позиции " << i+1 << endl;
					return 0;
				}
				if (((OperationIndexj < 4)&&(OperationIndexj>-1)&&(OperationIndexj!=6)||(Str[i+1]==0)))
				{
					cout << "Неверная запись выражения" << endl;
					cout << "Отсутствует переменная после операции на позиции " << i + 1 << endl;
					return 0;
				}
				continue;
			}
			if (OperationIndex == 4)
			{
				i += 2;
				if (Str[i + 1] != '(')
				{
					cout << "Неверная запись выражения" << endl;
					cout << "Отсутсвует параметр функции sin на позиции " << i+2 << endl;
					return 0;
				}
				continue;
			}
			if (OperationIndex == 5)
			{
				i += 2;
				if (Str[i + 1] != '(')
				{
					cout << "Неверная запись выражения" << endl;
					cout << "Отсутсвует параметр функции cos на позиции " << i+2 << endl;
					return 0;
				}
				continue;
			}
			if (OperationIndex == 6)
			{
				if (((OperationIndexj>-1) && (OperationIndexj<4)) || (OperationIndexj == 7))
				{
					cout << "Неверная запись выражения" << endl;
					cout << "После открывающей скобки не может быть операции " << ArifmOperations[OperationIndexj] << " в позиции "<< i+1 << endl;
					return 0;
				}
				amount++;
				continue;
			}
			if (OperationIndex == 7)
			{
				if ((((OperationIndexj > -1) && (OperationIndexj<4))) || (OperationIndexj == 6))
				{
					amount--;
					continue;
				}
				if (Str[i + 1] == NULL)
				{
					amount--;
					continue;
				}
				cout << "Неверная запись выражения" << endl;
				cout << "После закрывающей скобки на позиции "<< i+1 <<" не должно быть операнда, открывающей скобки или функций"  << endl;
				return 0;
			}
		}
		else 
		{
			p = 0;
			m = i;
			do
			{
				p++;
				m++;
				OperationIndex = IsOperation(Str, m, ArifmOperations);
				if (m == size)
					break;
			} while (OperationIndex == -1);
			Str1 = Str.substr(i, p);
			Str2 = new char[Str1.size() + 1];
			for (j = 0; j < Str1.size() + 1; j++)
				Str2[j] = Str1[j];
			tmp = strtod(Str2, NULL);
			if ((tmp != 0.0))
			{
				check = 0;
				for (p = 0; p < Str1.size(); p++)
				{
					if ((Str2[p] < '0') || (Str2[p] == ',') || (Str2[p] > '9'))
					{
						if (Str2[p] == ',')
						{
							check++;
							continue;
						}
						cout << "Неправильная запись переменной (Переменная не должна начинатся с цифры) на позиции " << i + 1 << endl;
						return 0;
					}
					if (check > 1)
					{
						cout << "Неправильная запись числа - лишняя запятая" << endl;;
						return 0;
					}
				}
			}
			i = i + p - 1;
			if (IsOperation(Str, m = i + 1, ArifmOperations) == 6)
			{
				cout << "Неверная запись выражения" << endl;
				cout << "После переменной не может быть открывающей скобки" << endl;
				return 0;
			}
		}
	}
	if (amount != 0)
	{
		cout << "Неверная запись выражения" << endl;
		cout << "Присутствуют лишние скобки" << endl;
		return 0;
	}
	return 1;
}
int priority(string &Str, string* ArifmOperations,char* OperationsPriority)
{
	int i = 0;
	while (Str != ArifmOperations[i])
		i++;
	return OperationsPriority[i];
}
void TPostfix::ToPostfix()
{
	string Str = infix;
	TStack<string> OperationsStack;
	string result;
	string now, OperationTop;
	int i,p,m, OperationIndex;
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
		OperationIndex = IsOperation(Str, i, ArifmOperations);
		if (OperationIndex > -1)
		{
			if (OperationIndex > 3)
				i = i + 2;
			if (OperationsStack.IsEmpty())
			{
				OperationsStack.Push(ArifmOperations[OperationIndex]);
				continue;
			}
			now = ArifmOperations[OperationIndex];
			OperationTop = OperationsStack.Pop();
			while (priority(now, ArifmOperations, OperationsPriority) <= priority(OperationTop, ArifmOperations, OperationsPriority))
			{
				result += OperationTop;
				if (OperationsStack.IsEmpty())
					break;
				OperationTop = OperationsStack.Pop();
			}
			if (priority(now, ArifmOperations, OperationsPriority) > priority(OperationTop, ArifmOperations, OperationsPriority))
				OperationsStack.Push(OperationTop);
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
				OperationIndex = IsOperation(Str, m, ArifmOperations);
				if (m == size)
					break;
			} while (OperationIndex == -1);
			result += Str.substr(i, p) + " ";
			i = i + p - 1;
		}
	}
	while (!OperationsStack.IsEmpty())
		result += OperationsStack.Pop();
  postfix = result;
}
double TPostfix::Calculate()
{
	setlocale(LC_ALL, "Russian");
	if (postfix == "Not Exist")
	{
		cout << "Постфиксная форма не создана" << endl;
		throw("postfix_not_exist");
	}
	TStack<double> CalculatingStack;
	double Var1,Var2;
	int i, p, j, check;
	int amount = 0;
	int OperationIndex;
	char * Str2;
	string Str;
	string MassiveOfVariables[5000];
	double MassiveOfValues[5000];
	int size = postfix.size();
	for (i = 0; i < size; i++)
	{
		OperationIndex = IsOperation(postfix, i, ArifmOperations);
		if (OperationIndex == -1)
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
			Str = postfix.substr(i, p);
			Str2 = new char[Str.size() + 1];
			for (j = 0; j < Str.size() + 1; j++)
				Str2[j] = Str[j];
			Var1 = strtod( Str2, NULL);
			if ((Str2[0] != '0')&&(Var1 == 0.0))
				Var1 = Var1 - 1;
			if (check == 0)
			{
				if (Var1 == -1.0)
				{
					cout << "Введите значение переменной " << Str << " ";
					cin >> MassiveOfValues[amount];
					MassiveOfVariables[amount] = (Str);
					amount++;
				}
				else
				{
					MassiveOfValues[amount] = Var1;
					MassiveOfVariables[amount] = (Str);
					amount++;
				}
			}
			i = i + p;
		}
		if (OperationIndex > 3)
			i = i + 2;
	}
	for (i = 0; i < size; i++)
	{
		OperationIndex = IsOperation (postfix, i, ArifmOperations);
		if (OperationIndex == -1)
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
			if (OperationIndex == 4)
			{
				i = i + 2;
				CalculatingStack.Push(sin((Var1*3.14159265) / 180));
				continue;
			}
			if (OperationIndex == 5)
			{
				i = i + 2;
				CalculatingStack.Push(cos((Var1*3.14159265) / 180));
				continue;
			}
			Var2 = CalculatingStack.Pop();
			switch (OperationIndex)
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
				if (Var1 == 0)
				{
					cout << "Ошибка: в процессе вычисления происходит деление на 0" << endl;
					return 0;
				}
				Var1 = Var2/Var1;
				CalculatingStack.Push(Var1);
				break;
			}
			}
		}
	}
	return CalculatingStack.Pop();
}
