#ifndef __LEXER__HPP
#define __LEXER__HPP

#include <string>
#include <optional>
#include <vector>

#include "tokens.hpp"

class Lexer {

    private:
        std::string src_code;
        int cur = 0;

        /**
         * Look up the character at the designated offset.
         * May return nothing.
         * Doesn't modify the parent class
         * @param offset Offset
         * @return char | nothing
        */
        std::optional<char> peek(const int offset = 0) const;

        /**
         * Get the character at the current parsing index and increment the index.
         * @return char
        */
        char pop();

        std::optional<Token> parseDualCharTokens(const char& char1);

    public:
        Lexer(const std::string& src);

        /**
         * Reads the plain text source code and parse it in tokens.
         * @return Vector of tokens
        */
        std::vector<Token> tokenize();



};


#endif
