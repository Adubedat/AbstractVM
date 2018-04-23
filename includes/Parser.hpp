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
# include "Token.hpp"
# include "InputSource.hpp"
# include <map>
# include <vector>

class Parser
{
public:
	Parser(InputSource & src);
	Parser(Parser const &src);
	virtual ~Parser();

	Parser	&operator=(Parser const &rhs);

	static const std::map<Token::Type, eOperandType>		makeOperandTokens();
	static const std::map<Token::Type, Instruction::Type>	makeInstructionTokens();

	std::vector<Instruction>	getInstructionList(void);

private:

	Parser(void);

	void 		tokensToInstruction(std::vector<Token> const & tokens);
	void 		checkOperand(Instruction::Type instruction, std::vector<Token>::const_iterator it);

	static const std::map<Token::Type, Instruction::Type>	_instructionTokens;
	static const std::map<Token::Type, eOperandType>		_operandTokens;

	std::vector<Instruction>	_instructionList;
	InputSource*				_src;
};

#endif
