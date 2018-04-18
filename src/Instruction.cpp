#include "Instruction.hpp"
#include "AbstractVM.hpp"

/*
**                  Constructors, destructor and coplien functions
*/

Instruction::Instruction() {};

Instruction::Instruction(Instruction const &src) {
    *this = src;
}

Instruction::Instruction(Instruction::Type type) :
    _instruction(type),
    _operand(NULL)
    {}

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

/*
**                  Instructions
*/

void        Instruction::execute( void ) const {
    Instruction::instructionPtr p = _instructionsArray[_instruction];
    (this->*p)();
}

void        Instruction::push( void ) const {
    std::deque<IOperand const *>    &stack = AbstractVM::getStack();
    
    stack.push_front(_operand);
}

void        Instruction::pop( void ) const {

}

void        Instruction::dump( void ) const {
    std::deque<IOperand const *>    stack = AbstractVM::getStack();

    for (std::deque<IOperand const *>::const_iterator it = stack.begin(); it != stack.end(); it++) {
        std::cout << (*it)->toString() << std::endl;
    }
}

void        Instruction::assert( void ) const {

}

void        Instruction::add( void ) const {

}

void        Instruction::sub( void ) const {

}

void        Instruction::mul( void ) const {

}

void        Instruction::div( void ) const {

}

void        Instruction::mod( void ) const {

}

void        Instruction::print( void ) const {

}

void        Instruction::exit( void ) const {

}

/*
**                  Initialisations
*/

const Instruction::instructionPtr   Instruction::_instructionsArray[] = {
    &Instruction::push,
    &Instruction::pop,
    &Instruction::dump,
    &Instruction::assert,
    &Instruction::add,
    &Instruction::sub,
    &Instruction::mul,
    &Instruction::div,
    &Instruction::mod,
    &Instruction::print,
    &Instruction::exit
};
