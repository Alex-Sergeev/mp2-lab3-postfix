#include "postfix.h"
#include <gtest.h>
#include <string>

TEST(TPostfix, can_create_postfix)
{
	string expression = "a+b";

	ASSERT_NO_THROW(TPostfix Sample(expression););
}
TEST(TPostfix, can_get_infix)
{
	string expression = "a+b";
	TPostfix Sample(expression);

	EXPECT_EQ("a+b",Sample.GetInfix());
}
TEST(TPostfix, can_get_postfix)
{
	string expression = "a+b";
	TPostfix Sample(expression);
	Sample.ToPostfix();

	ASSERT_NO_THROW(Sample.GetPostfix());
}

TEST(TPostfix, created_postfix_is_right)
{
	string expression = "a+b";
	TPostfix Sample(expression);
	Sample.ToPostfix();

	EXPECT_EQ("a b +", Sample.GetPostfix());
}
TEST(TPostfix, can_calculate)
{
	string expression = "5+6*3";
	TPostfix Sample(expression);
	Sample.ToPostfix();

	EXPECT_EQ(23, Sample.Calculate());
}
TEST(TPostfix, cant_calculate_not_existing_postfix)
{
	string expression = "a+b";
	TPostfix Sample(expression);

	ASSERT_ANY_THROW(Sample.Calculate());
}
TEST(TPostfix, wrong_expression_is_wrong)
{
	string expression = "a+";
	TPostfix Sample(expression);

	EXPECT_EQ(0, Sample.ErrorChecking());
}
TEST(TPostfix, wrong_expression_is_wrong_2)
{
	string expression = "a(b)";
	TPostfix Sample(expression);

	EXPECT_EQ(0, Sample.ErrorChecking());
}
TEST(TPostfix, wrong_expression_is_wrong_3)
{
	string expression = "sina";
	TPostfix Sample(expression);

	EXPECT_EQ(0, Sample.ErrorChecking());
}
TEST(TPostfix, wrong_expression_is_wrong_4)
{
	string expression = "a+(b";
	TPostfix Sample(expression);

	EXPECT_EQ(0, Sample.ErrorChecking());
}
TEST(TPostfix, right_expression_is_right)
{
	string expression = "a+b-(a-b)*y";
	TPostfix Sample(expression);

	EXPECT_EQ(1, Sample.ErrorChecking());
}

