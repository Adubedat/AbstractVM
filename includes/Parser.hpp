/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 17:54:23 by adubedat          #+#    #+#             */
/*   Updated: 2018/03/07 18:12:55 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
# define PARSER_HPP

# include "Instruction.hpp"
# include "Lexer.hpp"
# include <climits>
# include <cfloat>

class Parser
{
public:

	typedef IOperand const * (Parser::*createOperandPtr)(std::string const &value) const;

	Parser(InputSource & src);
	virtual ~Parser();

	std::vector<Instruction>	getInstructionList(void);

	class	GrammarException : public std::exception
	{
		public:
			GrammarException(std::string msg);
			virtual const char* what(void) const throw();
		private:
			std::string	_msg;
	};

private:

	Parser(void);

	void 		tokensToInstruction(std::vector<Token> const & tokens);
	void 		checkOperand(Instruction::Type instruction, std::vector<Token>::const_iterator it);

	const std::vector<createOperandPtr>				makeOperandFactory() const;
	const std::map<Token::Type, eOperandType>		makeOperandTokens() const;
	const std::map<Token::Type, Instruction::Type>	makeInstructionTokens() const;

    IOperand const * createOperand( eOperandType type, std::string const & value ) const;

	IOperand const * createInt8( std::string const & value ) const;
	IOperand const * createInt16( std::string const & value ) const;
	IOperand const * createInt32( std::string const & value ) const;
	IOperand const * createFloat( std::string const & value ) const;
	IOperand const * createDouble( std::string const & value ) const;

	const std::map<Token::Type, Instruction::Type>	_instructionTokens;
	const std::map<Token::Type, eOperandType>		_operandTokens;
	std::vector<Instruction>						_instructionList;
	const std::vector<createOperandPtr> 			_operandFactory;
	InputSource*									_src;
};

#endif
