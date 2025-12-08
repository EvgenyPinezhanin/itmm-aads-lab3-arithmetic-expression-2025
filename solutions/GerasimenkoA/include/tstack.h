// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// tstack.h
//
// Copyright (c) Пинежанин Е.С.

#ifndef __TStack_H__
#define __TStack_H__

#include <cstddef>      
#include <stdexcept>    
#include <utility> 

using namespace std;

const size_t DefaultMemSize = 1024; // стандартный размер памяти для стека

template <typename T>
class TStack {
protected:
    T* pMem;            // указатель на массив элементов
    size_t MemSize;     // размер памяти для СД
    size_t DataCount;   // количество элементов в СД
    size_t Hi;          // индекс вершины стека

    size_t GetNextIndex(size_t index) // получить следующий индекс
    {
        return (index + 1) % MemSize;
    }


public:
    TStack(size_t Size = DefaultMemSize) : pMem(nullptr), MemSize(Size), DataCount(0), Hi(0)
    {
        if (MemSize == 0) throw out_of_range("Stack size should be greater than zero.");
        pMem = new T[MemSize]();
    }

    ~TStack()
    {
        if (pMem != nullptr) delete[] pMem;
    }


    bool IsEmpty() const
    {
        return DataCount == 0;
    }

    bool IsFull() const
    {
        return DataCount == MemSize;
    }


    void Push(const T &Val) // добавить значение
    {
        if (IsFull()) throw out_of_range("Stack overflow.");
        pMem[Hi] = Val;
        Hi = GetNextIndex(Hi);
        ++DataCount;
    }

    void Pop() // извлечь значение
    {
        if (IsEmpty()) throw out_of_range("Stack underflow.");
        Hi = (Hi + MemSize - 1) % MemSize;
        --DataCount;
    }

    const T& Top() const // получить значение
    {
        if (IsEmpty()) throw out_of_range("Stack is empty.");
        size_t idx = (Hi + MemSize - 1) % MemSize;
        return pMem[idx];
    }   

    size_t size() const { return DataCount; }
    size_t capacity() const { return MemSize; }
    
};

#endif
