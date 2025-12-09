// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// tstack.h
//
// Copyright (c) Пинежанин Е.С.

#ifndef __TStack_H__
#define __TStack_H__

#include <stdexcept> // Для исключений

const int DefaultMemSize = 1024; // стандартный размер памяти для стека

template <typename T>
class TStack {
protected:
    T* pMem; // указатель на массив элементов
    int MemSize; // размер памяти для СД
    int DataCount; // количество элементов в СД
    int Hi; // индекс вершины стека

    int GetNextIndex(int index) // получить следующий индекс
    {
        return index + 1; // Просто увеличиваем индекс на 1
    }

public:
    TStack(int Size = DefaultMemSize) : MemSize(Size)
    {
        if (Size <= 0) {
            MemSize = DefaultMemSize; // Используем значение по умолчанию
        }
        pMem = new T[MemSize]; // Выделяем память
        DataCount = 0; // Стек пуст
        Hi = -1; // Индекс вершины -1 (стек пуст)
    }

    ~TStack() // Исправлено: было Tstack, должно быть TStack
    {
        delete[] pMem; // Освобождаем память
        pMem = nullptr; // Обнуляем указатель
    }

    bool IsEmpty() const
    {
        return DataCount == 0; // Стек пуст, если количество элементов 0
    }

    bool IsFull() const
    {
        return DataCount == MemSize; // Стек полон, если количество элементов равно размеру
    }

    void Put(const T& Val) // добавить значение
    {
        if (IsFull()) {
            throw std::overflow_error("Stack is full"); // Ошибка переполнения
        }
        Hi++; // Увеличиваем индекс вершины
        pMem[Hi] = Val; // Записываем значение
        DataCount++; // Увеличиваем счетчик элементов
    }

    T Top() const // получить значение
    {
        if (IsEmpty()) {
            throw std::underflow_error("Stack is empty"); // Ошибка пустого стека
        }
        return pMem[Hi]; // Возвращаем значение с вершины
    }

    void Get() // извлечь значение
    {
        if (IsEmpty()) {
            throw std::underflow_error("Stack is empty"); // Ошибка пустого стека
        }
        // Для простых типов T дополнительных действий не нужно
        // Для сложных типов может потребоваться вызов деструктора
        Hi--; // Уменьшаем индекс вершины
        DataCount--; // Уменьшаем счетчик элементов
    }
};

#endif