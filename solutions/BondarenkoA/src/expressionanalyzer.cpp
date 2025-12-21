#include "tstack.h"
#include "texpressionanalyzer.h"

// Реализация конструктора Lexem
Lexem::Lexem(LexemType t, const std::string& v) : type(t), value(v) {}

// Реализация методов-предикатов для определения типа токена в ToPostfix()
bool Lexem::isOperator() const {
    return type == OPERATOR;
}
bool Lexem::isVariable() const {
    return type == VARIABLE;
}
bool Lexem::isFunction() const {
    return type == FUNCTION;
}
bool Lexem::isNumber() const {
    return type == NUMBER;
}
bool Lexem::isUnary() const {
    return type == UNARY_MINUS;
}
bool Lexem::isParenthesis() const {
    return type == LEFT_PAREN || type == RIGHT_PAREN;
}

// Реализация функций-предикатов для определения типа символа входной строки в Parse()
bool isDigit(char ch) {
    return ch >= '0' && ch <= '9';
}
bool isOperator(char ch) {
    return ch == '-' || ch == '+' || ch == '*' || ch == '/';
}
bool isVariable(char ch) {
    return ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z';
}
bool isUnary(char ch) {
    return ch == '-';
}
bool isParenthesis(char ch) {
    return ch == '(' || ch == ')';
}
bool isLeft_Paren(char ch) {
    return ch == '(';
}
bool isRight_Paren(char ch) {
    return ch == ')';
}

// Перегрузка оператора вывода
std::ostream& operator<<(std::ostream& os, const Lexem& lexem) {
    os << lexem.value;
    return os;
}

// Перегрузка оператора ввода
std::istream& operator>>(std::istream& is, Lexem& lexem) {
    std::string value;
    is >> value;

    // Логика для определения типа лексемы

    if (value == "-" &&
        (lexem.value.empty() || lexem.value.back() == '(' ||
            lexem.value.back() == '+' || lexem.value.back() == '-' ||
            lexem.value.back() == '*' || lexem.value.back() == '/')) {
        lexem.type = UNARY_MINUS; // Унарный минус
    }
    else if (value == "+" || value == "-" || value == "*" || value == "/") {
        lexem.type = OPERATOR; // Бинарный оператор
    }
    else if (value == "sin" || value == "cos" || value == "tg" || value == "ctg") {
        lexem.type = FUNCTION;
    }
    else if (value == "(") {
        lexem.type = LEFT_PAREN;
    }
    else if (value == ")") {
        lexem.type = RIGHT_PAREN;
    }
    else if (value.size() > 0 && (value[0] >= 'a' && value[0] <= 'z') || (value[0] >= 'A' && value[0] <= 'Z') || value[0] == '_') {
        lexem.type = VARIABLE; // Переменная
    }
    else {
        lexem.type = NUMBER; // Число
    }

    lexem.value = value;
    //lexem.priority = 0;
    return is;
}


#pragma region Реализация класса TArithmeticExpression

// Конструктор класса TArithmeticExpression
TArithmeticExpression::TArithmeticExpression(string infx) : infix(infx) {
    (*this).Parse();
    (*this).ToPostfix();
}

