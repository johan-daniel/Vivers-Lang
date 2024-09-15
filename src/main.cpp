#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>

#include "Lexer.hpp"

void run_console();

int main(int argc, char const *argv[])
{
    run_console();

    if(argc < 2) {
        std::cerr << "Incorrect usage. Correct usage : viv {input.viv}" << std::endl;
        return 1;
    }

    if(std::filesystem::path(argv[1]).extension() != ".viv") {
        std::cerr << "Wrong file given. I can only understand .viv files." << std::endl;
        return 1;
    }

    // Read the source file content
    std::ifstream file(argv[1]);
    std::stringstream sstream;
    std::string src_code;
    if(file.is_open()) {
        sstream << file.rdbuf();
        src_code = sstream.str();
    }
    file.close();

    Lexer lexer(src_code);
    std::vector<Token> tokens = lexer.tokenize();

    for(Token t : tokens)
    {
        std::cout << toString(t) << std::endl;
    }

    return 0;
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

        for(Token t : tokens)
        {
            std::cout << toString(t) << std::endl;
        }
    }
}
