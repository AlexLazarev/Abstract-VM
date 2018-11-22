//
// Created by Alex LAZAREV on 8/13/18.
//

#ifndef VM_OPERANDFACTORY_HPP
#define VM_OPERANDFACTORY_HPP


#include <stack>
#include "Operand.hpp"
#include "Command.hpp"

class OperandFactory {

public:
    OperandFactory();
    OperandFactory(OperandFactory const &src);
    virtual ~OperandFactory();

    IOperand const * createOperand( eOperandType type, std::string const & value ) const;

    OperandFactory  &operator=(OperandFactory const &src);
private:
    IOperand const * createInt8( std::string const & value ) const;
    IOperand const * createInt16( std::string const & value ) const;
    IOperand const * createInt32( std::string const & value ) const;
    IOperand const * createFloat( std::string const & value ) const;
    IOperand const * createDouble( std::string const & value ) const;

};


#endif //VM_OPERANDFACTORY_HPP
