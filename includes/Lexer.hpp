/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 14:45:56 by adubedat          #+#    #+#             */
/*   Updated: 2018/03/07 18:26:19 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_HPP
# define LEXER_HPP

# include "InputSource.hpp"

enum 				e_tokenType {

					Instruction,
					Int8,
					Int16,
					Int32,
					Float,
					Double,
					Separator
};

struct				s_token {

	TokenType		token;
	std::string		value;
}					t_token;

class Lexer
{
public:

	Lexer(void);
	Lexer(Lexer const &src);
	virtual ~Lexer(void);

	Lexer					&operator=(Lexer const & rhs);
	std::vector<t_token>	get_next_tokens(void);

}

#endif
