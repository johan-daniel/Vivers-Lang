#ifndef __TOKENS_HPP__
#define __TOKENS_HPP__

#include <map>
#include <string>
#include <iostream>
#include <optional>

enum TokenType {
    // Single character tokens
    LPAREN, RPAREN, LBRACK, RBRACK, LBRACE, RBRACE,
    DIV, MUL, PLUS, MINUS, SEMI, COMMA, EXCLAM,
    QUESTION, GT, LT, ASSIGN, COLON,

    // 2 character tokens
    GTE, LTE, EQ, NEQ, OR, AND,
    
    // Literals
    ID, DIGIT, STRING,

    // Keywords
    RETURN, EXIT, IF, ELSE, FUNC,
    TRUE, FALSE, STR, INT, FLOAT,
    DOUBLE, LONG, SHORT, BOOL,
    CHAR,


    ILLEGAL, END
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
    {',', COMMA},
    {':', COLON}
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
    {QUESTION, "QUESTION"},
    {GT, "GT"},
    {LT, "LT"},
    {GTE, "GTE"},
    {LTE, "LTE"},
    {EQ, "EQ"},
    {NEQ, "NEQ"},
    {ASSIGN, "ASSIGN"},
    {IF, "IF"},
    {ELSE, "ELSE"},
    {TRUE, "TRUE"},
    {FALSE, "FALSE"},
    {ILLEGAL, "ILLEGAL"},
    {FUNC, "FUNC"},
    {END, "EOF"},
    {STRING, "STRING_LIT"},
    {STR, "STRING"},
    {INT, "INT"},
    {FLOAT, "FLOAT"},
    {DOUBLE, "DOUBLE"},
    {LONG, "LONG"},
    {BOOL, "BOOL"},
    {CHAR, "CHAR"},
    {COLON, "COLON"}
};

struct Token {
    TokenType token_type;
    std::optional<std::string> lexeme;
    int line;
    void to_string() { 
        std::string value = lexeme.has_value() ? lexeme.value() : "''";
        std::cout << "{ " + TokenTypeToString[token_type] << " at line " << std::to_string(line) << ", Value: " << value << " }\n";
    }
};


#endif