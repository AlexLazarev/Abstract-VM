//
// Created by Alex LAZAREV on 8/12/18.
//

#ifndef VM_SCOMMAND_HPP
#define VM_SCOMMAND_HPP

#include "eOperation.hpp"
#include "eOperandType.hpp"

struct Command {
    eOperation      operation;
    eOperandType    operand;
    std::string     value;
};

#endif //VM_SCOMMAND_HPP
