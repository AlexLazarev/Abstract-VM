//
// Created by Alex LAZAREV on 8/13/18.
//

#include <iostream>
#include "../includes/OperandFactory.hpp"

OperandFactory::OperandFactory() {
}

OperandFactory::OperandFactory(OperandFactory const &src) {
    *this = src;
}

OperandFactory::~OperandFactory() {

}

OperandFactory &OperandFactory::operator=(OperandFactory const &src) {
    if (this != &src){

    }
    return *this;
}

IOperand const *OperandFactory::createOperand(eOperandType type, std::string const &value) const {
    switch (type) {
        case Int8:
            return createInt8(value);
        case Int16:
            return createInt16(value);
        case Int32:
            return createInt32(value);
        case Float:
            return createFloat(value);
        case Double:
            return createDouble(value);
    }
    return nullptr;
}

IOperand const *OperandFactory::createInt8(std::string const &value) const {
    return new Operand(Int8, value);
}

IOperand const *OperandFactory::createInt16(std::string const &value) const {
    return new Operand(Int16, value);
}

IOperand const *OperandFactory::createInt32(std::string const &value) const {
    return new Operand(Int32, value);
}

IOperand const *OperandFactory::createFloat(std::string const &value) const {
    return new Operand(Float, value);
}

IOperand const *OperandFactory::createDouble(std::string const &value) const {
    return new Operand(Double, value);
}