#include "texpressionanalyzer.h"

#include <gtest.h>
#include <string.h>

TEST(TExpressionAnalyzer, can_work_formulaconverter)
{
    TExpressionAnalyzer expr("(a + 31) * 5 - 2 * b");
    expr.FormulaConverter();
    EXPECT_EQ("a 31 + 5 * 2 b * - ", expr.GetPostfix());
}

TEST(TExpressionAnalyzer, cant_work_formulaconverter_with_empty_string) {
    TExpressionAnalyzer expr("");
    ASSERT_ANY_THROW(expr.FormulaConverter());
}

TEST(TExpressionAnalyzer, can_work_numeric_calculation)
{
    TExpressionAnalyzer expr("(1 + 3) * 5 - 2 * 4");
    expr.FormulaConverter();                     
    int result = 0;
    ASSERT_NO_THROW(result = expr.FormulaCalculator());
    EXPECT_EQ(12, result);
}

TEST(TExpressionAnalyzer, can_work_numbers_with_multiply_digits_calculation)
{
    TExpressionAnalyzer expr("(243 + 31) * 5 - 48 / 12");
    expr.FormulaConverter();
    int result = 0;
    ASSERT_NO_THROW(result = expr.FormulaCalculator());
    EXPECT_EQ(1366, result);
}

TEST(TExpressionAnalyzer, can_work_integer_division_calculation)
{
    TExpressionAnalyzer expr("38 % 12");
    expr.FormulaConverter();
    int result = 0;
    ASSERT_NO_THROW(result = expr.FormulaCalculator());
    EXPECT_EQ(2, result);
}

TEST(TExpressionAnalyzer, cant_work_integer_division_by_zero_calculation)
{
    TExpressionAnalyzer expr("38 % 0");
    expr.FormulaConverter();
    int result = 0;
    ASSERT_ANY_THROW(result = expr.FormulaCalculator());
}

TEST(TExpressionAnalyzer, cant_work_numeric_calculation_when_formula_is_incorrect) {
    TExpressionAnalyzer expr("(1 + )");
    expr.FormulaConverter();
    ASSERT_ANY_THROW(expr.FormulaCalculator());
}

TEST(TExpressionAnalyzer, cant_work_numeric_calculation_when_div_by_zero) {
    TExpressionAnalyzer expr("(4 / 0)");
    expr.FormulaConverter();
    ASSERT_ANY_THROW(expr.FormulaCalculator());
}


TEST(TExpressionAnalyzer, cant_work_numeric_calculation_when_letters_with_numbers)
{
    TExpressionAnalyzer expr("a + 1");
    expr.FormulaConverter();
    ASSERT_ANY_THROW(expr.FormulaCalculator());
}

TEST(TExpressionAnalyzer, can_formula_checker_returns_true_for_correct)
{
    TExpressionAnalyzer expr("((1+2) * (3+4))");
    EXPECT_TRUE(expr.FormulaChecker());
}

TEST(TExpressionAnalyzer, can_formula_checker_returns_false_for_incorrect)
{
    TExpressionAnalyzer expr("((1+2) * (3+4)");
    EXPECT_FALSE(expr.FormulaChecker());

    TExpressionAnalyzer expr2(")1+2(");
    EXPECT_FALSE(expr2.FormulaChecker());
}