// Метод для перевода из инфиксного массива токенов в постфиксный, 
// используется после Parse(), который разбивает входную строку на токены в infixTokens
void TArithmeticExpression::ToPostfix()
{
    TStack<Lexem> stack;

    for (const Lexem& token : infixTokens) {
        if (token.isNumber()) {
            // Если это число, добавляем в постфикс
            postfixTokens.push_back(token);
        }
        else if (token.isVariable()) {
            // Если это переменная, добавляем в постфикс (и в вектор переменных)
            postfixTokens.push_back(token);
            //variables.push_back(token);
        }
        else if (token.isUnary()) {//!!!
            // Унарный минус, например, обработаем как оператор
            stack.Push(token);
        }
        else if (token.isParenthesis()) {
            // Обработка скобок
            if (token.type == LEFT_PAREN) {
                stack.Push(token);
            }
            else {
                while (!stack.IsEmpty() && stack.Top().type != LEFT_PAREN) {
                    postfixTokens.push_back(stack.Top());
                    // Обработка исключения для удаления из пустого стека
                    try {
                        stack.Pop();
                    }
                    catch (const std::exception& e) {
                        std::cerr << "Error: " << e.what();
                        std::cerr << "Apparently you've introduced an extra parenthesis." << std::endl;
                        return;
                    }
                }
                try {
                    stack.Pop();  // Убираем открывающую скобку
                }
                catch (const std::exception& e) {
                    std::cerr << "Error: " << e.what();
                    std::cerr << "Apparently you've introduced an extra parenthesis." << std::endl;
                    return;
                }
            }//	Проверяем, содержится ли символ в списке операторов
        }// дальше как-будто костыли
        else if (operationPriority.count(token.value.c_str()[0])) {


            //	Заносим в выходную строку все операторы из стека, имеющие более высокий приоритет
            while (!stack.IsEmpty() && (operationPriority.at(stack.Top().value.c_str()[0]) >= operationPriority.at(token.value.c_str()[0]))) {
                postfixTokens.push_back(stack.Top());
                stack.Pop();
            }
            //	Заносим в стек оператор
            stack.Push(token);
        }
    }
    // Добавляем все оставшиеся операторы в стек в конец
    while (!stack.IsEmpty()) {
        postfixTokens.push_back(stack.Top());
        stack.Pop();
    }
}

void TArithmeticExpression::printPostfix(std::ostream& os) const {          //!!!
    for (const Lexem& token : postfixTokens) {
        os << token.value << " ";
    }
    os << std::endl;
}

// Преобразование строки в число
double TArithmeticExpression::simpleStringToDouble(const std::string& str) {
    double result = 0.0;
    bool isNegative = false;
    size_t i = 0;

    // Обработка отрицательных чисел
    if (str[i] == '-') {
        isNegative = true;
        i++;
    }
    else if (str[i] == '+') {
        i++;
    }

    // Обработка целой части
    while (i < str.length() && isDigit(str[i])) {
        result = result * 10 + (str[i] - '0');
        i++;
    }

    // Обработка десятичной точки и дробной части
    if (i < str.length() && str[i] == '.') {
        i++;
        double decimalPlace = 0.1;
        while (i < str.length() && isDigit(str[i])) {
            result += (str[i] - '0') * decimalPlace;
            decimalPlace /= 10;
            i++;
        }
    }

    // Обработка экспоненты
    if (i < str.length() && (str[i] == 'e' || str[i] == 'E')) {
        i++;
        bool expIsNegative = false;
        if (i < str.length() && str[i] == '-') {
            expIsNegative = true;
            i++;
        }
        else if (i < str.length() && str[i] == '+') {
            i++;
        }

        int exponent = 0;
        while (i < str.length() && isDigit(str[i])) {
            exponent = exponent * 10 + (str[i] - '0');
            i++;
        }

        // Применяем экспоненту
        double expValue = 1.0;
        for (int j = 0; j < exponent; ++j) {
            expValue *= 10.0;

        }
        if (expIsNegative) {
            result /= expValue;
        }
        else {
            result *= expValue;
        }
    }

    // Применяем знак минус, если необходимо
    if (isNegative) {
        result = -result;
    }

    return result;
}

// Метод для записи значений переменных в map<название_переменной, значение> variables
void TArithmeticExpression::setVariables() {
    for (auto iter = variables.begin(); iter != variables.end(); ++iter) {
        cout << "Enter a value of " << iter->first << ": " << endl;
        cin >> iter->second;
        // Проверка корректности ввода
        if (std::cin.fail()) {
            std::cerr << "Error: Invalid input!" << std::endl;
            return;
        }
    }

}

