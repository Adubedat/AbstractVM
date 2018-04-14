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

# include "Lexer.hpp"
# include "IOperand.hpp"
# include "Instruction.hpp"

class Parser
{
public:

	typedef IOperand const * (Parser::*createOperandPtr)(std::string const &value) const;

	IOperand const * createInt8( std::string const & value ) const;
	IOperand const * createInt16( std::string const & value ) const;
	IOperand const * createInt32( std::string const & value ) const;
	IOperand const * createFloat( std::string const & value ) const;
	IOperand const * createDouble( std::string const & value ) const;

	Parser(void);
	Parser(InputSource & src);
	virtual ~Parser();

	std::vector<Instruction>	get_instruction_list(void);

private:

	const std::vector<createOperandPtr>	makeOperandFactory() const;
    IOperand const * 					createOperand( eOperandType type, std::string const & value ) const;

	std::vector<Instruction>			_instruction_list;
	const std::vector<createOperandPtr> _operandFactory;
};

#endif
