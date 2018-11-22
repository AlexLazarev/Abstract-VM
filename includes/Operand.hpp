//
// Created by Alex LAZAREV on 8/13/18.
//

#ifndef VM_OPERAND_HPP
#define VM_OPERAND_HPP


#include <sstream>
#include <iomanip>
#include <cmath>
#include <iostream>
#include "IOperand.hpp"
#include "OperandFactory.hpp"
#include "Exception.hpp"

class Operand : public IOperand{

public:

    Operand();
    Operand(eOperandType type, std::string value);
    Operand(Operand const &operand);

    virtual ~Operand();

    int getPrecision(void) const;

    eOperandType getType(void) const;

    const IOperand *operator+(IOperand const &rhs) const;

    const IOperand *operator-(IOperand const &rhs) const;

    const IOperand *operator*(IOperand const &rhs) const;

    const IOperand *operator/(IOperand const &rhs) const;

    const IOperand *operator%(IOperand const &rhs) const;

    const std::string &toString(void) const;


    Operand &operator=(Operand const &src);
private:
    eOperandType    type;
    std::string     value;

    std::string   validValue(eOperandType type, std::string value_str) const;
};


#endif //VM_OPERAND_HPP
