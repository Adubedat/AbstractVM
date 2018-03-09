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
	
	Push,
	Pop,
	Dump,
	Assert,
	Add,
	Sub,
	Mul,
	Div,
	Mod,
	Print,
	Exit
};

typedef struct		s_instruction {

	e_instruction	instruction;
}					t_instruction;

class Parser
{
public:
	Parser(void);
	Parser(InputSource & src);
	virtual ~Parser();
	
	std::vector<t_instruction>	get_instruction_list(void);	

private:
	
	std::vector<t_instruction>	_instruction_list;
};

#endif
