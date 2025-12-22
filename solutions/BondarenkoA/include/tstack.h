//// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
////
//// tstack.h
////
//// Copyright (c) Пинежанин Е.С.
//
#ifndef __TStack_H__
#define __TStack_H__

#include <iostream>
#include <cstddef>      
#include <stdexcept> 
#include <utility> 
using namespace std;

const int DefaultMemSize = 1024; // стандартный размер памяти для стека

template <typename T>
class TStack {
    // Отдельный элемент стека содержит в себе значение типа Т 
    // и указательна следующий узел
    struct Node
    {
        T data;
        Node* next;
    };
protected:
    Node* pMem;             // указатель на массив элементов
    size_t MemSize;         // размер памяти для СД
    size_t DataCount;       // количество элементов в СД
    size_t Hi;              // индекс вершины стека

    size_t GetNextIndex(size_t index)         // получить следующий индекс
    {
        return (index + 1) % MemSize;         // Используем %, чтоб не выходить за пределы стека
    }
    size_t GetPrevIndex(size_t index)         // получить предыдущий индекс
    {
        return (index + MemSize - 1) % MemSize;
    }

public:
    TStack(size_t Size = DefaultMemSize) : MemSize(Size)
    {
        if (MemSize <= 0)
            throw out_of_range("Stack size should be greater than zero.\n");
        try {
            pMem = new Node[MemSize]();
        }
        catch (bad_alloc) {
            throw ("Memory error.\n");
        }
        pMem = nullptr;
    }

    ~TStack()
    {
        if (pMem != nullptr)
            delete[] pMem;
        pMem = nullptr;
    }

    bool IsEmpty() const
    {
        return pMem == nullptr;
        //return DataCount == 0;
        //return false;
    }

    bool IsFull() const
    {
        return DataCount == MemSize;
    }

    void Push(const T& Val) // добавить значение
    {
        if (IsFull())
            throw out_of_range("Stack overflow.\n");

        Node* NewNode = new Node;
        NewNode->data = Val;
        NewNode->next = pMem;
        pMem = NewNode;

        Hi = GetNextIndex(Hi);
        ++DataCount;
    }

    void Pop() // извлечь значение
    {
        if (IsEmpty())
            throw out_of_range("Stack underflow.\n");
        Node* DelNode = pMem;
        pMem = DelNode->next;
        delete DelNode;
        //return DelNode->data;
        Hi = GetPrevIndex(Hi);
        --DataCount;
        if (DataCount == 0)
            pMem = nullptr;
    }

    _NODISCARD const T& Top() const // получить значение
    {
        if (IsEmpty())
            throw out_of_range("Stack underflow.\n");

        return pMem[Hi].data;
    }
    _NODISCARD T& Top()  // получить значение
    {
        if (IsEmpty())
            throw out_of_range("Stack underflow.\n");

        return pMem->data;
    }

    // Очистка стека
    void Clear()
    {
        while (!IsEmpty())
        {
            Pop();  // Удаляем все элементы
        }
    }

    size_t size() const { return DataCount; }
    size_t capacity() const { return MemSize; }

    // ввод-вывод стека в консоль
    template<typename T>
    friend istream& operator>>(istream& istr, TStack<T>& st)
    {
        Node* NewNode = new Node;
        for (size_t i = 0; i < st.MemSize; i++)
        {
            istr >> NewNode->data;
            st.Push(NewNode->data);

        }
        return istr;
    }

    template<typename T>
    friend ostream& operator<<(ostream& ostr, const TStack<T>& st)
    {
        Node* NewNode = st.pMem;
        while (NewNode)
        {
            ostr << NewNode->data << " ";
            NewNode = NewNode->next;
        }
        return ostr;
    }
};

#endif