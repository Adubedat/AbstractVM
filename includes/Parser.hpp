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

/*! \enum 
 *
 *  Instructions that VM can accept
 */

enum 	e_instruction {
	
	push,
	pop,
	dump,
	assert,
	add,
	sub,
	mul,
	div,
	mod,
	print,
	exit
};

struct	s_instruction {

	e_instruction	instruction;
}		t_instruction;

class Parser
{
public:
	Parser(arguments);
	Parser(InputSource const & src);
	virtual ~Parser ();

private:
	
	std::vector<t_instruciton>	_instruction_list;
	std::vector<t_token>		_token_list
};
