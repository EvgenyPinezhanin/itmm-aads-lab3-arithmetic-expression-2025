// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// texpressionanalyzer.h
//
// Copyright (c) Пинежанин Е.С.

#ifndef __TExpressionAnalyzer_H__
#define __TExpressionAnalyzer_H__

#include <string>

class TExpressionAnalyzer {
private:
    std::string Formula;
    std::string PostfixForm;

    void RemoveSpaces();
    void FormulaConverter();

public:
    TExpressionAnalyzer(const std::string& _Formula = "");

    void SetExpression(const std::string& expr);
    bool FormulaChecker();
    double FormulaCalculator();
    double Calculate();
    std::string GetPostfix() const;
};

#endif