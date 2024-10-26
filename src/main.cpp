#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>

#include "Lexer.hpp"

void run_console();
void run_file(std::string);

inline void error(int line, std::string err) { 
    std::cerr << "Error on line " << line << " : " << err << std::endl; 
    exit(65);
}

int main(int argc, char const *argv[])
{
    // if(argc < 2) {
    //     std::cerr << "Incorrect usage. Correct usage : viv {input.viv}" << std::endl;
    //     return 1;
    // }
    if(argc == 2) run_file(argv[1]);
    else run_console();

    return 0;
}

void run_file(std::string file_path) {
    if(std::filesystem::path(file_path).extension() != ".viv") {
        std::cerr << "Wrong file given. I can only understand .viv files." << std::endl;
        exit(1);
    }

    // Read the source file content
    std::ifstream file(file_path);
    std::stringstream sstream;
    std::string src_code;
    if(file.is_open()) {
        sstream << file.rdbuf();
        src_code = sstream.str();
    }
    file.close();

    Lexer lexer(src_code);
    std::vector<Token> tokens = lexer.tokenize();

    for(Token t : tokens) t.to_string();
}


void run_console()
{
    const std::string CONSOLE_PROMPT = ">> ";

    bool finished = false;
    std::string line;

    while(!finished)
    {
        std::cout << CONSOLE_PROMPT;
        std::getline(std::cin, line);
        Lexer lexer(line);
        std::vector<Token> tokens = lexer.tokenize();

        for(Token t : tokens) t.to_string();
    }
}