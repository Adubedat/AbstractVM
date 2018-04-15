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
 	_operandFactory(makeOperandFactory()),
    _operandTokens(makeOperandTokens()),
    _instructionTokens(makeInstructionTokens())
	{

	Lexer	lexer(src);
	std::vector<Token>	tokens;
	while (lexer.getNextTokens(tokens)) {
		try {
            tokensToInstruction(tokens);
        } catch (std::exception &e) {
            std::cout << e.what() << std::endl;
        }
	}

}

Parser::~Parser(void) {};

/*
**                  Grammar checking
*/

void        Parser::tokensToInstruction(std::vector<Token> const & tokens) {

    std::vector<Token>::const_iterator    it = tokens.begin();

    if (tokens.empty())
        return ;
    auto found = _instructionTokens.find(it->type);
    if (found == _instructionTokens.end())
        throw Parser::GrammarException("Error line " + std::to_string(InputSource::getLineNbr()) + " : Each line must begin with an instruction");
    else if (it->type == Token::Type::Push || it->type == Token::Type::Assert) {
        if (tokens.size() != 5)
            throw Parser::GrammarException("Error line " + std::to_string(InputSource::getLineNbr()) + " : Unvalid line, Instr Operand(value) expected");
        checkOperand(found->second, it);
    }
    else if (tokens.size() > 1)
        throw Parser::GrammarException("Error line " + std::to_string(InputSource::getLineNbr()) + " : Unexpected expression following instruction");
    else
        _instructionList.push_back(Instruction(found->second));
}

void        Parser::checkOperand(Instruction::Type instruction, std::vector<Token>::const_iterator it) {

    std::string str;
    auto found = _operandTokens.find((++it)->type);
    if (found == _operandTokens.end())
        throw Parser::GrammarException("Error line " + std::to_string(InputSource::getLineNbr()) + " : This instruction msut be followed by an operand");
    if ((++it)->type != Token::Type::OpenParenthesis)
        throw Parser::GrammarException("Error line " + std::to_string(InputSource::getLineNbr()) + " : Expected opened parenthesis after operand type");
    if ((++it)->type != Token::Type::Number)
        throw Parser::GrammarException("Error line " + std::to_string(InputSource::getLineNbr()) + " : Expected value after parenthesis");
    str = it->value;
    if ((++it)->type != Token::Type::ClosedParenthesis)
        throw Parser::GrammarException("Error line " + std::to_string(InputSource::getLineNbr()) + " : Expected closed parenthesis after value");
    _instructionList.push_back(Instruction(instruction, createOperand(found->second, str)));
}

/*
**					Initialisations
*/

const std::vector<Parser::createOperandPtr>         Parser::makeOperandFactory() const {

	std::vector<Parser::createOperandPtr> factory;

	factory.push_back(&Parser::createInt8);
	factory.push_back(&Parser::createInt16);
	factory.push_back(&Parser::createInt32);
	factory.push_back(&Parser::createFloat);
	factory.push_back(&Parser::createDouble);

	return (factory);
}

const std::map<Token::Type, eOperandType>			Parser::makeOperandTokens() const {

    std::map<Token::Type, eOperandType> map;

    map[Token::Type::Int8]  = Int8;
    map[Token::Type::Int16] = Int16;
    map[Token::Type::Int32] = Int32;
    map[Token::Type::Float] = Float;
    map[Token::Type::Double] = Double;

    return (map);
}

const std::map<Token::Type, Instruction::Type>      Parser::makeInstructionTokens() const {

    std::map<Token::Type, Instruction::Type> map;

    map[Token::Type::Push]   = Instruction::Type::Push;
    map[Token::Type::Pop]    = Instruction::Type::Pop;
    map[Token::Type::Dump]   = Instruction::Type::Dump;
    map[Token::Type::Assert] = Instruction::Type::Assert;
    map[Token::Type::Add]    = Instruction::Type::Add;
    map[Token::Type::Sub]    = Instruction::Type::Sub;
    map[Token::Type::Mul]    = Instruction::Type::Mul;
    map[Token::Type::Div]    = Instruction::Type::Div;
    map[Token::Type::Mod]    = Instruction::Type::Mod;
    map[Token::Type::Print]  = Instruction::Type::Print;
    map[Token::Type::Exit]   = Instruction::Type::Exit;

    return (map);
}

/*
**                  Getters and setters
*/

std::vector<Instruction>	Parser::getInstructionList(void) {

	return (_instructionList);
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

/*
**                  Exception
*/

Parser::GrammarException::GrammarException(std::string msg) :
	_msg(msg)
{}

const char*		Parser::GrammarException::what(void) const throw() {

	return (_msg.c_str());
}
