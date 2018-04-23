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
#include "Factory.hpp"
#include "Lexer.hpp"


/*
**					Constructors and destructor
*/

Parser::Parser(void) {};

Parser::Parser(InputSource & src)
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

Parser::Parser(Parser const &src) {
    *this = src;
}

Parser::~Parser(void) {};

Parser      &Parser::operator=(Parser const &rhs) {
    if (this != &rhs) {
        _instructionList = rhs._instructionList;
        _src= rhs._src;
    }
    return (*this);
}
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
        Instruction(instruction, Factory::getInstance()->createOperand(found->second, str)).execute();
    else
        _instructionList.push_back(Instruction(instruction, Factory::getInstance()->createOperand(found->second, str)));
}

/*
**					Initialisations
*/

const std::map<Token::Type, eOperandType>			Parser::makeOperandTokens() {

    std::map<Token::Type, eOperandType> map;

    map[Token::Type::Int8]  = Int8;
    map[Token::Type::Int16] = Int16;
    map[Token::Type::Int32] = Int32;
    map[Token::Type::Float] = Float;
    map[Token::Type::Double] = Double;

    return (map);
}

const std::map<Token::Type, Instruction::Type>      Parser::makeInstructionTokens() {

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

const std::map<Token::Type, Instruction::Type>	Parser::_instructionTokens = makeInstructionTokens();
const std::map<Token::Type, eOperandType>		Parser::_operandTokens = makeOperandTokens();

/*
**                  Getters and setters
*/

std::vector<Instruction>	Parser::getInstructionList(void) {

	return (_instructionList);
}
