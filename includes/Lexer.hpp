//
// Created by Alex LAZAREV on 8/12/18.
//

#ifndef VM_LEXER_HPP
#define VM_LEXER_HPP

#include <string>
#include <array>
#include "Command.hpp"

class Lexer {

public:
    Lexer();
    Lexer(Lexer const &src);
    virtual ~Lexer();

    void                    readFile(std::string file);
    void                    readInput();
    std::vector<Command>    *getCommand() const;

    Lexer                   &operator=(Lexer const &src);
private:
    bool                    flag;
    bool                    stop;
    std::vector<Command>    *vector;
    bool                    validation(const std::string &line);
    eOperation              getOperation(std::string const &operation);
    eOperandType            getOperand(std::string const &operand);
    std::string             getValue(std::string const &v1, std::string const &v2);
};


#endif //VM_LEXER_HPP
