//
// Created by Alex LAZAREV on 8/12/18.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include "../includes/Parser.hpp"
#include "../includes/Exception.hpp"

Parser::Parser() {
}

Parser::Parser(Parser const &src) {
    *this = src;
}

Parser::~Parser() {

}

Parser &Parser::operator=(Parser const &src) {
    if (this != &src){

    }
    return *this;
}

void Parser::parse(std::vector<Command> const &command) {
    IOperand const *operand;
    try {
        for (unsigned long i = 0; i < command.size(); i++) {
            switch (command[i].operation) {
                case Push:
                    if ((operand = factory.createOperand(command[i].operand, command[i].value)) == nullptr)
                        throw ParserException();
                    stack.push_front(operand);
                    size++;
                    break;
                case Pop:
                    if (stack.empty())
                        throw StackIsEmptyException();
                    stack.pop_front();
                    size--;
                    break;
                case Dump:
                    if (stack.empty())
                        throw StackIsEmptyException();
                    for (auto it = stack.begin(); it != stack.end(); it++)
                        std::cout << (*it)->toString() << std::endl;
                    break;
                case Assert:
                    if (stack.empty())
                        throw StackIsEmptyException();
                    if ((*stack.begin())->toString().compare(command[i].value))
                        throw AssertWrongValueException();
                    if ((*stack.begin())->getType() != (command[i].operand))
                        throw AssertWrognTypeException();
                    break;
                case Add:
                case Sub:
                case Mul:
                case Div:
                case Mod:
                case Pow:
                    action(command[i].operation);
                    break;
                case Min:
                    if (stack.empty())
                        throw StackIsEmptyException();
                    std::cout << "Min: " << min() << std::endl;
                    break;
                case Max:
                    if (stack.empty())
                        throw StackIsEmptyException();
                    std::cout << "Max: " << max() << std::endl;
                    break;
                case Size:
                    std::cout << size << std::endl;
                    break;
                case Print:
                    if ((operand = *stack.begin())->getType() != Int8)
                        throw LastValueIsNotCharException();
                    std::cout << (char) std::stoi(operand->toString()) << std::endl;
                    break;
                case Clear:
                    if (stack.empty())
                        throw StackIsEmptyException();
                    stack.clear();
                    break;
                case Exit:
                    exit(0);
            }
        }
    }
    catch (std::exception &e){
        std::cout << e.what() << std::endl;
    }
}

void Parser::action(eOperation operation) {
    IOperand const *operand;

    if (stack.empty())
        throw StackIsEmptyException();
    if (size < 2)
        throw StackDeficitElemException();
    operand = *stack.begin();
    stack.pop_front();
    switch (operation) {
        case Add:
            operand = **stack.begin() + *operand;
            break;
        case Sub:
            operand = **stack.begin() - *operand;
            break;
        case Mul:
            operand = **stack.begin() * *operand;
            break;
        case Div:
            if (std::stod(operand->toString()) == 0)
                throw DivisionByZeroException();
            operand = **stack.begin() / *operand;
            break;
        case Mod:
            if (std::stod(operand->toString()) == 0)
                throw DivisionByZeroException();
            operand = **stack.begin() % *operand;
            break;
        case Pow:
            operand = factory.createOperand(
                    (eOperandType)std::max((*stack.begin())->getPrecision(), operand->getPrecision()),
                    std::to_string(pow(std::stod((*stack.begin())->toString()), std::stod(operand->toString()))));
            break;
        default:
            break;
    }
    stack.pop_front();
    stack.push_front(operand);
    size--;
}

std::string Parser::min() {
    IOperand const *min = *stack.begin();

    for (auto it = stack.begin(); it != stack.end(); it++) {
        if (std::stod((*it)->toString()) < std::stod(min->toString()))
            min = *it;
    }
    return min->toString();
}

std::string Parser::max() {
    IOperand const *max = *stack.begin();

    for (auto it = stack.begin(); it != stack.end(); it++) {
        if (std::stod((*it)->toString()) > std::stod(max->toString()))
            max = *it;
    }
    return max->toString();
}




