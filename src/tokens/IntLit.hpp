#ifndef __INT_LIT_HPP__
#define __INT_LIT_HPP__

#include "Token.hpp"

class IntLitToken : public Token
{
    public:
        inline IntLitToken(std::string val): Token(TokenType::INT_LITERAL, val) {};
        inline std::string toString() override { return "{ INT_LITERAL: " + value.value() + " }"; };
        std::string x86_64() override { return "TODO"; };
};


#endif