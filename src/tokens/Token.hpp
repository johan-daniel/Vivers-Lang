#ifndef __TOKEN__HPP
#define __TOKEN__HPP

#include <string>
#include <optional>

enum TokenType {
    EXIT,
    INT_LITERAL,
    SEMI
};

class Token {

    protected:
        TokenType tokenType;
        std::optional<std::string> value;

    public:
        Token(TokenType);
        Token(TokenType, std::string);
        ~Token();

        virtual std::string toString() = 0;
        virtual std::string x86_64() = 0;

};


class SemiToken : public Token {
    public:
        inline SemiToken() : Token(TokenType::SEMI) {};
        inline std::string toString() override { return "{ SEMICOLON }"; }
        inline std::string x86_64() override { return "TODO"; }
};


#endif