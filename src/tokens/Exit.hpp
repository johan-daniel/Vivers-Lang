#ifndef __EXIT_TOKEN_HPP__
#define __EXIT_TOKEN_HPP__

#include "Token.hpp"

class ExitToken : public Token
{
    public:
        inline ExitToken() : Token(TokenType::EXIT) {}
        inline std::string toString() override { return "{ EXIT }"; }
        inline std::string x86_64() override { return "TODO"; }
};



#endif
