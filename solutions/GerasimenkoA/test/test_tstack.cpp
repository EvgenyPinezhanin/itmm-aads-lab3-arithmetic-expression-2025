#include "tstack.h"

#include <gtest.h>

TEST(TStack, can_create_tstack_with_positive_length)
{
	ASSERT_NO_THROW(TStack<int> s(5));
}

TEST(TStack, throws_when_create_tstack_with_negative_length)
{
	ASSERT_ANY_THROW(TStack<int> s(-1));
}

TEST(TStack, throws_when_create_tstack_with_zero_length)
{
	ASSERT_ANY_THROW(TStack<int> s(0));
}

TEST(TStack, isempty_work)
{
	TStack<int> s(3);
	EXPECT_TRUE(s.IsEmpty());
	s.Push(10);
	EXPECT_FALSE(s.IsEmpty());
}

TEST(TStack, isfull_work)
{
	TStack<int> s(2);
	EXPECT_FALSE(s.IsFull());
	s.Push(1);
	EXPECT_FALSE(s.IsFull());
	s.Push(2);
	EXPECT_TRUE(s.IsFull());
}

TEST(TStack, can_push)
{
	TStack<int> s(2);
	ASSERT_NO_THROW(s.Push(100));
	EXPECT_EQ(s.size(), 1);
}

TEST(TStack, cant_push_when_stack_overflow)
{
	TStack<int> s(1);
	s.Push(1);
	ASSERT_TRUE(s.IsFull());
	ASSERT_ANY_THROW(s.Push(2));
}

TEST(TStack, can_pop)
{
	TStack<int> s(3);
	s.Push(5);
	s.Push(7);
	ASSERT_NO_THROW(s.Pop());
	EXPECT_EQ(s.Top(), 5);
}

TEST(TStack, cant_pop_when_stack_underflow)
{
	TStack<int> s(2);
	EXPECT_TRUE(s.IsEmpty());
	ASSERT_ANY_THROW(s.Pop());
}

TEST(TStack, can_top)
{
	TStack<int> s(2);
	s.Push(42);
	int top = s.Top();
	EXPECT_EQ(top, 42);

}

TEST(TStack, cant_top_when_stack_is_empty)
{
	TStack<int> s(2);
	ASSERT_ANY_THROW(s.Top());
}

