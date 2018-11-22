//
// Created by Alex LAZAREV on 8/12/18.
//

#include <iostream>
#include "../includes/Parser.hpp"
#include "../includes/Lexer.hpp"

int main(int argc, char **argv){

    Lexer *lexer = new Lexer();
    Parser *parser = new Parser();

    if (argc == 1 || argc == 2) {
        try {
            if (argc == 1)
                lexer->readInput();
            else
                lexer->readFile(argv[1]);
            parser->parse((*lexer->getCommand()));
        }
        catch (std::exception &e){
            std::cout << e.what() << std::endl;
        }
    }
    else
        std::cout << "./avm [file]" << std::endl;
    return 0;
}