// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// texpressionanalyzer.cpp
//
// Copyright (c) Пинежанин Е.С.

#include "texpressionanalyzer.h"
#include "tstack.h"
#include <cctype>
#include <stdexcept>
#include <sstream>

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

TExpressionAnalyzer::TExpressionAnalyzer(const std::string& _Formula)
    : Formula(_Formula) {
    RemoveSpaces();
}

void TExpressionAnalyzer::RemoveSpaces() {
    std::string result;
    for (char c : Formula) {
        if (!std::isspace(static_cast<unsigned char>(c))) {
            result += c;
        }
    }
    Formula = result;
}

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

void TExpressionAnalyzer::FormulaConverter() {
    PostfixForm.clear();
    TStack<char> stack;
    std::string currentNumber;
    bool readingNumber = false;

    for (size_t i = 0; i < Formula.length(); i++) {
        char c = Formula[i];

        // Если символ - часть числа (цифра или точка)
        if (std::isdigit(c) || c == '.') {
            currentNumber += c;
            readingNumber = true;
        }
        else {
            // Если до этого читали число, добавляем его
            if (readingNumber) {
                PostfixForm += currentNumber + " ";
                currentNumber.clear();
                readingNumber = false;
            }

            if (c == '(') {
                stack.Put(c);
            }
            else if (c == ')') {
                // Выталкиваем все операторы до открывающей скобки
                while (!stack.IsEmpty() && stack.Top() != '(') {
                    PostfixForm += stack.Top();
                    PostfixForm += " ";
                    stack.Get();
                }
                if (!stack.IsEmpty()) {
                    stack.Get(); // Удаляем '('
                }
            }
            else if (IsOperator(c)) {
                // Выталкиваем операторы с более высоким или равным приоритетом
                while (!stack.IsEmpty() && GetPriority(stack.Top()) >= GetPriority(c)) {
                    PostfixForm += stack.Top();
                    PostfixForm += " ";
                    stack.Get();
                }
                stack.Put(c);
            }
        }
    }

    // Добавляем оставшееся число, если есть
    if (!currentNumber.empty()) {
        PostfixForm += currentNumber + " ";
    }

    // Выталкиваем все оставшиеся операторы из стека
    while (!stack.IsEmpty()) {
        PostfixForm += stack.Top();
        PostfixForm += " ";
        stack.Get();
    }

    // Удаляем последний пробел, если есть
    if (!PostfixForm.empty() && PostfixForm.back() == ' ') {
        PostfixForm.pop_back();
    }
}

double TExpressionAnalyzer::FormulaCalculator() {
    if (PostfixForm.empty()) {
        FormulaConverter();
    }

    TStack<double> stack;
    std::istringstream iss(PostfixForm);
    std::string token;

    while (iss >> token) {
        // Проверяем, является ли токен оператором
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            // Проверяем, достаточно ли операндов в стеке
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
            if (token == "+") {
                result = a + b;
            }
            else if (token == "-") {
                result = a - b;
            }
            else if (token == "*") {
                result = a * b;
            }
            else if (token == "/") {
                if (b == 0.0) {
                    throw std::runtime_error("Division by zero");
                }
                result = a / b;
            }
            stack.Put(result);
        }
        else {
            // Это число
            try {
                double num = std::stod(token);
                stack.Put(num);
            }
            catch (const std::exception& e) {
                throw std::runtime_error("Invalid number in expression");
            }
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

void TExpressionAnalyzer::SetExpression(const std::string& expr) {
    Formula = expr;
    RemoveSpaces();
    PostfixForm.clear();
}

double TExpressionAnalyzer::Calculate() {
    return FormulaCalculator();
}

std::string TExpressionAnalyzer::GetPostfix() const {
    return PostfixForm;
}