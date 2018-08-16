#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cctype>

/*
 * A tiny recursive-descent parser which uses
 * syntax-directed translation to convert infix
 * expressions to postfix using the following production
 * rules and translation scheme.
 * 
 * ===================================
 *         PRODUCTION RULES
 * ===================================
 * expr   -> expr + term | expr - term | term
 * term   -> term * factor | term / factor | factor
 * factor -> (expr) | digit
 * digit  -> 0|1|2|3|4|5|6|7|8|9
 * 
 * ===================================
 *        TRANSLATION SCHEME
 * ===================================
 * 
 * expr -> expr + term {print("+")}
 *       | expr - term {print("-")}
 *       | term
 * 
 * term -> term * factor {print("*")}
 *       | term / factor {print("/")}
 *       | factor
 * 
 * factor -> (expr) | digit
 * 
 * digit  -> 0 {print("0")}
 *         | 1 {print("1")}
 *         ...
 *         ...
 *         | 9 {print("9")} 
 * 
 * ==================================
 *    ELIMINATING LEFT RECURSION
 * ==================================
 * 
 * expr  -> term expr'
 * expr' -> +  term {print("+")} expr'
 *        | -  term {print("-")} expr'
 *        | epsilon
 * term  -> factor term'
 * term' -> *  factor {print("*")} term'
 *        | /  factor {print("/")} term'
 *        | epsilon
 * factor -> (expr) | digit
 * digit  -> 0 {print("0")}
 *         | 1 {print("1")}
 *         ...
 *         ...
 *         | 9 {print("9")}
 */
class Parser {
    public:

    Parser() {
        std::string str;
        std::cout << "Enter infix string : ";
        std::cin >> str;
        stream = std::stringstream(str);
        lookahead = stream.get();
    }

    void parse() {
        expr();
        print_translated_string();
    }

    private:
    
    char lookahead;
    std::string translated;
    std::stringstream stream;

    void display(char terminal) {
        translated += terminal;
    }

    void print_translated_string() {
        std::cout << translated << std::endl; 
    }

    std::string error_message(char lookahead) {
        return "Syntax error near " + std::string(1, lookahead);
    }

    void match(char terminal) {
        if (terminal == lookahead) {
            lookahead = stream.get();
        }
        else {
            throw std::invalid_argument(error_message(lookahead));
        }
    }

    void digit() {
        display(lookahead);
        match(lookahead);
    }

    void factor() {
        if (isdigit(lookahead)) {
            digit();
        }
        else if (lookahead == '(') {
            match('(');
            expr();
            match(')');
        }
        else {
            throw std::invalid_argument(error_message(lookahead));
        }
    }

    void term() {
        factor();

        while (true) {
            if (lookahead == '*') {
                match('*');
                factor();
                display('*');
            }
            else if (lookahead == '/') {
                match('/');
                factor();
                display('/');
            }
            else {
                return;
            }
        }
    }

    void expr() {
        term();

        while (true) {
            if (lookahead == '+') {
                match('+');
                term();
                display('+');
            }
            else if (lookahead == '-') {
                match('-');
                term();
                display('-');
            }
            else {
                return;
            }
        }
    }
};
