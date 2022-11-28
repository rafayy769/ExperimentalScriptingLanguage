#include <string>

enum class TokenType
{
    // Single-character tokens.
    // Operators
    OPERATOR,
    PLUS, MINUS, MULTIPLY, DIVIDE, MOD,

    // One or two character tokens.

    // Literals.
    NUMBER,

    // Keywords.
    INT, PRINT,

    // None
    NONE, UNKNOWN
};

/**
 * @brief Converts a token type to a string.
 * 
 * @param type 
 * @return std::string 
 */
std::string token_type_to_string(const TokenType& type)
{
    switch (type)
    {
        case TokenType::PLUS: return "PLUS";
        case TokenType::MINUS: return "MINUS";
        case TokenType::MULTIPLY: return "MULTIPLY";
        case TokenType::DIVIDE: return "DIVIDE";
        case TokenType::MOD: return "MOD";
        case TokenType::NUMBER: return "NUMBER";
        case TokenType::INT: return "INT";
        case TokenType::PRINT: return "PRINT";
        default: return "UNKNOWN";
    }
}

class Token
{
    private:
    TokenType type;
    std::string token_value;

    public:
    Token() : type(TokenType::NONE), token_value("") {}
    Token(TokenType type, std::string token_value) : type(type), token_value(token_value) {}
    TokenType get_type() { return this->type; }
    std::string get_token_value() { return token_value; }

    std::string convert_to_string()
    {
        return "Token(" + token_value + ", " + token_type_to_string(type) + ")";
    }

    friend std::ostream& operator<<(std::ostream& os, const Token& token)
    {
        std::string to_print = "Token(" + token.token_value + ", " + token_type_to_string(token.type) + ")";
        os << to_print;
        return os;
    }
};