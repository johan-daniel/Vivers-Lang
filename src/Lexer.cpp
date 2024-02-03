#include "Lexer.hpp"
#include <iostream>

Lexer::Lexer(const std::string& src) : src_code(std::move(src)) {}


std::optional<char> Lexer::peek(int offset) const {
    if(cur + offset >= src_code.length()) return {};
    return src_code.at(cur + offset);
}

char Lexer::pop() {
    return src_code.at(cur++);
}

std::vector<Token> Lexer::tokenize() {

    std::vector<Token> tokens;
    std::string wordBuffer;

    // Loop over all the characters in the source code
    while(peek().has_value()) {

        // Ignore spaces
        if(std::isspace(peek().value())) pop();

        // If the first letter of the word is a letter
        else if(std::isalpha(peek().value())) {

            // Read the rest of the word into the buffer
            while(peek().has_value() && std::isalnum(peek().value())) wordBuffer.push_back(pop());

            std::cout << wordBuffer << std::endl;

            // Add the correct token to the tokens list
            if(wordBuffer == "exit") tokens.push_back({TokenType::EXIT});

            wordBuffer.clear();
        }

        else if(std::isdigit(peek().value())) {
            while(peek().has_value() && std::isdigit(peek().value())) wordBuffer.push_back(pop());
            tokens.push_back({TokenType::INT_LITERAL, wordBuffer});
            wordBuffer.clear();
        }

        else if(peek().value() == ';') {
            tokens.push_back({TokenType::SEMI});
            pop();
        }
    }



    return tokens;
}