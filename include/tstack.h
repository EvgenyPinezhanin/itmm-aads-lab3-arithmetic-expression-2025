// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// tstack.h
//
// Copyright (c) Пинежанин Е.С.

#ifndef __TStack_H__
#define __TStack_H__

#include <stdexcept>  

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
        return index + 1;
    }

public:
    TStack(int Size = DefaultMemSize) : MemSize(Size)
    {
        if (Size <= 0) {
            throw std::invalid_argument("Stack size must be positive");
        }
        pMem = new T[MemSize]; // Выделяем память
        DataCount = 0; // Стек пуст
        Hi = -1; // Индекс вершины -1 (стек пуст)
    }

    ~TStack()
    {
        delete[] pMem;
        pMem = nullptr;
    }

    bool IsEmpty() const
    {
        return DataCount == 0;
    }

    bool IsFull() const
    {
        return DataCount == MemSize;
    }

    void Put(const T& Val)
    {
        if (IsFull()) {
            throw std::overflow_error("Stack is full");
        }
        Hi++;
        pMem[Hi] = Val;
        DataCount++; // Увеличиваем счетчик элементов
    }

    T Top() const // получить значение
    {
        if (IsEmpty()) {
            throw std::underflow_error("Stack is empty");
        }
        return pMem[Hi]; // Возвращаем значение с вершины
    }

    void Get() // извлечь значение
    {
        if (IsEmpty()) {
            throw std::underflow_error("Stack is empty");
        }
        Hi--;
        DataCount--;
    }
};

#endif