#ifndef INSTRUCTION_HPP
# define INSTRUCTION_HPP

# include <iostream>
# include <deque>
# include "Operand.hpp"

class	Instruction
{
public:

	enum	Type {

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

	typedef void (Instruction::*instructionPtr)( void ) const;

    Instruction();
    Instruction(Instruction const &src);
	Instruction(Instruction::Type const type);
	Instruction(Instruction::Type instructionType, IOperand const *operand);

	void    			execute( void ) const;

	void    			push( void ) const;
	void    			pop( void ) const;
	void    			dump( void ) const;
	void    			assert( void ) const;
	void    			add( void ) const;
	void    			sub( void ) const;
	void    			mul( void ) const;
	void    			div( void ) const;
	void    			mod( void ) const;
	void    			print( void ) const;
	void    			exit( void ) const;

    Instruction 		&operator=(Instruction const &rhs);

	std::string const  	toString() const;

    virtual ~Instruction();

private:

	Type										_instruction;
	const IOperand*								_operand;
	static const Instruction::instructionPtr	_instructionsArray[];

};

#endif