// Парсинг входной строки, токены записываются в infixTokens, если токен - переменная, 
// то она записывается как ключ в map для переменных
void TArithmeticExpression::Parse()
{
    size_t length = infix.length();

    bool isPreviousOperator = true;  // Считываем как унарный минус, если он идет первым

    for (size_t i = 0; i < length; ++i) {
        char symbol = infix.at(i);
        Lexem token;

        if (std::isdigit(symbol)) {
            // Считываем число, в том числе с плавающей запятой и научной нотацией
            size_t j = i;
            bool hasDecimalPoint = false;
            bool hasExponent = false;

            // Считываем цифры до точки или экспонента
            while (j < length && (std::isdigit(infix.at(j)) || infix.at(j) == '.')) {
                if (symbol == '.') {
                    if (hasDecimalPoint) break;  // Если точка уже была, завершаем
                    hasDecimalPoint = true;
                }
                j++;
            }

            // Обрабатываем экспоненциальную часть (e или E)
            if (j < length && (symbol == 'e' || symbol == 'E')) {
                hasExponent = true;
                j++;  // Пропускаем 'e' или 'E'

                // Пропускаем знак экспоненты
                if (j < length && (symbol == '+' || symbol == '-')) {
                    j++;
                }

                // Считываем цифры экспоненты
                while (j < length && std::isdigit(symbol)) {
                    j++;
                }
            }

            token.value = infix.substr(i, j - i);
            token.type = NUMBER;
            infixTokens.push_back(token);
            i = j - 1;
            isPreviousOperator = false;

        }
        else if (isVariable(symbol)) {

            // Считываем переменные
            size_t j = i;
            while (j < length && isVariable(infix.at(j)))
                ++j;
            //token.value = std::string(infix + i, j - i);
            token.value = infix.substr(i, j - i);
            token.type = VARIABLE;
            infixTokens.push_back(token);
            i = j - 1;
            isPreviousOperator = false;

            // записываем в map variavles ключ-переменную и значение по умолчанию
            variables.insert({ token.value, 0.0 });

        }
        else if (isLeft_Paren(symbol)) {
            token.value = symbol;
            token.type = LEFT_PAREN;
            infixTokens.push_back(token);
            isPreviousOperator = true;  // После открывающей скобки может идти оператор
        }
        else if (isRight_Paren(symbol)) {
            token.value = symbol;
            token.type = RIGHT_PAREN;
            infixTokens.push_back(token);
            isPreviousOperator = false;  // После закрывающей скобки не может быть оператора
        }
        else if (isOperator(symbol)) {
            // Это оператор
            token.value = std::string(1, symbol);
            if (isPreviousOperator && isUnary(symbol)) {
                token.type = UNARY_MINUS;  // Унарный минус
            }
            else {
                token.type = OPERATOR;  // Обычный оператор
            }
            infixTokens.push_back(token);
            isPreviousOperator = true;  // Следующий символ может быть числом или переменной

        }
        else {
            // Пропускаем все остальные символы (например, пробелы)
        }
    }
}

vector<Lexem> TArithmeticExpression::GetVariables() const
{
    vector<Lexem> vars;

    for (const auto& key : variables) {
        Lexem var;
        var.value = key.first;
        var.type = VARIABLE;
        vars.push_back(var);
    }

    return vars;
}

// Метод для вычисления выражения
double TArithmeticExpression::evaluate() {
    vector<double> stack;

    for (const Lexem& token : postfixTokens) {
        if (token.isNumber()) {
            stack.push_back(simpleStringToDouble(token.value));
        }
        else if (token.isVariable()) {
            auto it = variables.find(token.value);  // Найдите значение по ключу token.value
            if (it != variables.end()) {            // Если ключ найден
                stack.push_back(it->second);
            }
            else {
                throw std::invalid_argument("Undefined variable: " + token.value);
            }
        }
        else if (token.isUnary()) {
            if (stack.empty())
                throw std::invalid_argument("Insufficient arguments for unary minus");
            double operand = stack.back();
            stack.pop_back();
            stack.push_back(-operand);
        }
        else if (token.isOperator()) {
            if (stack.size() < 2)
                throw std::invalid_argument("Insufficient arguments for operator");
            double right = stack.back(); stack.pop_back();
            double left = stack.back(); stack.pop_back();

            if (token.value == "+") stack.push_back(left + right);
            else if (token.value == "-") stack.push_back(left - right);
            else if (token.value == "*") stack.push_back(left * right);
            else if (token.value == "/") {
                if (right == 0)
                    throw std::invalid_argument("Division by zero");
                stack.push_back(left / right);
            }
        }
    }

    if (stack.size() != 1)
        throw std::invalid_argument("Invalid expression");
    return stack.back();
}

#pragma endregion