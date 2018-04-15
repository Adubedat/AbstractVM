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

std::string const       Instruction::toString() const {
    switch (_instruction) {
        case Type::Push:
            return "Push " + _operand->toString();
        case Type::Pop:
            return "Pop";
        case Type::Dump:
            return "Dump";
        case Type::Assert:
            return "Assert " + _operand->toString();
        case Type::Add:
            return "Add";
        case Type::Sub:
            return "Sub";
        case Type::Mul:
            return "Mul";
        case Type::Div:
            return "Div";
        case Type::Mod:
            return "Mod";
        case Type::Print:
            return "Print";
        case Type::Exit:
            return "Exit";
    }
}

Instruction::~Instruction() {}
