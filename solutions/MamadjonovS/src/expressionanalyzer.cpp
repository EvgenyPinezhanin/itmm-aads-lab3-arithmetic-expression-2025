// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// texpressionanalyzer.cpp
//
// Copyright (c) Пинежанин Е.С.

#include "texpressionanalyzer.h"
#include "tstack.h"
#include <cctype>
#include <stdexcept>

bool IsOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int GetPriority(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

 
// Конструктор (исправляем синтаксическую ошибку)
TExpressionAnalyzer::TExpressionAnalyzer(const std::string& _Formula)
    : Formula(_Formula) {
    RemoveSpaces();
}

// Удаление пробелов
void TExpressionAnalyzer::RemoveSpaces() {
    std::string result;
    for (char c : Formula) {
        if (!std::isspace(static_cast<unsigned char>(c))) {
            result += c;
        }
    }
    Formula = result;
}

// Проверка правильности скобок
bool TExpressionAnalyzer::FormulaChecker() {
    TStack<char> stack;
    for (char c : Formula) {
        if (c == '(') {
            stack.Put(c);
        }
        else if (c == ')') {
            if (stack.IsEmpty()) {
                return false;
            }
            stack.Get();
        }
    }
    return stack.IsEmpty();
}

// Перевод в постфиксную форму
void TExpressionAnalyzer::FormulaConverter() {
    PostfixForm.clear();
    TStack<char> stack;

    for (char c : Formula) {
        if (std::isdigit(c)) {
            PostfixForm.push_back(c);
        }
        else if (c == '(') {
            stack.Put(c);
        }
        else if (c == ')') {
            while (!stack.IsEmpty() && stack.Top() != '(') {
                PostfixForm.push_back(stack.Top());
                stack.Get();
            }
            if (!stack.IsEmpty()) {
                stack.Get(); // Удаляем '('
            }
        }
        else if (IsOperator(c)) {
            while (!stack.IsEmpty() && IsOperator(stack.Top()) &&
                GetPriority(stack.Top()) >= GetPriority(c)) {
                PostfixForm.push_back(stack.Top());
                stack.Get();
            }
            stack.Put(c);
        }
    }

    while (!stack.IsEmpty()) {
        PostfixForm.push_back(stack.Top());
        stack.Get();
    }
}

// Вычисление результата
double TExpressionAnalyzer::FormulaCalculator() {
 
    if (PostfixForm.empty()) {
        FormulaConverter();
    }

    TStack<double> stack;

    for (char c : PostfixForm) {
        if (std::isdigit(c)) {
            stack.Put(static_cast<double>(c - '0'));
        }
        else if (IsOperator(c)) {
            if (stack.IsEmpty()) {
                throw std::runtime_error("Not enough operands");
            }
            double b = stack.Top();
            stack.Get();

            if (stack.IsEmpty()) {
                throw std::runtime_error("Not enough operands");
            }
            double a = stack.Top();
            stack.Get();

            double result;
            switch (c) {
            case '+':
                result = a + b;
                break;
            case '-':
                result = a - b;
                break;
            case '*':
                result = a * b;
                break;
            case '/':
                if (b == 0.0) {
                    throw std::runtime_error("Division by zero");
                }
                result = a / b;
                break;
            default:
                throw std::runtime_error("Unknown operator");
            }

            stack.Put(result);
        }
    }

    if (stack.IsEmpty()) {
        throw std::runtime_error("No result");
    }

    double result = stack.Top();
    stack.Get();

    if (!stack.IsEmpty()) {
        throw std::runtime_error("Too many values in stack");
    }

    return result;
}