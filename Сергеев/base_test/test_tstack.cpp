#include "stack.h"
#include <gtest.h>

TEST(TStack, Empty_Stack_Is_Empty)
{
	TStack<int> tmp;

	EXPECT_EQ (1, tmp.IsEmpty());
}
TEST(TStack, Not_Empty_Stack_Is_Not_Empty)
{
	TStack<int> tmp;
	tmp.Push(25);

	EXPECT_EQ(0, tmp.IsEmpty());
}
TEST(TStack, Can_Push_Elem)
{
	TStack<int> tmp;

	ASSERT_NO_THROW(tmp.Push(25));
}
TEST(TStack, Can_Push_Elem_In_Full_Stack)
{
	TStack<int> tmp;
	for (int i = 0; i<50; i++)
		tmp.Push(i);

	ASSERT_NO_THROW(tmp.Push(50));
}
TEST(TStack, Can_Pop_Elem)
{
	TStack<int> tmp;
	tmp.Push(25);

	EXPECT_EQ(25,tmp.Pop());
}
TEST(TStack, Cant_Pop_Elem_From_Empty_Stack)
{
	TStack<int> tmp;

	ASSERT_ANY_THROW(tmp.Pop());
}
TEST(TStack, Not_Full_Stack_Is_Not_Full)
{
	TStack<int> tmp;
	tmp.Push(25);

	EXPECT_EQ(0, tmp.IsFull());
}
TEST(TStack, Full_Stack_Is_Full)
{
	TStack<int> tmp;
	for (int i=0;i<50;i++)
		tmp.Push(25);

	EXPECT_EQ(1, tmp.IsFull());
}