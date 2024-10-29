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

std::optional<Token> Lexer::parseDualCharTokens(const char& char1, int line) {
    std::optional<char> char2 = peek(1);
    std::optional<Token> token = std::nullopt;

    // If no 2nd character was found in the source code abort
    if(!char2.has_value()) return token;

    char char2_val = char2.value();

    if(char1 == '=') {
        if(char2_val == '=') token = { EQ, std::nullopt, line };
        else if(char2_val == '!') token = { NEQ, std::nullopt, line };
    }
    else if(char1 == '<') {
        if(char2_val == '=') token = { LTE, std::nullopt, line };
    }
    else if(char1 == '>') {
        if(char2_val == '=') token = { GTE, std::nullopt, line };
    }

    if(token.has_value()) {
        pop(); pop();
    }

    return token;
}   

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    std::string word_buffer;
    int line = 1;

    // Loop over all the characters in the source code
    while(peek().has_value())
    {
        char value = peek().value();

        if(value == '\n') 
            ++line;

        // Ignore spaces
        if(std::isspace(value)) {
            pop();
            continue;
        }

        // Parse 2 characters tokens
        std::optional<Token> token2chars = parseDualCharTokens(value, line);
        if(token2chars.has_value()) 
            tokens.push_back(token2chars.value());

        // Parse 1 character tokens
        else if(singleCharTokenMap.contains(value)) {
            tokens.push_back({ singleCharTokenMap.at(value), std::nullopt, line });
            pop();
        }

        // Parse String literal
        else if(value == '"') {
            pop();
            while(peek().has_value() && peek().value() != '"') word_buffer.push_back(pop());
            tokens.push_back({ STRING, word_buffer} );
            word_buffer.clear();
            pop();
        }

        // If the word starts with a letter
        else if(std::isalpha(value))
        {
            while(peek().has_value() && (std::isalnum(peek().value()) || peek().value() == '_')) 
                word_buffer.push_back(pop());

            if(word_buffer == "exit") tokens.push_back({ EXIT, std::nullopt, line });
            else if(word_buffer == "return") tokens.push_back({ RETURN, std::nullopt, line });
            else if(word_buffer == "if") tokens.push_back({ IF, std::nullopt, line });
            else if(word_buffer == "else") tokens.push_back({ ELSE, std::nullopt, line });
            else if(word_buffer == "true") tokens.push_back({ TRUE, std::nullopt, line });
            else if(word_buffer == "false") tokens.push_back({FALSE, std::nullopt, line });
            else if(word_buffer == "function") tokens.push_back({ FUNC, std::nullopt, line });
            else if(word_buffer == "str") tokens.push_back({ STR, std::nullopt, line });
            else if(word_buffer == "char") tokens.push_back({ CHAR, std::nullopt, line });
            else if(word_buffer == "int") tokens.push_back({ INT, std::nullopt, line });
            else if(word_buffer == "double") tokens.push_back({ DOUBLE, std::nullopt, line });
            else if(word_buffer == "long") tokens.push_back({ LONG, std::nullopt, line });
            else if(word_buffer == "float") tokens.push_back({ FLOAT, std::nullopt, line });
            else tokens.push_back({ ID, word_buffer, line });

            word_buffer.clear();
        }

        // If the word starts with a digit
        else if(std::isdigit(value))
        {
            TokenType ttype = DIGIT;
            bool decimal_point_found = false;

            while(peek().has_value() && (std::isdigit(peek().value()) || peek().value() == '.')) {
                char x = pop();
                word_buffer.push_back(x);

                if(x == '.') {
                    if(decimal_point_found) ttype = ILLEGAL;
                    else decimal_point_found = true;
                }
            
            } 

            tokens.push_back({ ttype, word_buffer, line });
            word_buffer.clear();
        }
    }

    tokens.push_back({END, std::nullopt, line});

    return tokens;
}
