#include "tstack.h"
#include <gtest.h>

TEST(TStack, can_create_stack_with_default_size)
{
    ASSERT_NO_THROW(TStack<int> s);
}

TEST(TStack, can_create_stack_with_positive_size)
{
    ASSERT_NO_THROW(TStack<int> s(100));
}

TEST(TStack, cant_create_stack_with_zero_size)
{
    ASSERT_ANY_THROW(TStack<int> s(0));
}

TEST(TStack, new_stack_is_empty)
{
    TStack<int> s;
    EXPECT_TRUE(s.IsEmpty());
}

TEST(TStack, stack_is_not_empty_after_put)
{
    TStack<int> s;
    s.Put(5);
    EXPECT_FALSE(s.IsEmpty());
}

TEST(TStack, can_put_element)
{
    TStack<int> s;
    ASSERT_NO_THROW(s.Put(10));
}

TEST(TStack, can_get_top_element)
{
    TStack<int> s;
    s.Put(42);
    EXPECT_EQ(42, s.Top());
}

TEST(TStack, top_does_not_remove_element)
{
    TStack<int> s;
    s.Put(1);
    s.Put(2);
    EXPECT_EQ(2, s.Top());
    EXPECT_EQ(2, s.Top()); // Top дважды возвращает то же значение
}

TEST(TStack, can_remove_element_with_get)
{
    TStack<int> s;
    s.Put(10);
    s.Put(20);
    s.Get();
    EXPECT_EQ(10, s.Top());
}

TEST(TStack, can_check_full_stack)
{
    TStack<int> s(2);
    s.Put(1);
    s.Put(2);
    EXPECT_TRUE(s.IsFull());
}

TEST(TStack, can_put_and_get_multiple_elements)
{
    TStack<int> s(5);
    for (int i = 1; i <= 5; i++) {
        s.Put(i);
    }
    for (int i = 5; i >= 1; i--) {
        EXPECT_EQ(i, s.Top());
        s.Get();
    }
    EXPECT_TRUE(s.IsEmpty());
}

TEST(TStack, throws_when_get_from_empty_stack)
{
    TStack<int> s;
    ASSERT_ANY_THROW(s.Get());
}

TEST(TStack, throws_when_top_from_empty_stack)
{
    TStack<int> s;
    ASSERT_ANY_THROW(s.Top());
}

TEST(TStack, throws_when_put_to_full_stack)
{
    TStack<int> s(2);
    s.Put(1);
    s.Put(2);
    ASSERT_ANY_THROW(s.Put(3));
}