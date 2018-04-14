#include "Token.hpp"

Token::Token() {};

Token::Token(Token const &src) {
    *this = src;
}

Token::Token(Token::Type type) : type(type), value("") {}

Token::Token(Token::Type type, std::string value) : type(type), value(value) {}

Token   &Token::operator=(Token const &rhs) {
    if (this != &rhs) {
        type = rhs.type;
        value = rhs.value;
    }
    return (*this);
}

Token::~Token() {};
