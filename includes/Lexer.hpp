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
# include "Token.hpp"
# include <vector>
# include <sstream>
# include <map>

class Lexer
{
public:

	Lexer(InputSource &src);
	Lexer(Lexer const &src);
	virtual ~Lexer(void);

	Lexer	&operator=(Lexer const & src);
	int		getNextTokens(std::vector<Token> &tokens);

private:

	Lexer(void);
	InputSource*							_src;
	std::string::iterator					_it;
	std::map<std::string, Token::Type>		_keywords;
	std::map<char, Token::Type> 			_reserved_char;

	std::vector<Token>			lineToTokens(std::string &line);
	Token 						name(std::string const &line);
	Token						number(std::string const &line);

};

#endif
