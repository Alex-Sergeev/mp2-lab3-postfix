#ifndef __STACK_H__
#define __STACK_H__

template <class T>
class TStack
{
	int top;
	T *pMem;
	unsigned char size;
public:
	TStack()
	{
		top = -1;
		pMem = new T[50];
		size = 50;
	}
	bool IsEmpty()
	{
		return top == -1;
	}
	bool IsFull()
	{
		return top == (size - 1);
	}
	void Push(T value)
	{
		if (IsFull())
		{
			size = size * 2;
			if (size == 819200)
				throw "Creating too large Stack";
			T *tmp = pMem;
			pMem = new T[size];
			for (int i = 0; i < size / 2; i++)
				pMem[i] = tmp[i];
		}
		pMem[++top] = value;
	}
	T Pop()
	{
		if (IsEmpty())
			throw "Access to empty Stack";
		return pMem[top--];
	}
};

#endif
