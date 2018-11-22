//
// Created by Alex LAZAREV on 8/12/18.
//

#include <regex>
#include <fstream>
#include <iostream>
#include <cmath>
#include "../includes/Lexer.hpp"
#include "../includes/Exception.hpp"


void Lexer::readFile(std::string file) {
    bool                error = false;
    std::string         line;
    std::ifstream       ifs;
    int                 i = 0;
    ifs.open(file);

    if (ifs.is_open()) {
        while (!stop && !ifs.eof()){
            getline(ifs, line);
            if (!validation(line)) {
                std::cout << "error in line " << i << ": " << line << std::endl;
                error = true;
            }
            i++;
        }
        ifs.close();
    }
    else
        throw OpenFileException();
    if (error)
        throw LexerException();
    if (!flag)
        throw ExitIsAbsentException();
}

void Lexer::readInput() {
    bool                error = false;
    std::string         line;
    int                 i = 0;

    while (!stop && std::getline(std::cin, line)){
        if (!validation(line)) {
            std::cout << "error in line " << i << ": " << line << std::endl;
            error = true;
        }
        i++;
    }
    if (error)
        throw LexerException();
    if (!flag)
        throw ExitIsAbsentException();
}


bool Lexer::validation(const std::string &line) {
    std::cmatch     result;
    Command         command;
    bool            pair;

    std::regex regStop("\\s*(;;)\\s*");
    std::regex regSpace("\\s*"
                        "(;[\\S\\s]*)?");
    std::regex regAlone("\\s*"
                        "(add|pop|dump|add|sub|mul|div|mod|pow|min|max|size|print|clear|exit)"
                        "\\s*"
                        "(;[\\S\\s]*)?");
    std::regex regPairInt("\\s*"
                       "(push|assert)"
                       "\\s*"
                       "(int8|int16|int32)"
                       "\\("
                       "(0|-?[1-9][0-9]*)"
                       "\\)"
                       "\\s*"
                       "(;[\\S\\s]*)?");
    std::regex regPairFloat("\\s*"
                               "(push|assert)"
                               "\\s*"
                               "(float|double)"
                               "\\("
                               "(0|-?[1-9][0-9]*)"
                               "(\\.[0-9]+)"
                               "\\)"
                               "\\s*"
                               "(;[\\S\\s]*)?");
    if (std::regex_match(line.c_str(),result, regStop))
        return (stop = true);
    if (std::regex_match(line.c_str(), result, regSpace))
        return true;
    if (        (pair = std::regex_match(line.c_str(), result, regPairInt)) ||
                (pair = std::regex_match(line.c_str(), result, regPairFloat)) ||
                std::regex_match(line.c_str(), result, regAlone) ){
        command.operation   = getOperation(result[1]);
        if (command.operation == Exit)
            flag = true;
        if (pair) {
            command.operand = getOperand(result[2]);
            command.value = getValue(result[3], result[4]); //[5] == 42   [6] == .42
        }
        vector->push_back(command);
        return true;
    }
    return false;
}

Lexer::Lexer() {
    vector = new std::vector<Command>;
    stop = false;
    flag = false;
}

Lexer::Lexer(Lexer const &src) {
    *this = src;
}

Lexer::~Lexer() {
    delete vector;
}

Lexer &Lexer::operator=(Lexer const &src) {
    if (this != &src){
        this->flag = src.flag;
        vector->clear();
        for (unsigned long i = 0; i < src.getCommand()->size(); i++)
            this->vector[i] = src.getCommand()[i];
    }
    return *this;
}

eOperation Lexer::getOperation(std::string const &operation) {

    if (!operation.compare("push"))
        return Push;
    if (!operation.compare("pop"))
        return Pop;
    if (!operation.compare("dump"))
        return Dump;
    if (!operation.compare("assert"))
        return Assert;
    if (!operation.compare("add"))
        return Add;
    if (!operation.compare("sub"))
        return Sub;
    if (!operation.compare("mul"))
        return Mul;
    if (!operation.compare("div"))
        return Div;
    if (!operation.compare("mod"))
        return Mod;
    if (!operation.compare("pow"))
        return Pow;
    if (!operation.compare("min"))
        return Min;
    if (!operation.compare("max"))
        return Max;
    if (!operation.compare("size"))
        return Size;
    if (!operation.compare("print"))
        return Print;
    if (!operation.compare("clear"))
        return Clear;
    if (!operation.compare("exit"))
        return Exit;
    return Exit;
}

eOperandType Lexer::getOperand(std::string const &operand) {

    if (!operand.compare("int8"))
        return Int8;
    if (!operand.compare("int16"))
        return Int16;
    if (!operand.compare("int32"))
        return Int32;
    if (!operand.compare("float"))
        return Float;
    if (!operand.compare("double"))
        return Double;
    return Double;
}

std::string Lexer::getValue(std::string const &v1, std::string const &v2) {
    std::string value;
    value.append(v1);
    value.append(v2);
    return value;
}

std::vector<Command> * Lexer::getCommand() const {
    return vector;
}
