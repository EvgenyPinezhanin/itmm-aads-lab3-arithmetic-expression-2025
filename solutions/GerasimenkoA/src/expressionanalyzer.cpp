// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// texpressionanalyzer.cpp
//
// Copyright (c) Пинежанин Е.С.

#include <texpressionanalyzer.h>
#include <tstack.h>

#include <algorithm> 
#include <cctype>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>

using namespace std;

void TExpressionAnalyzer::RemoveSpaces()
{
    string result;
    
    for (size_t i = 0; i < Formula.length(); i++) {
        if (Formula[i] != ' ') {
            result.push_back(Formula[i]);
        }
    }

    Formula = result;

}

TExpressionAnalyzer::TExpressionAnalyzer(const string& _Formula) : Formula(_Formula)
{
    RemoveSpaces();
    PostfixForm.clear();
}

bool TExpressionAnalyzer::FormulaChecker()
{
    TStack<char> st(Formula.size());
    for (size_t i = 0; i < Formula.length(); i++) {
        char c = Formula[i];
        if (c == '(') st.Push(c); 
        else if (c == ')') {
            if (st.IsEmpty())
                return false;
            st.Pop();
        }
    }
    return st.IsEmpty();
}

static int Prior(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/' || op == '%') return 2;
    if (op == '(') return 0;
    return -1;
}

void TExpressionAnalyzer::FormulaConverter()
{
    PostfixForm.clear();
    TStack<char> st(Formula.size()); 

    size_t i = 0;
    while (i < Formula.size()) {
        char c = Formula[i];
       
        if (isdigit(static_cast<unsigned char>(c))) {
            string num;
            while (i < Formula.size() && isdigit(static_cast<unsigned char>(Formula[i]))) {
                num.push_back(Formula[i]);
                ++i;
            }
            PostfixForm += num;
            PostfixForm.push_back(' ');
            continue;
        }

        if (isalpha(static_cast<unsigned char>(c))) {
            string abc;
            while (i < Formula.size() && isalnum(static_cast<unsigned char>(Formula[i]))) {
                abc.push_back(Formula[i]);
                ++i;
            }
            PostfixForm += abc;
            PostfixForm.push_back(' ');
            continue;
        }


        if (c == '(') { // '('
            st.Push(c);
            ++i;
            continue;
        }

        if (c == ')') { // ')'
            while (!st.IsEmpty() && st.Top() != '(') {
                PostfixForm.push_back(st.Top());
                PostfixForm.push_back(' ');
                st.Pop();
            }
            // убрал '('
            if (!st.IsEmpty() && st.Top() == '(') st.Pop();
            ++i;
            continue;
        }

        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%') {
            while (!st.IsEmpty() && Prior(c) <= Prior(st.Top())) {
                if (st.Top() == '(') break;
                PostfixForm.push_back(st.Top());
                PostfixForm.push_back(' ');
                st.Pop();
            }
            st.Push(c);
            ++i;
            continue;
        }
        ++i;
    }
    while (!st.IsEmpty()) {
        if (st.Top() == '(') { st.Pop(); continue; }
        PostfixForm.push_back(st.Top());
        PostfixForm.push_back(' ');
        st.Pop();
    }
}

string TExpressionAnalyzer::GetPostfix() const
{
    return PostfixForm;
}

//добавить остаток от деления. Убрать дабл деление, работаем в интах.

int TExpressionAnalyzer::FormulaCalculator()
{
    string pf = GetPostfix();
    if (pf.empty()) throw out_of_range("Empty postfix expression");

    TStack<int> st(pf.size() ? pf.size() : 1);

    istringstream iss(pf);
    string token;
    while (iss >> token) {
        if (!token.empty() && (isdigit(static_cast<unsigned char>(token[0])))) {
            int value = stoi(token);
            st.Push(value);
        }
        else if (token.size() == 1) {
            char ch = token[0];
            if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%') {
                if (st.IsEmpty()) throw out_of_range("Calculation error");
                int right = st.Top(); st.Pop();
                if (st.IsEmpty())  throw out_of_range("Calculation error");
                int left = st.Top(); st.Pop();
                int result = 0;
                switch (ch) {
                case '+':
                    result = left + right;
                    break;
                case '-':
                    result = left - right;
                    break;
                case '*':
                    result = left * right;
                    break;
                case '/':
                    if (right == 0) throw out_of_range("Division by zero");
                    result = left / right;
                    break;
                case '%':
                    if (right == 0) throw out_of_range("Modul by zero");
                    result = left % right;
                    break;
                default:
                    throw out_of_range("Unknown operator");
                }
                st.Push(result);
            }
            else {
                throw out_of_range("Unknown token in postfix: " + token);
            }
        }
    }
    if (st.IsEmpty())  throw out_of_range("Empty result");
    int finalResult = st.Top();
    st.Pop();
    if (!st.IsEmpty()) throw out_of_range("Extra items in stack");
    return finalResult;
}
