#ifndef __LEXER__HPP
#define __LEXER__HPP

#include <map>
#include <string>
#include <optional>
#include <vector>

enum TokenType {
    LPAREN,
    RPAREN,
    LBRACK,
    RBRACK,
    LBRACE,
    RBRACE,
    DIGIT,
    PLUS,
    MINUS,
    DIV,
    MUL,
    RETURN,
    ID,
    EXIT,
    SEMI,
    COMMA,
    EXCLAM,
    QUESTION,
    GT,
    LT,
    GTE,
    LTE,
    EQ,
    NEQ,
    ASSIGN,
    IF,
    ELSE,
    BOOL,
    ILLEGAL,
    FUNC
};

static std::map<char, TokenType> singleCharTokenMap = {
    {';', SEMI},
    {'{', LBRACE},
    {'}', RBRACE},
    {'(', LPAREN},
    {')', RPAREN},
    {'[', LBRACK},
    {']', RBRACK},
    {'<', LT},
    {'>', GT},
    {'+', PLUS},
    {'-', MINUS},
    {'/', DIV},
    {'*', MUL},
    {'=', ASSIGN},
    {'!', EXCLAM},
    {'?', QUESTION},
    {',', COMMA}
};

static std::map<TokenType, std::string> TokenTypeToString = {
    {LPAREN, "LPAREN"},
    {RPAREN, "RPAREN"},
    {LBRACK, "LBRACK"},
    {RBRACK, "RBRACK"},
    {LBRACE, "LBRACE"},
    {RBRACE, "RBRACE"},
    {DIGIT, "DIGIT"},
    {PLUS, "PLUS"},
    {MINUS, "MINUS"},
    {DIV, "DIV"},
    {MUL, "MUL"},
    {RETURN, "RETURN"},
    {ID, "ID"},
    {EXIT, "EXIT"},
    {SEMI, "SEMI"},
    {COMMA, "COMMA"},
    {EXCLAM, "EXCLAM"},
    {GT, "GT"},
    {LT, "LT"},
    {GTE, "GTE"},
    {LTE, "LTE"},
    {EQ, "EQ"},
    {NEQ, "NEQ"},
    {ASSIGN, "ASSIGN"},
    {IF, "IF"},
    {ELSE, "ELSE"},
    {BOOL, "BOOL"},
    {ILLEGAL, "ILLEGAL"},
    {FUNC, "FUNC"},
};

struct Token {
    TokenType token_type;
    std::optional<std::string> lexeme;
};

inline std::string toString(Token t) {
    std::string value = t.lexeme.has_value() ? t.lexeme.value() : "''";
    return "{ " + TokenTypeToString[t.token_type] + ", Value: " + value + " }";
}

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

    public:
        Lexer(const std::string& src);

        /**
         * Reads the plain text source code and parse it in tokens.
         * @return Vector of tokens
        */
        std::vector<Token> tokenize();



};


#endif
