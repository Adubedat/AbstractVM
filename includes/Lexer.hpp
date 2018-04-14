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
# include <unordered_map>

class Lexer
{
public:

	Lexer(InputSource &src);
	Lexer(Lexer const &src);
	virtual ~Lexer(void);

	Lexer	&operator=(Lexer const & src);
	int		get_next_tokens(std::vector<Token> &tokens);

	class	SyntaxException : public std::exception
	{
		public:
			SyntaxException(std::string msg);
			virtual const char* what(void) const throw();
		private:
			std::string	_msg;
	};

private:

	Lexer(void);
	InputSource*									_src;
	std::string::iterator							_it;
	std::unordered_map<std::string, Token::Type>	_keywords;
	std::unordered_map<char, Token::Type> 			_reserved_char;

	std::vector<Token>			line_to_tokens(std::string &line);
	Token 						name(std::string const &line);
	Token						number(std::string const &line);

};

#endif
