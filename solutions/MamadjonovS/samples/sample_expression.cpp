// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Тестирование вычисления выражений
//
// Copyright (c) Пинежанин Е.С.

#include <iostream>
#include <string>

#include "tstack.h"

#include "texpressionanalyzer.h"

void main()
{
  std::string formula = "(4 * 5 + 7) + (20 - 3 * 8)";
  int correct_res = 29;

  TExpressionAnalyzer analyzer(formula);

  if (!analyzer.FormulaChecker()) {
    std::cout << "Error: formula isn't correct\n";
    return;
  }

  analyzer.FormulaConverter();

  int res = analyzer.FormulaCalculator();

  if (res == correct_res) {
    std::cout << "Answer: " << res << "\n";
  } else {
    std::cout << "Error: answer isn't correct\n";
  }
}
