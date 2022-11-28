#include "token.h"

class Lexer
{
private:
    std::string source;
    int current_position = 0;

    // private method that raises an exception
    void raise_error(std::string message)
    {
        throw std::runtime_error(message);
    }

public:
    Lexer() : source(""), current_position(0) {}
    Lexer(std::string source) : source(source) {}

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
};