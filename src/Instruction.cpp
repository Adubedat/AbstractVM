#include "Instruction.hpp"
#include "IOperand.hpp"

Instruction::Instruction() {};

Instruction::Instruction(Instruction const &src) {
    *this = src;
}

Instruction::Instruction(Instruction::Type type) : _instruction(type), _operand(NULL) {}

Instruction::Instruction(Instruction::Type instructionType, IOperand const *operand) :
    _instruction(instructionType),
    _operand(operand)
    {}

Instruction   &Instruction::operator=(Instruction const &rhs) {
    if (this != &rhs) {
        _instruction = rhs._instruction;
        _operand = rhs._operand;
    }
    return (*this);
}

Instruction::~Instruction() {
    if (_operand != NULL) {
        delete _operand;
    }
}
