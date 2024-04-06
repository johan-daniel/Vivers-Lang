#include "Token.hpp"

Token::Token(TokenType tType) : tokenType(tType) 
{
}

Token::Token(TokenType tType, std::string val) : tokenType(tType), value(val)
{
}

Token::~Token()
{
}