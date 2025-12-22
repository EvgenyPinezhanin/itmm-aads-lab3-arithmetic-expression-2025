#include "tstack.h"

#include <gtest.h>
 
TEST(TStack, Constructor_ThrowsOnNegativeSize) {
    EXPECT_THROW({
        TStack<int> s(-5);
        }, std::invalid_argument);
}

// Создание стека с нулевым размером
TEST(TStack, Constructor_ThrowsOnZeroSize) {
    EXPECT_THROW({
        TStack<int> s(0);
        }, std::invalid_argument);
}


// Создание пустого стека
TEST(TStack, Constructor_Default) {
    TStack<int> stack;
    EXPECT_TRUE(stack.IsEmpty());
    EXPECT_FALSE(stack.IsFull());
}

//   Создание стека с заданным размером
TEST(TStack, Constructor_WithSize) {
    TStack<int> stack(5);
    EXPECT_TRUE(stack.IsEmpty());
    EXPECT_FALSE(stack.IsFull());
}

//   Добавление одного элемента
TEST(TStack, Put_OneElement) {
    TStack<int> stack(10);
    stack.Put(42);
    EXPECT_FALSE(stack.IsEmpty());
    EXPECT_EQ(stack.Top(), 42);
}

//  Добавление нескольких элементов
TEST(TStack, Put_MultipleElements) {
    TStack<int> stack(3);
    stack.Put(1);
    stack.Put(2);
    stack.Put(3);
    EXPECT_TRUE(stack.IsFull());
    EXPECT_EQ(stack.Top(), 3);
}

//   Извлечение одного элемента
TEST(TStack, Get_OneElement) {
    TStack<int> stack(5);
    stack.Put(100);
    int top = stack.Top();
    stack.Get();
    EXPECT_EQ(top, 100);
    EXPECT_TRUE(stack.IsEmpty());
}

//  Порядок LIFO (последним пришел - первым ушел)
TEST(TStack, LIFO_Order) {
    TStack<int> stack;
    stack.Put(10);
    stack.Put(20);
    stack.Put(30);

    EXPECT_EQ(stack.Top(), 30);
    stack.Get();
    EXPECT_EQ(stack.Top(), 20);
    stack.Get();
    EXPECT_EQ(stack.Top(), 10);
    stack.Get();
    EXPECT_TRUE(stack.IsEmpty());
}

//   Top не удаляет элемент
TEST(TStack, Top_DoesNotRemove) {
    TStack<int> stack;
    stack.Put(99);
    EXPECT_EQ(stack.Top(), 99);
    EXPECT_EQ(stack.Top(), 99); // Второй вызов возвращает то же значение
    EXPECT_FALSE(stack.IsEmpty());
}

//  Переполнение стека
TEST(TStack, Put_Overflow) {
    TStack<int> stack(2);
    stack.Put(1);
    stack.Put(2);
    EXPECT_THROW(stack.Put(3), std::overflow_error);
}

//   Извлечение из пустого стека
TEST(TStack, Get_EmptyStack) {
    TStack<int> stack(5);
    EXPECT_THROW(stack.Get(), std::underflow_error);
}

//   Получение вершины пустого стека
TEST(TStack, Top_EmptyStack) {
    TStack<int> stack(5);
    EXPECT_THROW(stack.Top(), std::underflow_error);
}

//   Работа с разными типами данных
TEST(TStack, DifferentDataTypes) {
    TStack<double> doubleStack;
    doubleStack.Put(3.14);
    EXPECT_DOUBLE_EQ(doubleStack.Top(), 3.14);

    TStack<std::string> stringStack;
    stringStack.Put("Hello");
    EXPECT_EQ(stringStack.Top(), "Hello");
}

//   Многократное добавление и извлечение
TEST(TStack, MultiplePutAndGet) {
    TStack<int> stack(100);
    for (int i = 0; i < 50; i++) {
        stack.Put(i);
    }
    for (int i = 49; i >= 0; i--) {
        EXPECT_EQ(stack.Top(), i);
        stack.Get();
    }
    EXPECT_TRUE(stack.IsEmpty());
}

// Очистка стека
TEST(TStack, ClearStack) {
    TStack<int> stack(10);
    for (int i = 0; i < 5; i++) {
        stack.Put(i);
    }
    while (!stack.IsEmpty()) {
        stack.Get();
    }
    EXPECT_TRUE(stack.IsEmpty());
}

//   Повторное заполнение после очистки
TEST(TStack, RefillAfterClear) {
    TStack<int> stack(3);
    stack.Put(1);
    stack.Put(2);
    stack.Put(3);

    // Очищаем
    while (!stack.IsEmpty()) {
        stack.Get();
    }

    // Заполняем снова
    stack.Put(4);
    stack.Put(5);
    EXPECT_EQ(stack.Top(), 5);
    stack.Get();
    EXPECT_EQ(stack.Top(), 4);
}

//   Граничные условия
TEST(TStack, BoundaryConditions) {
    TStack<int> stack(1);
    EXPECT_TRUE(stack.IsEmpty());
    EXPECT_FALSE(stack.IsFull());

    stack.Put(42);
    EXPECT_FALSE(stack.IsEmpty());
    EXPECT_TRUE(stack.IsFull());

    EXPECT_EQ(stack.Top(), 42);
    stack.Get();
    EXPECT_TRUE(stack.IsEmpty());
}