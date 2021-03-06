#include "Instruction.hpp"
#include "Operand.hpp"
#include "AbstractVM.hpp"
#include "Exceptions.hpp"

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
    try {
        (this->*p)();
    } catch (RuntimeException &e) {
        std::cout << e.what() << std::endl;
        AbstractVM::cleanStack();
        std::exit(EXIT_FAILURE);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void        Instruction::push( void ) const {
    std::deque<IOperand const *>    &stack = AbstractVM::getStack();

    stack.push_front(_operand);
}

void        Instruction::pop( void ) const {
    std::deque<IOperand const *>    &stack = AbstractVM::getStack();

    if (stack.empty())
        throw   RuntimeException("Pop on empty stack");
    delete stack[0];
    stack.pop_front();
}

void        Instruction::dump( void ) const {
    std::deque<IOperand const *>    stack = AbstractVM::getStack();

    for (std::deque<IOperand const *>::const_iterator it = stack.begin(); it != stack.end(); it++) {
        std::cout << (*it)->toString() << std::endl;
    }
}

void        Instruction::assert( void ) const {
    std::deque<IOperand const *>    &stack = AbstractVM::getStack();

    if (stack.empty())
        throw   RuntimeException("Assert on empty stack");
    if (!(*(stack.front()) == *_operand))
        throw   RuntimeException("Assert operand is not equal to the first stack element");
}

void        Instruction::add( void ) const {
    std::deque<IOperand const *>    &stack = AbstractVM::getStack();
    IOperand const *                newElem;

    if (stack.size() < 2)
        throw   RuntimeException("Add instruction with less than two operands in stack");
    newElem = *stack[0] + *stack[1];
    delete stack[0];
    delete stack[1];
    stack.pop_front();
    stack.pop_front();
    stack.push_front(newElem);
}

void        Instruction::sub( void ) const {
    std::deque<IOperand const *>    &stack = AbstractVM::getStack();
    IOperand const *                newElem;

    if (stack.size() < 2)
        throw   RuntimeException("Sub instruction with less than two operands in stack");
    newElem = *stack[1] - *stack[0];
    delete stack[0];
    delete stack[1];
    stack.pop_front();
    stack.pop_front();
    stack.push_front(newElem);
}

void        Instruction::mul( void ) const {
    std::deque<IOperand const *>    &stack = AbstractVM::getStack();
    IOperand const *                newElem;

    if (stack.size() < 2)
        throw   RuntimeException("Mul instruction with less than two operands in stack");
    newElem = *stack[0] * *stack[1];
    delete stack[0];
    delete stack[1];
    stack.pop_front();
    stack.pop_front();
    stack.push_front(newElem);
}

void        Instruction::div( void ) const {
    std::deque<IOperand const *>    &stack = AbstractVM::getStack();
    IOperand const *                newElem;

    if (stack.size() < 2)
        throw   RuntimeException("Div instruction with less than two operands in stack");
    newElem = *stack[1] / *stack[0];
    delete stack[0];
    delete stack[1];
    stack.pop_front();
    stack.pop_front();
    stack.push_front(newElem);
}

void        Instruction::mod( void ) const {
    std::deque<IOperand const *>    &stack = AbstractVM::getStack();
    IOperand const *                newElem;

    if (stack.size() < 2)
        throw   RuntimeException("Mod instruction with less than two operands in stack");
    newElem = *stack[1] % *stack[0];
    delete stack[0];
    delete stack[1];
    stack.pop_front();
    stack.pop_front();
    stack.push_front(newElem);
}

void        Instruction::print( void ) const {
    std::deque<IOperand const *>    &stack = AbstractVM::getStack();

    if (stack.empty())
        throw   RuntimeException("Print on empty stack");
    if (stack.front()->getType() != Int8)
        throw   RuntimeException("First stack element is not an Int8 for print instruction");
    std::cout << static_cast<char>(dynamic_cast<const Operand<int8_t> *>(stack.front())->getValue()) << std::endl;
}

void        Instruction::exit( void ) const {
    AbstractVM::cleanStack();
    std::exit(EXIT_SUCCESS);
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
