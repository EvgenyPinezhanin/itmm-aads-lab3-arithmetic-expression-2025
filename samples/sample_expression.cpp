
        case LEFT_PAREN:
            std::cout << "LEFT_PAREN";
            break;
        case RIGHT_PAREN:
            std::cout << "RIGHT_PAREN";
            break;
        case UNARY_MINUS:
            std::cout << "UNARY_MIN";
            break;
        default:
            std::cout << "UNKNOWN";
            break;
        }
        std::cout << std::endl;
    } // for token in tokens
    try {
        // Устанавливаем переменные в PostfixConverter
        converter.setVariables();

        // Печатаем результат
        std::cout << "Postfix notation: ";
        converter.printPostfix(std::cout);

        // Вычисляем результат
        double result = converter.evaluate();
        std::cout << "Result: " << result << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
};