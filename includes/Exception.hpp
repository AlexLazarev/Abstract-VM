//
// Created by Alex LAZAREV on 8/13/18.
//

#ifndef VM_EXCEPTION_HPP
#define VM_EXCEPTION_HPP

#include <exception>

class ParserException : public std::exception{

public:
    virtual const char *what() const throw(){
        return "Parser error";
    }
};

class LexerException : public std::exception{

public:
    virtual const char *what() const throw(){
        return "Lexer error";
    }
};

class StackIsEmptyException : public std::exception{

public:
    virtual const char *what() const throw(){
        return "Stack is empty";
    }
};

class LastValueIsNotCharException : public std::exception{

public:
    virtual const char *what() const throw(){
        return "Last value in stack is not char";
    }
};

class OverflowException : std::overflow_error {
public:
    OverflowException(const std::string &s) : overflow_error(s), str(s) {}

    virtual const char *what() const throw() override {
        return str.c_str();
    }

private:
    std::string str;
};


class UnderflowException : std::underflow_error {
public:
    UnderflowException(const std::string &s) : underflow_error(s), str(s) {}

    virtual const char *what() const throw() override {
        return str.c_str();
    }

private:
    std::string str;
};

class StackDeficitElemException : public std::exception{

public:
    virtual const char *what() const throw(){
        return "Stack haven't enough elements";
    }
};

class DivisionByZeroException : public std::exception{

public:
    virtual const char *what() const throw(){
        return "Division by zero";
    }
};


class AssertWrongValueException : public std::exception{

public:
    virtual const char *what() const throw(){
        return "Wrong value";
    }
};

class AssertWrognTypeException : public std::exception{

public:
    virtual const char *what() const throw(){
        return "Wrong type";
    }
};

class ExitIsAbsentException : public std::exception{

public:
    virtual const char *what() const throw(){
        return "Exit is absent";
    }
};

class OpenFileException : public std::exception{

public:
    virtual const char *what() const throw(){
        return "Connot open a file";
    }
};

#endif //VM_EXCEPTION_HPP
