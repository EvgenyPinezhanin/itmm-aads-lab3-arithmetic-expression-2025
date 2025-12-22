#include "texpressionanalyzer.h"
#include <gtest.h>

TEST(TExpressionAnalyzer, can_create_analyzer_with_valid_expression)
{
    ASSERT_NO_THROW(TExpressionAnalyzer a("2+2"));
}

TEST(TExpressionAnalyzer, spaces_are_removed)
{
    TExpressionAnalyzer a("  2  +  2  ");
    // Проверяем косвенно через вычисление
    EXPECT_NO_THROW(a.FormulaCalculator());
}

TEST(TExpressionAnalyzer, can_check_correct_brackets)
{
    TExpressionAnalyzer a("(2+3)*(4-1)");
    EXPECT_TRUE(a.FormulaChecker());
}

TEST(TExpressionAnalyzer, can_detect_incorrect_brackets_extra_closing)
{
    TExpressionAnalyzer a("(2+3))");
    EXPECT_FALSE(a.FormulaChecker());
}

TEST(TExpressionAnalyzer, can_detect_incorrect_brackets_extra_opening)
{
    TExpressionAnalyzer a("((2+3)");
    EXPECT_FALSE(a.FormulaChecker());
}

TEST(TExpressionAnalyzer, can_calculate_simple_addition)
{
    TExpressionAnalyzer a("2+3");
    EXPECT_NEAR(5.0, a.FormulaCalculator(), 0.001);
}

TEST(TExpressionAnalyzer, can_calculate_simple_subtraction)
{
    TExpressionAnalyzer a("5-2");
    EXPECT_NEAR(3.0, a.FormulaCalculator(), 0.001);
}

TEST(TExpressionAnalyzer, can_calculate_simple_multiplication)
{
    TExpressionAnalyzer a("3*4");
    EXPECT_NEAR(12.0, a.FormulaCalculator(), 0.001);
}

TEST(TExpressionAnalyzer, can_calculate_simple_division)
{
    TExpressionAnalyzer a("10/2");
    EXPECT_NEAR(5.0, a.FormulaCalculator(), 0.001);
}

TEST(TExpressionAnalyzer, can_calculate_expression_with_brackets)
{
    TExpressionAnalyzer a("(2+3)*4");
    EXPECT_NEAR(20.0, a.FormulaCalculator(), 0.001);
}

TEST(TExpressionAnalyzer, can_calculate_expression_with_nested_brackets)
{
    TExpressionAnalyzer a("((2+3)*(4-1))");
    EXPECT_NEAR(15.0, a.FormulaCalculator(), 0.001);
}

TEST(TExpressionAnalyzer, can_calculate_expression_with_floats)
{
    TExpressionAnalyzer a("3.5+2.1");
    EXPECT_NEAR(5.6, a.FormulaCalculator(), 0.001);
}

TEST(TExpressionAnalyzer, division_by_zero_throws_exception)
{
    TExpressionAnalyzer a("5/0");
    ASSERT_ANY_THROW(a.FormulaCalculator());
}

TEST(TExpressionAnalyzer, can_calculate_complex_expression)
{
    TExpressionAnalyzer a("2+3*4-6/2");
    // 2 + 12 - 3 = 11
    EXPECT_NEAR(11.0, a.FormulaCalculator(), 0.001);
}

TEST(TExpressionAnalyzer, can_calculate_expression_with_multiple_operations)
{
    TExpressionAnalyzer a("2*3+4*5");
    // 6 + 20 = 26
    EXPECT_NEAR(26.0, a.FormulaCalculator(), 0.001);
}

TEST(TExpressionAnalyzer, can_calculate_expression_with_spaces)
{
    TExpressionAnalyzer a(" 2 + 3 * ( 4 - 1 ) ");
    // 2 + 3 * 3 = 2 + 9 = 11
    EXPECT_NEAR(11.0, a.FormulaCalculator(), 0.001);
}