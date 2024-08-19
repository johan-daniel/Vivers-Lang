#include "Lexer.hpp"
#include <cctype>

Lexer::Lexer(const std::string& src) : src_code(std::move(src)) {}


std::optional<char> Lexer::peek(int offset) const {
    if(cur + offset >= src_code.length()) return std::nullopt;
    return src_code.at(cur + offset);
}

char Lexer::pop() {
    return src_code.at(cur++);
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    std::string word_buffer;

    // Loop over all the characters in the source code
    while(peek().has_value())
    {
        char value = peek().value();

        // Ignore spaces
        if(std::isspace(value)) pop();

        else if(value == ';')
        {
            tokens.push_back({ SEMI, std::nullopt });
            pop();
        }
        else if(value == '{')
        {
            tokens.push_back({ LBRACE, std::nullopt });
            pop();
        }
        else if(value == '}')
        {
            tokens.push_back({ RBRACE, std::nullopt });
            pop();
        }

        // If the word starts with a letter
        else if(std::isalpha(value))
        {
            while(peek().has_value() && std::isalnum(peek().value())) word_buffer.push_back(pop());

            if(word_buffer == "exit") tokens.push_back({ EXIT, std::nullopt });
            word_buffer.clear();
        }

        else if(std::isdigit(value))
        {
            while(peek().has_value() && std::isdigit(peek().value())) word_buffer.push_back(pop());
            tokens.push_back({ DIGIT, word_buffer });
            word_buffer.clear();
        }
    }

    return tokens;
}
