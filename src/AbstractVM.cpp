/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractVM.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 17:02:53 by adubedat          #+#    #+#             */
/*   Updated: 2018/03/07 17:58:03 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AbstractVM.hpp"
#include "Exceptions.hpp"

AbstractVM::AbstractVM(void) {}

AbstractVM::AbstractVM(AbstractVM const & src) {
	*this = src;
}

AbstractVM::AbstractVM(InputSource &src){
	Parser	parser(src);
	_instructionList = parser.getInstructionList();
}

AbstractVM::~AbstractVM(void) {
	cleanStack();
}

AbstractVM		&AbstractVM::operator=(AbstractVM const &rhs) {
	if (this != &rhs) {
		_instructionList = rhs._instructionList;
		_stack = rhs._stack;
	}
	return (*this);
}

std::deque<IOperand const *>		&AbstractVM::getStack(){
	return (_stack);
}

void    							AbstractVM::cleanStack() {
	for (IOperand const * &elem : _stack) {
		delete elem;
		_stack.pop_front();
	}
}

void    							AbstractVM::execute() {
	for (Instruction &instr : _instructionList) {
		instr.execute();
	}
	cleanStack();
	throw RuntimeException("Exit instruction is missing, program did not end properly");
}
std::deque<IOperand const *>	AbstractVM::_stack;
