#include "token.h"
#include <vector>
#include <iostream>

class Interpreter
{
private:
    std::string source;
    int current_position = 0;
    Token current_token;

    // private method that raises an exception
    void raise_error(std::string message)
    {
        throw std::runtime_error(message);
    }

    // private method eat


public:
    Interpreter() : source(""), current_position(0), current_token() {}
    Interpreter(std::string source) : source(source) {}

    void set_source(std::string source)
    {
        this->source = source;
        this->current_position = 0;
    }

    /**
     * @brief Returns the next token. We can assume all tokens are separated by a space, and tokens end at the end of the line.
     * 
     * @return Token 
     */
    Token get_next_token()
    {
        // Check if we are at the end of the source
        if (current_position >= static_cast<int>(source.length()))
        {
            return Token(TokenType::NONE, "");
        }

        if (source[current_position] == ' ')
        {
            current_position++;
            return get_next_token();
        }

        // Get the current character
        char current_char = source[current_position];

        // Check if the current character is a digit
        if (isdigit(current_char))
        {
            // Get the whole number
            std::string number = "";
            while (isdigit(current_char))
            {
                number += current_char;
                current_position++;
                current_char = source[current_position];
            }

            // Return the number token
            return Token(TokenType::NUMBER, number);
        }

        // Check if the current character is a plus
        if (current_char == '+')
        {
            current_position++;
            return Token(TokenType::PLUS, "+");
        }

        // Check if the current character is a minus
        if (current_char == '-')
        {
            current_position++;
            return Token(TokenType::MINUS, "-");
        }

        // Check if the current character is a multiply
        if (current_char == '*')
        {
            current_position++;
            return Token(TokenType::MULTIPLY, "*");
        }

        // Check if the current character is a divide
        if (current_char == '/')
        {
            current_position++;
            return Token(TokenType::DIVIDE, "/");
        }

        // Check if the current character is a mod
        if (current_char == '%')
        {
            current_position++;
            return Token(TokenType::MOD, "%");
        }

        return Token(TokenType::UNKNOWN, "");
    }

    void eat(const TokenType& token_to_comp)
    {
        if (current_token.get_type() == token_to_comp)
        {
            current_token = get_next_token();
        }
        else
        {
            raise_error("Invalid syntax: Next token is not " + token_type_to_string(token_to_comp));
        }
    }

    int evaluate_expression()
    {
        current_token = get_next_token();
        Token left = current_token;

        eat(TokenType::NUMBER);

        Token op = current_token;
        if (op.get_type() == TokenType::PLUS)
        {
            eat(TokenType::PLUS);
        }
        else if (op.get_type() == TokenType::MINUS)
        {
            eat(TokenType::MINUS);
        }
        else if (op.get_type() == TokenType::MULTIPLY)
        {
            eat(TokenType::MULTIPLY);
        }
        else if (op.get_type() == TokenType::DIVIDE)
        {
            eat(TokenType::DIVIDE);
        }
        else if (op.get_type() == TokenType::MOD)
        {
            eat(TokenType::MOD);
        }
        else
        {
            raise_error("Invalid syntax: Expected an operator");
        }

        Token right = current_token;

        eat(TokenType::NUMBER);

        int left_value = std::stoi(left.get_token_value());
        int right_value = std::stoi(right.get_token_value());

        if (op.get_type() == TokenType::PLUS)
        {
            return left_value + right_value;
        }
        else if (op.get_type() == TokenType::MINUS)
        {
            return left_value - right_value;
        }
        else if (op.get_type() == TokenType::MULTIPLY)
        {
            return left_value * right_value;
        }
        else if (op.get_type() == TokenType::DIVIDE)
        {
            return left_value / right_value;
        }
        else if (op.get_type() == TokenType::MOD)
        {
            return left_value % right_value;
        }
        else
        {
            raise_error("Invalid syntax");
        }
    }

    void interpret()
    {
        std::cout << evaluate_expression() << std::endl;
    }
};