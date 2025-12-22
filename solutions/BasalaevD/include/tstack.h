// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// tstack.h
//
// Copyright (c) Пинежанин Е.С.

#ifndef __TStack_H__
#define __TStack_H__

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
    TStack(int Size = DefaultMemSize) : MemSize(Size), DataCount(0), Hi(-1)
    {
        if (MemSize <= 0) {
           throw "Stack size must be positive";
        }
        pMem = new T[MemSize];
    }

    ~TStack()
    {
        delete[] pMem;
    }


    bool IsEmpty() const
    {
        return DataCount == 0;
    }

    bool IsFull() const
    {
        return DataCount == MemSize;
    }


    void Put(const T &Val) // добавить значение
    {
        if (IsFull()) {
            throw "Stack overflow";
        }
        
        Hi = GetNextIndex(Hi);
        pMem[Hi] = Val;
        DataCount++;
    }

    T Top() const // получить значение
    {
        if (IsEmpty()) {
            throw "Stack is empty";
        }
        
        return pMem[Hi];
    }   

    void Get() // извлечь значение
    {
        if (IsEmpty()) {
            throw "Stack is empty";
        }
        
        Hi--;
        DataCount--;
    }
};

#endif
