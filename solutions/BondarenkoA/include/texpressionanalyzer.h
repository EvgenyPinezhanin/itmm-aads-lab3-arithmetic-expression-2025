// объявление функций и классов для вычисления арифметических выражений

#ifndef TEXPRESSIONANALYZER_H
#define TEXPRESSIONANALYZER_H

#include <string>
#include <vector>
#include <cmath>
#include <map>
#include "tstack.h"

// Перечисление для типов лексем
enum LexemType {
	NUMBER,
	VARIABLE,
	FUNCTION,
	OPERATOR,
	UNARY_MINUS,
	LEFT_PAREN,
	RIGHT_PAREN
};

//Класс lexem
class Lexem {
public:
	LexemType type;
	std::string value;

	Lexem(LexemType t = NUMBER, const std::string& v = "");
	bool isOperator() const;
	bool isFunction() const;
	bool isParenthesis() const;
	bool isNumber() const;
	bool isUnary() const;
	bool isVariable() const;

	// перегрузка операторов ввода и вывода
	friend std::ostream& operator<<(std::ostream& os, const Lexem& lexem);
	friend std::istream& operator>>(std::istream& is, Lexem& lexem);
};

class TArithmeticExpression
{
	string infix;						// Инфиксная форма
	vector<Lexem> postfixTokens;		// Вектор лексем в постфиксной форме (их ToPostfix() )
	vector<Lexem> infixTokens;			// Вектор лексем(минимальных единиц вырвжения {переменных, чисел, операторов или скобок})
	std::map<char, int> operationPriority{	// Словарь приорететности операторов
		{'(', 0},
		{'+', 1},
		{'-', 1},
		{'*', 2},
		{'/', 2},
		{'^', 3}
	};
	std::map<std::string, double> variables;	// strind для названий переменных длинны больше 1

	void Parse();		// Разбиение на лексемы
	void ToPostfix();	// Построение постфиксной записи
public:
	TArithmeticExpression(string infx);
	vector<Lexem> GetInfix() const
	{
		return infixTokens;
	} // GetInfix
	vector<Lexem> GetPostfix() const	// добавить определение для возвращения стринга
	{
		return postfixTokens;
	} // GetPostfix

	double evaluate();					// Метод для вычисления выражения

	void setVariables();				// Установить переменные
	vector<Lexem> GetVariables() const;	// Получить переменные
	void printPostfix(std::ostream& os = std::cout) const;
	double simpleStringToDouble(const std::string& str);

};
#endif