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

public:
    TStack(int Size = DefaultMemSize) : MemSize(Size)
    {
        if (Size <= 0) {
            throw std::invalid_argument("Размер стека должен быть положительным.");
        }
        pMem = new T[MemSize]; // Выделяем память
        DataCount = 0; // Стек пуст
        Hi = -1; // Индекс вершины -1 (стек пуст)
    }

    ~TStack() {
        if (pMem != nullptr) {  // лишняя проверка
            delete[] pMem;
            pMem = nullptr;
        }
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
        pMem[++Hi] = Val; // Сначала увеличиваем Hi, потом записываем
        DataCount++;
    }

    T Top() const
    {
        if (IsEmpty()) {
            throw std::underflow_error("Stack is empty");
        }
        return pMem[Hi];
    }

    void Get()
    {
        if (IsEmpty()) {
            throw std::underflow_error("Stack is empty");
        }
        Hi--;
        DataCount--;
    }
};

#endif