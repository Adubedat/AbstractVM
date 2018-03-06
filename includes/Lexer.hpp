/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 14:45:56 by adubedat          #+#    #+#             */
/*   Updated: 2018/03/06 16:18:13 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_HPP
# define LEXER_HPP

enum 				TokenType {

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

private:

	std::deque<TokenType>	token;

}

#endif
