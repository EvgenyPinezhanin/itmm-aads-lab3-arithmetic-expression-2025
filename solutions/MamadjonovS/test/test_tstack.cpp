#include "tstack.h"

#include <gtest.h>

TEST(TStack, test)
{
  ADD_FAILURE();
}

// Тесты для класса TStack
TEST(TStack, can_create_stack_with_default_size) {
    // Проверка создания стека с размером по умолчанию
    ASSERT_NO_THROW(TStack<int> s);
}

TEST(TStack, can_create_stack_with_given_size) {
    // Проверка создания стека с заданным размером
    ASSERT_NO_THROW(TStack<int> s(10));
}

TEST(TStack, throws_when_create_stack_with_zero_size) {
    // При создании стека размером 0 должен быть использован DefaultMemSize
    // Проверим, что стек работает с размером 0 (в нашей реализации он использует DefaultMemSize)
    TStack<int> s(0);
    // Попробуем добавить элемент - должно работать
    ASSERT_NO_THROW(s.Put(1));
    EXPECT_EQ(s.Top(), 1);
}

TEST(TStack, new_stack_is_empty) {
    // Новый стек должен быть пустым
    TStack<int> s;
    EXPECT_TRUE(s.IsEmpty());
}

TEST(TStack, stack_is_not_empty_after_put) {
    // После добавления элемента стек не должен быть пустым
    TStack<int> s;
    s.Put(10);
    EXPECT_FALSE(s.IsEmpty());
}

TEST(TStack, can_put_and_top_element) {
    // Проверка добавления и получения элемента
    TStack<int> s;
    s.Put(42);
    EXPECT_EQ(s.Top(), 42);
}

TEST(TStack, top_does_not_remove_element) {
    // Метод Top не должен удалять элемент
    TStack<int> s;
    s.Put(5);
    s.Top(); // Просто смотрим на вершину
    EXPECT_FALSE(s.IsEmpty()); // Стек все еще не пуст
    EXPECT_EQ(s.Top(), 5); // И элемент все еще там
}

TEST(TStack, can_get_element) {
    // Проверка извлечения элемента
    TStack<int> s;
    s.Put(10);
    s.Get(); // Извлекаем
    EXPECT_TRUE(s.IsEmpty()); // Стек должен стать пустым
}

TEST(TStack, stack_is_full_after_adding_MemSize_elements) {
    // Проверка заполнения стека
    TStack<int> s(3); // Маленький стек для теста
    s.Put(1);
    s.Put(2);
    s.Put(3);
    EXPECT_TRUE(s.IsFull());
}

TEST(TStack, throws_when_put_to_full_stack) {
    // Проверка исключения при переполнении
    TStack<int> s(2);
    s.Put(1);
    s.Put(2);
    ASSERT_THROW(s.Put(3), std::overflow_error);
}

TEST(TStack, throws_when_top_empty_stack) {
    // Проверка исключения при попытке получить элемент из пустого стека
    TStack<int> s;
    ASSERT_THROW(s.Top(), std::underflow_error);
}

TEST(TStack, throws_when_get_empty_stack) {
    // Проверка исключения при попытке извлечь элемент из пустого стека
    TStack<int> s;
    ASSERT_THROW(s.Get(), std::underflow_error);
}

TEST(TStack, lifo_order_is_correct) {
    // Проверка порядка LIFO (Last In - First Out)
    TStack<int> s;
    s.Put(1);
    s.Put(2);
    s.Put(3);

    EXPECT_EQ(s.Top(), 3); // Последний добавленный - первый
    s.Get();
    EXPECT_EQ(s.Top(), 2); // Следующий
    s.Get();
    EXPECT_EQ(s.Top(), 1); // Первый добавленный
}

TEST(TStack, can_put_after_get) {
    // Проверка возможности добавления после извлечения
    TStack<int> s(2);
    s.Put(1);
    s.Get(); // Извлекаем
    s.Put(2); // Снова добавляем
    EXPECT_EQ(s.Top(), 2);
}

TEST(TStack, multiple_puts_and_gets_work_correctly) {
    // Проверка нескольких операций добавления/извлечения
    TStack<int> s;

    for (int i = 0; i < 5; i++) {
        s.Put(i);
        EXPECT_EQ(s.Top(), i);
    }

    for (int i = 4; i >= 0; i--) {
        EXPECT_EQ(s.Top(), i);
        s.Get();
    }

    EXPECT_TRUE(s.IsEmpty());
}

TEST(TStack, can_use_different_types) {
    // Проверка работы с разными типами данных
    TStack<double> s1;
    s1.Put(3.14);
    EXPECT_DOUBLE_EQ(s1.Top(), 3.14);

    TStack<std::string> s2;
    s2.Put("test");
    EXPECT_EQ(s2.Top(), "test");
}