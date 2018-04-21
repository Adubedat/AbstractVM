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
#include "Exceptions.hpp"

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

    _src = &src;
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
        throw SyntaxException("Each line must begin with an instruction");
    else if (it->type == Token::Type::Push || it->type == Token::Type::Assert) {
        if (tokens.size() != 5)
            throw SyntaxException("Unvalid line, Instr Operand(value) expected");
        checkOperand(found->second, it);
    }
    else if (tokens.size() > 1)
        throw SyntaxException("Unexpected expression following instruction");
    else if (_src->isCin())
        Instruction(found->second).execute();
    else
        _instructionList.push_back(Instruction(found->second));
}

void        Parser::checkOperand(Instruction::Type instruction, std::vector<Token>::const_iterator it) {

    std::string str;
    auto found = _operandTokens.find((++it)->type);
    if (found == _operandTokens.end())
        throw SyntaxException("This instruction must be followed by an operand");
    if ((++it)->type != Token::Type::OpenParenthesis)
        throw SyntaxException("Opened parenthesis expected after operand type");
    if ((++it)->type != Token::Type::Number)
        throw SyntaxException("Value expected after parenthesis");
    str = it->value;
    if ((++it)->type != Token::Type::ClosedParenthesis)
        throw SyntaxException("Closed parenthesis expected after value");
    if (_src->isCin())
        Instruction(instruction, createOperand(found->second, str)).execute();
    else
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
    try {
        int nbr = std::stoi(value);
        if (nbr < CHAR_MIN || nbr > CHAR_MAX)
            throw OutOfRangeException("");
        return (new Operand<int8_t>(nbr, Int8));
    } catch (std::exception &e) {
        throw OutOfRangeException("int8 value must be between " + std::to_string(CHAR_MIN) + " and " + std::to_string(CHAR_MAX));
    }
}

IOperand        const * Parser::createInt16(std::string const & value) const {
    try {
        int nbr = std::stoi(value);
        if (nbr < SHRT_MIN || nbr > SHRT_MAX)
            throw OutOfRangeException("");
        return (new Operand<int16_t>(nbr, Int16));
    } catch (std::exception &e) {
        throw OutOfRangeException("int16 value must be between " + std::to_string(SHRT_MIN) + " and " + std::to_string(SHRT_MAX));
    }
}

IOperand        const * Parser::createInt32(std::string const & value) const {
    try {
        int nbr = std::stoi(value);
        if (nbr < INT_MIN || nbr > INT_MAX)
            throw OutOfRangeException("");
        return (new Operand<int32_t>(nbr, Int32));
    } catch (std::exception &e) {
        throw OutOfRangeException("int32 value must be between " + std::to_string(INT_MIN) + " and " + std::to_string(INT_MAX));
    }
}

IOperand        const * Parser::createFloat(std::string const & value) const {
    try {
        float nbr = std::stof(value);
        if (nbr < -FLT_MAX || nbr > FLT_MAX)
            throw OutOfRangeException("");
        return (new Operand<float>(nbr, Float));
    } catch (std::exception &e) {
        throw OutOfRangeException("float value must be between " + std::to_string(-FLT_MAX) + " and " + std::to_string(FLT_MAX));
    }
}

IOperand        const * Parser::createDouble(std::string const & value) const {
    try {
        double nbr = std::stod(value);
        if (nbr < -DBL_MAX || nbr > DBL_MAX)
            throw OutOfRangeException("");
        return (new Operand<double>(nbr, Double));
    } catch (std::exception &e) {
        throw OutOfRangeException("double value must be between " + std::to_string(-DBL_MAX) + " and " + std::to_string(DBL_MAX));
    }
}
