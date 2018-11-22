//
// Created by Alex LAZAREV on 8/12/18.
//

#ifndef VM_PARSER_H
#define VM_PARSER_H

#include <string>
#include <forward_list>
#include "Command.hpp"
#include "Operand.hpp"
#include "OperandFactory.hpp"

class Parser {

public:
    Parser();
    Parser(Parser const &src);
    virtual ~Parser();

    void    parse(std::vector<Command> const &command);

    Parser  &operator=(Parser const &src);

private:
    OperandFactory                          factory;
    std::forward_list<IOperand const *>     stack;
    size_t                                  size;
    void                                    action(eOperation operation);
    std::string                             min();
    std::string                             max();
};


#endif //VM_PARSER_H
