// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// texpressionanalyzer.h
//
// Copyright (c) Пинежанин Е.С.

#ifndef __TExpressionAnalyzer_H__
#define __TExpressionAnalyzer_H__

#include <iostream>
#include <string>
#include <vector>

class TExpressionAnalyzer {
private:
  std::string Formula;			// входная строка
  std::string PostfixForm;		// постфиксная запись

  void RemoveSpaces(); // удаление пробелов

public:
  TExpressionAnalyzer(const std::string& _Formula);

  bool FormulaChecker();	// проверка правильности расстановки скобок
  void FormulaConverter();	// перевод в постфиксную форму
  int FormulaCalculator();	// вычисление результата

  std::string GetPostfix() const;

};

#endif
