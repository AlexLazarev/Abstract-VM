//
// Created by Alex LAZAREV on 8/15/18.
//

#include "../includes/Operand.hpp"

Operand::Operand() {}

Operand::Operand(eOperandType type, std::string value): type(type) {
    try {
        this->value = validValue(type, value);
    }
    catch (OverflowException &e){
        std::cout << "OverflowException [" << e.what() << "]" << std::endl;
        exit(0);
    }
    catch (UnderflowException &e){
        std::cout << "UnderflowException [" << e.what() << "]" << std::endl;
        exit(0);
    }
}
Operand::Operand(Operand const &operand) {
    *this = operand;
}

Operand::~Operand() {}

int Operand::getPrecision(void) const {
    return type;
}

eOperandType Operand::getType(void) const {
    return type;
}

const IOperand *Operand::operator+(IOperand const &rhs) const {
    eOperandType    type;

    type = (eOperandType)std::max(this->getPrecision(), rhs.getPrecision());

    return new Operand(type, std::to_string(std::stod(value) + std::stod(rhs.toString())));
}

const IOperand *Operand::operator-(IOperand const &rhs) const {
    eOperandType    type;

    type = (eOperandType)std::max(this->getPrecision(), rhs.getPrecision());

    return new Operand(type, std::to_string(std::stod(value) - std::stod(rhs.toString())));
}

const IOperand *Operand::operator*(IOperand const &rhs) const {
    eOperandType    type;

    type = (eOperandType)std::max(this->getPrecision(), rhs.getPrecision());

    return new Operand(type, std::to_string(std::stod(value) * std::stod(rhs.toString())));
}

const IOperand *Operand::operator/(IOperand const &rhs) const {
    eOperandType    type;

    type = (eOperandType)std::max(this->getPrecision(), rhs.getPrecision());

    return new Operand(type, std::to_string(std::stod(value) / std::stod(rhs.toString())));
}

const IOperand *Operand::operator%(IOperand const &rhs) const {
    eOperandType    type;

    type = (eOperandType)std::max(this->getPrecision(), rhs.getPrecision());

    return new Operand(type, std::to_string(fmod(std::stod(value), std::stod(rhs.toString())))); //re
}

const std::string &Operand::toString(void) const {
    return value;
}


std::string   Operand::validValue(eOperandType type, std::string value_str) const {
    int                 k;
    std::ostringstream  out;

    switch (type){
        case Int8:
            k = std::stoi(value_str);
            if (k < INT8_MIN)
                throw UnderflowException("Int8 cant be " + value_str);
            if (k > INT8_MAX)
                throw OverflowException("Int8 cant be " + value_str);
            return std::to_string(k);
        case Int16:
            k = std::stoi(value_str);
            if (k < INT16_MIN)
                throw UnderflowException("Int16 cant be " + value_str);
            if (k > INT16_MAX)
                throw OverflowException("Int16 cant be " + value_str);
            return std::to_string(k);
        case Int32:
            k = std::stoi(value_str);
            if (k < INT32_MIN)
                throw UnderflowException("Int32 cant be " + value_str);
            if (k > INT32_MAX)
                throw OverflowException("Int32 cant be " + value_str);
            return std::to_string(k);
        case Float:
            try {
                stof(value_str);
                return value_str;
            }
            catch (std::exception e){
                std::cout << e.what() << std::endl;
            }
        case Double:
            try {
                stod(value_str);
                return value_str;
            }
            catch (std::exception e){
                std::cout << e.what() << std::endl;
            }
    }
    return value_str;
}

Operand &Operand::operator=(Operand const &src) {
    if (this != &src){
        this->type = src.type;
        this->value = src.value;
    }
    return *this;
}