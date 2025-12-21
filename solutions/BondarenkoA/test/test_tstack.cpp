// тесты для стека

#include "tstack.h"
#include <gtest.h>
#include <stdexcept>  // Для исключений

// Тестируем стандартные операции стека
TEST(StackTest, TestPushAndPop)
{
    TStack<int> stack;

    // Проверка пустоты стека
    EXPECT_TRUE(stack.IsEmpty());
    EXPECT_EQ(stack.size(), 0);

    // Добавляем элемент в стек
    stack.Push(1);
    EXPECT_FALSE(stack.IsEmpty());
    EXPECT_EQ(stack.size(), 1);

    // Проверка верхнего элемента
    EXPECT_EQ(stack.Top(), 1);

    // Извлекаем элемент
    stack.Pop();
    EXPECT_TRUE(stack.IsEmpty());
    EXPECT_EQ(stack.size(), 0);
}

// Тест на извлечение из пустого стека
TEST(StackTest, TestPopFromEmptyStack)
{
    TStack<int> stack;

    // Проверка на пустой стек при попытке извлечь элемент
    EXPECT_THROW(stack.Pop(), std::out_of_range);
}

// Тест на получение верхнего элемента из пустого стека
TEST(StackTest, TestTopFromEmptyStack)
{
    TStack<int> stack;

    // Проверка на пустой стек при попытке получить верхний элемент
    EXPECT_THROW(stack.Top(), std::out_of_range);
}

// Тест на несколько операций push
TEST(StackTest, TestMultiplePush)
{
    TStack<int> stack;

    // Добавляем несколько элементов в стек
    stack.Push(1);
    stack.Push(2);
    stack.Push(3);

    // Проверка верхнего элемента
    EXPECT_EQ(stack.Top(), 3);
    EXPECT_EQ(stack.size(), 3);

    // Извлекаем элементы и проверяем
    stack.Pop();
    EXPECT_EQ(stack.Top(), 2);
    stack.Pop();
    EXPECT_EQ(stack.Top(), 1);
    stack.Pop();

    // Стек должен быть пустым
    EXPECT_TRUE(stack.IsEmpty());
}

// Тест на очистку стека
TEST(StackTest, TestClear)
{
    TStack<int> stack;

    // Добавляем элементы
    stack.Push(1);
    stack.Push(2);
    stack.Push(3);

    // Очищаем стек
    stack.clear();

    // Проверяем, что стек пуст
    EXPECT_TRUE(stack.IsEmpty());
    EXPECT_EQ(stack.size(), 0);
}
