#include "Lexer.hpp"
#include <cctype>
#include <optional>

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

        // Parse single and 2 characters tokens
        else if(singleCharTokenMap.contains(value))
        {
            char value2 = peek(1).has_value() ? peek(1).value() : ' ';
            if(value == '=')
            {
                if(value2 == '=')
                {
                    tokens.push_back({ EQ, std::nullopt });
                    pop(); pop();
                    continue;
                }
                if(value2 == '!')
                {
                    tokens.push_back({ NEQ, std::nullopt });
                    pop(); pop();
                    continue;
                }
            }
            else if(value == '<')
            {
                if(value2 == '=')
                {
                    tokens.push_back({ LTE, std::nullopt });
                    pop(); pop();
                    continue;
                }
            }
            else if(value == '>')
            {
                if(value2 == '=')
                {
                    tokens.push_back({ GTE, std::nullopt });
                    pop(); pop();
                    continue;
                }
            }
            tokens.push_back({ singleCharTokenMap.at(value), std::nullopt });
            pop();
        }

        // If the word starts with a letter
        else if(std::isalpha(value))
        {
            while(peek().has_value() && std::isalnum(peek().value())) word_buffer.push_back(pop());

            if(word_buffer == "exit") tokens.push_back({ EXIT, std::nullopt });
            if(word_buffer == "return") tokens.push_back({ RETURN, std::nullopt });
            if(word_buffer == "if") tokens.push_back({ IF, std::nullopt });
            if(word_buffer == "else") tokens.push_back({ ELSE, std::nullopt });
            if(word_buffer == "true" || word_buffer == "false") tokens.push_back({ BOOL, word_buffer });
            if(word_buffer == "function") tokens.push_back({ FUNC, std::nullopt });

            word_buffer.clear();
        }

        // If the word starts with a digit
        else if(std::isdigit(value))
        {
            while(peek().has_value() && std::isdigit(peek().value())) word_buffer.push_back(pop());
            tokens.push_back({ DIGIT, word_buffer });
            word_buffer.clear();
        }
    }

    return tokens;
}
