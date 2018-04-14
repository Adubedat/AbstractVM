#ifndef INSTRUCTION_HPP
# define INSTRUCTION_HPP

# include <iostream>
# include "IOperand.hpp"
# include "Operand.hpp"

class	Instruction
{
public:

	enum class	Type {

		Push,
		Pop,
		Dump,
		Assert,
		Add,
		Sub,
		Mul,
		Div,
		Mod,
		Print,
		Exit
	};

    Instruction();
    Instruction(Instruction const &src);
	Instruction(Instruction::Type const type);
	Instruction(Instruction::Type instructionType, IOperand const *operand);

    Instruction   &operator=(Instruction const &rhs);

    virtual ~Instruction();

private:

	Type               _instruction;
	const IOperand*    _operand;

};

#endif
