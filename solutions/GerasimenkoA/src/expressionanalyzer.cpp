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

}

double TExpressionAnalyzer::FormulaCalculator()
{
    return 0.0;
}
