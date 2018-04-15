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

AbstractVM::AbstractVM(void) {}

AbstractVM::AbstractVM(InputSource &src){

	Parser	parser(src);
	_instructionList = parser.getInstructionList();
	for (std::vector<Instruction>::iterator it = _instructionList.begin(); it != _instructionList.end(); it++) {
		std::cout << it->toString() << std::endl;
	}
}

AbstractVM::~AbstractVM(void) {}
