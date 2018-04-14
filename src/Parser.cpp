/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 17:58:09 by adubedat          #+#    #+#             */
/*   Updated: 2018/03/07 18:12:52 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

/*
**					Constructors and destructor
*/

Parser::Parser(void) {};

Parser::Parser(InputSource & src) :
 	_operandFactory(makeOperandFactory())
	{

	Lexer	lexer(src);
	std::vector<Token>	tokens;
	while (lexer.get_next_tokens(tokens)) {
		for (std::vector<Token>::iterator it = tokens.begin(); it != tokens.end(); it++) {
			std::cout << (*it).value << std::endl;
		}
		//if (tokens.size() > 0)
			//std::cout << tokens[0].value << std::endl;
	}

}

Parser::~Parser(void) {};

/*
**					Factory initialisation
*/

const std::vector<Parser::createOperandPtr>		Parser::makeOperandFactory() const {

	std::vector<Parser::createOperandPtr> factory;

	factory.push_back(&Parser::createInt8);
	factory.push_back(&Parser::createInt16);
	factory.push_back(&Parser::createInt32);
	factory.push_back(&Parser::createFloat);
	factory.push_back(&Parser::createDouble);

	return (factory);
}


std::vector<Instruction>	Parser::get_instruction_list(void) {

	return (_instruction_list);
}

/*
**					Operand creation functions
*/

IOperand        const * Parser::createOperand(eOperandType type, std::string const & value) const {

    Parser::createOperandPtr p = this->_operandFactory[type];
    return ((this->*p)(value));
}

IOperand        const * Parser::createInt8(std::string const & value) const {

    return (new Operand<int8_t>(std::stoi(value), Int8));
}

IOperand        const * Parser::createInt16(std::string const & value) const {
    return (new Operand<int16_t>(std::stoi(value), Int16));
}

IOperand        const * Parser::createInt32(std::string const & value) const {
    return (new Operand<int32_t>(std::stoi(value), Int32));
}

IOperand        const * Parser::createFloat(std::string const & value) const {
    return (new Operand<float>(std::stof(value), Float));
}

IOperand        const * Parser::createDouble(std::string const & value) const {
    return (new Operand<double>(std::stoi(value), Double));
}
