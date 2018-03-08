/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 14:45:56 by adubedat          #+#    #+#             */
/*   Updated: 2018/03/07 21:05:32 by adubedat         ###   ########.fr       */
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
	Lexer(InputSource const & src);
	Lexer(Lexer const &src);
	virtual ~Lexer(void);

	int	get_next_tokens(vector<t_token> *tokens);

private:

	InputSource	*_src;
}

#endif
