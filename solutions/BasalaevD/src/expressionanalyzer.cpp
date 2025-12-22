// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// expressionanalyzer.cpp
//
// Copyright (c) Пинежанин Е.С.

#include "texpressionanalyzer.h"
#include "tstack.h"
#include <cctype>
#include <stdexcept>

// Удаление пробелов
void TExpressionAnalyzer::RemoveSpaces()
{
    std::string result;
    for (size_t i = 0; i < Formula.size(); i++) {
        if (Formula[i] != ' ') {
            result += Formula[i];
        }
    }
    Formula = result;
}

// Конструктор
TExpressionAnalyzer::TExpressionAnalyzer(const std::string& _Formula)
    : Formula(_Formula)
{
    RemoveSpaces();
}

// Проверка правильности расстановки скобок
bool TExpressionAnalyzer::FormulaChecker()
{
    TStack<char> stack;
    
    for (size_t i = 0; i < Formula.size(); i++) {
        char c = Formula[i];
        
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
void TExpressionAnalyzer::FormulaConverter()
{
    PostfixForm.clear();
    TStack<char> operators;
    
    for (size_t i = 0; i < Formula.size(); i++) {
        char c = Formula[i];
        
        // Если цифра или точка - собираем всё число
        if (std::isdigit(c) || c == '.') {
            std::string number;
            while (i < Formula.size() && (std::isdigit(Formula[i]) || Formula[i] == '.')) {
                number += Formula[i];
                i++;
            }
            i--; // Возвращаемся на один символ
            
            // Добавляем число в постфиксную форму
            for (char digit : number) {
                PostfixForm.push_back(digit);
            }
            PostfixForm.push_back(' '); // Разделитель
        }
        // Если открывающая скобка
        else if (c == '(') {
            operators.Put(c);
        }
        // Если закрывающая скобка
        else if (c == ')') {
            while (!operators.IsEmpty() && operators.Top() != '(') {
                PostfixForm.push_back(operators.Top());
                PostfixForm.push_back(' ');
                operators.Get();
            }
            if (!operators.IsEmpty()) {
                operators.Get(); // Удаляем '('
            }
        }
        // Если оператор
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            // Определяем приоритет
            int currentPriority = 0;
            if (c == '+' || c == '-') currentPriority = 1;
            else if (c == '*' || c == '/') currentPriority = 2;
            
            // Выталкиваем операторы с большим или равным приоритетом
            while (!operators.IsEmpty() && operators.Top() != '(') {
                char topOp = operators.Top();
                int topPriority = 0;
                if (topOp == '+' || topOp == '-') topPriority = 1;
                else if (topOp == '*' || topOp == '/') topPriority = 2;
                
                if (topPriority >= currentPriority) {
                    PostfixForm.push_back(topOp);
                    PostfixForm.push_back(' ');
                    operators.Get();
                } else {
                    break;
                }
            }
            
            operators.Put(c);
        }
    }
    
    // Выталкиваем оставшиеся операторы
    while (!operators.IsEmpty()) {
        PostfixForm.push_back(operators.Top());
        PostfixForm.push_back(' ');
        operators.Get();
    }
    
    // Убираем последний пробел, если есть
    if (!PostfixForm.empty() && PostfixForm.back() == ' ') {
        PostfixForm.pop_back();
    }
}

// Вычисление результата
double TExpressionAnalyzer::FormulaCalculator()
{
    if (PostfixForm.empty()) {
        FormulaConverter();
    }
    
    TStack<double> stack;
    std::string currentNumber;
    
    for (size_t i = 0; i < PostfixForm.size(); i++) {
        char c = PostfixForm[i];
        
        if (std::isdigit(c) || c == '.') {
            currentNumber += c;
        }
        else if (c == ' ') {
            if (!currentNumber.empty()) {
                stack.Put(std::stod(currentNumber));
                currentNumber.clear();
            }
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            if (stack.IsEmpty()) throw std::runtime_error("Invalid expression");
            double b = stack.Top();
            stack.Get();
            
            if (stack.IsEmpty()) throw std::runtime_error("Invalid expression");
            double a = stack.Top();
            stack.Get();
            
            double result = 0.0;
            if (c == '+') result = a + b;
            else if (c == '-') result = a - b;
            else if (c == '*') result = a * b;
            else if (c == '/') {
                if (b == 0.0) throw std::runtime_error("Division by zero");
                result = a / b;
            }
            
            stack.Put(result);
        }
    }
    
    // Если осталось число (последнее в выражении из одного числа)
    if (!currentNumber.empty()) {
        stack.Put(std::stod(currentNumber));
    }
    
    if (stack.IsEmpty()) {
        throw std::runtime_error("Invalid expression");
    }
    
    return stack.Top();
}