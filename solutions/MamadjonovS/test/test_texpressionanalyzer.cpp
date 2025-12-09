#include "texpressionanalyzer.h"

#include <gtest.h>
 
 
//   Создание анализатора с выражением
TEST(TExpressionAnalyzer, Constructor) {
    TExpressionAnalyzer analyzer("2+2");
    // Проверяем, что объект создан
    SUCCEED();
}

//   Проверка правильности скобок (корректное выражение)
TEST(TExpressionAnalyzer, FormulaChecker_Correct) {
    TExpressionAnalyzer analyzer("(2+3)");
    EXPECT_TRUE(analyzer.FormulaChecker());
}

//  Проверка правильности скобок (некорректное выражение)
TEST(TExpressionAnalyzer, FormulaChecker_Incorrect) {
    TExpressionAnalyzer analyzer("(2+3");
    EXPECT_FALSE(analyzer.FormulaChecker());
}

//   Простое сложение
TEST(TExpressionAnalyzer, SimpleAddition) {
    TExpressionAnalyzer analyzer("2+3");
    EXPECT_TRUE(analyzer.FormulaChecker());
    double result = analyzer.FormulaCalculator();
    EXPECT_DOUBLE_EQ(result, 5.0);
}

//   Приоритет операторов (умножение перед сложением)
TEST(TExpressionAnalyzer, OperatorPriority) {
    TExpressionAnalyzer analyzer("2+3*4");
    EXPECT_TRUE(analyzer.FormulaChecker());
    double result = analyzer.FormulaCalculator();
    EXPECT_DOUBLE_EQ(result, 14.0); // 2 + 12 = 14
}

//  Выражение со скобками
TEST(TExpressionAnalyzer, WithParentheses) {
    TExpressionAnalyzer analyzer("(2+3)*4");
    EXPECT_TRUE(analyzer.FormulaChecker());
    double result = analyzer.FormulaCalculator();
    EXPECT_DOUBLE_EQ(result, 20.0); // 5 * 4 = 20
}

//   Деление
TEST(TExpressionAnalyzer, Division) {
    TExpressionAnalyzer analyzer("6/2");
    EXPECT_TRUE(analyzer.FormulaChecker());
    double result = analyzer.FormulaCalculator();
    EXPECT_DOUBLE_EQ(result, 3.0);
}

//  Выражение с пробелами
TEST(TExpressionAnalyzer, WithSpaces) {
    TExpressionAnalyzer analyzer(" 2 + 3 * 4 ");
    EXPECT_TRUE(analyzer.FormulaChecker());
    double result = analyzer.FormulaCalculator();
    EXPECT_DOUBLE_EQ(result, 14.0);
}

//   Несколько операций подряд
TEST(TExpressionAnalyzer, MultipleOperations) {
    TExpressionAnalyzer analyzer("2+3-1");
    EXPECT_TRUE(analyzer.FormulaChecker());
    double result = analyzer.FormulaCalculator();
    EXPECT_DOUBLE_EQ(result, 4.0); // 2 + 3 - 1 = 4
}

//   Деление на ноль
TEST(TExpressionAnalyzer, DivisionByZero) {
    TExpressionAnalyzer analyzer("2/0");
    EXPECT_TRUE(analyzer.FormulaChecker());
    EXPECT_THROW(analyzer.FormulaCalculator(), std::runtime_error);
}

//   Вложенные скобки
TEST(TExpressionAnalyzer, NestedParentheses) {
    TExpressionAnalyzer analyzer("((2+3)*(4-2))");
    EXPECT_TRUE(analyzer.FormulaChecker());
    double result = analyzer.FormulaCalculator();
    EXPECT_DOUBLE_EQ(result, 10.0); // 5 * 2 = 10
}

//  Все операторы вместе
TEST(TExpressionAnalyzer, AllOperators) {
    TExpressionAnalyzer analyzer("2+3*4-6/2");
    EXPECT_TRUE(analyzer.FormulaChecker());
    double result = analyzer.FormulaCalculator();
    EXPECT_DOUBLE_EQ(result, 11.0); // 2 + 12 - 3 = 11
}

//   Выражение из одного числа
TEST(TExpressionAnalyzer, SingleNumber) {
    TExpressionAnalyzer analyzer("5");
    EXPECT_TRUE(analyzer.FormulaChecker());
    double result = analyzer.FormulaCalculator();
    EXPECT_DOUBLE_EQ(result, 5.0);
}

//   Сложное выражение с приоритетами
TEST(TExpressionAnalyzer, ComplexPriority) {
    TExpressionAnalyzer analyzer("2+3*4/2-1");
    EXPECT_TRUE(analyzer.FormulaChecker());
    double result = analyzer.FormulaCalculator();
    EXPECT_DOUBLE_EQ(result, 7.0); // 2 + 6 - 1 = 7
}

//   Несколько скобок и операций
TEST(TExpressionAnalyzer, MultipleParenthesesAndOperations) {
    TExpressionAnalyzer analyzer("(2+3)*(4-1)/(2+1)");
    EXPECT_TRUE(analyzer.FormulaChecker());
    double result = analyzer.FormulaCalculator();
    EXPECT_DOUBLE_EQ(result, 5.0); // 5 * 3 / 3 = 5
}