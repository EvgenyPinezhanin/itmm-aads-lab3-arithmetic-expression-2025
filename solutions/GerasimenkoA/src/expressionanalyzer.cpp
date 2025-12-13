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
    if (op == '*' || op == '/') return 2;
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
       
        if (isalnum(static_cast<unsigned char>(c))) {
            PostfixForm.push_back(c);
            ++i;
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
                st.Pop();
            }
            // убрал '('
            if (!st.IsEmpty() && st.Top() == '(') st.Pop();
            ++i;
            continue;
        }

        if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (!st.IsEmpty() && Prior(c) <= Prior(st.Top())) {
                PostfixForm.push_back(st.Top());
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
        st.Pop();
    }
}

string TExpressionAnalyzer::GetPostfix() const
{
    return string(PostfixForm.begin(), PostfixForm.end());
}

//добавить остаток от деления. Убрать дабл деление, работаем в интах.

double TExpressionAnalyzer::FormulaCalculator()
{
    string pf = GetPostfix();
    TStack<double> st(pf.size() ? pf.size() : 1);
    

    for (size_t i = 0; i < pf.size(); ++i) {
        char ch = pf[i];
        if (isdigit(ch)) {
            double value = double(ch - '0');
            st.Push(value);
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            if (st.IsEmpty()) throw out_of_range("Calculation error");
            double right = st.Top();
            st.Pop();
            if (st.IsEmpty())  throw out_of_range("Calculation error");
            double left = st.Top();
            st.Pop();
            double result = 0.0;

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
                if (right == 0.0) throw out_of_range("Calculation error");
                result = left / right;
            }
            st.Push(result);
        }
    }
    if (st.IsEmpty())  throw out_of_range("Empty result");
    double finalResult = st.Top();
    st.Pop();
    if(!st.IsEmpty()) throw out_of_range("Extra items in stack");
    return finalResult;
}
