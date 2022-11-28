#include "lexer.h"
#include <vector>
#include <iostream>

class Interpreter
{
private:
    Lexer lexer;
    Token current_token;

    // private method that raises an exception
    void raise_error(std::string message)
    {
        throw std::runtime_error(message);
    }

    // private method eat
    void eat(const TokenType &token_to_comp)
    {
        if (current_token.get_type() == token_to_comp)
        {
            current_token = lexer.get_next_token();
        }
        else
        {
            raise_error("Invalid syntax: Next token is not " + token_type_to_string(token_to_comp));
        }
    }

public:
    Interpreter() : lexer() {}
    Interpreter(std::string source)
    {
        lexer = Lexer(source);
        current_token = lexer.get_next_token();
    }

    void set_source(std::string source)
    {
        this->lexer.set_source(source);
    }

    int factor()
    {
        Token token = current_token;
        eat(TokenType::NUMBER);
        return std::stoi(token.get_token_value());
    }

    int term()
    {
        int result = factor();

        while (current_token.get_type() == TokenType::MULTIPLY || current_token.get_type() == TokenType::DIVIDE)
        {
            Token token = current_token;
            if (token.get_type() == TokenType::MULTIPLY)
            {
                eat(TokenType::MULTIPLY);
                result *= factor();
            }
            else if (token.get_type() == TokenType::DIVIDE)
            {
                eat(TokenType::DIVIDE);
                result /= factor();
            }
        }

        return result;
    }

    int evaluate_expression()
    {
        // Get the first term
        int result = factor();

        // Loop through the rest of the tokens
        while (current_token.get_type() == TokenType::PLUS || current_token.get_type() == TokenType::MINUS)
        {
            Token op = current_token;
            if (op.get_type() == TokenType::PLUS)
            {
                eat(TokenType::PLUS);
                result += term();
            }
            else if (op.get_type() == TokenType::MINUS)
            {
                eat(TokenType::MINUS);
                result -= term();
            }
            else
            {
                raise_error("Invalid syntax: Unknown operator " + op.get_token_value() + " after a number");
            }
        }
        

        return result;
    }

    void interpret()
    {
        std::cout << evaluate_expression() << std::endl;
    }
};