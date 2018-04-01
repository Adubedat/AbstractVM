/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 14:45:14 by adubedat          #+#    #+#             */
/*   Updated: 2018/03/07 21:38:25 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lexer.hpp"

Lexer::Lexer(void) {}

Lexer::Lexer(InputSource &src) {

	_src = &src;
}

Lexer::Lexer(Lexer const & src) {

	*this = src;
}

Lexer::~Lexer(void) {}

Lexer		&Lexer::operator=(Lexer const & rhs) {

	if (this != &rhs) {
		_src = rhs._src;
	}
	return (*this);
}

int						Lexer::get_next_tokens(std::vector<t_token> *tokens) {

	std::string	line;

	if (_src->get_next_line(&line)) {

		*tokens = str_to_token(line);
		return (1);
	}
	return (0);
}

std::vector<std::string>	Lexer::split(std::string const &src) {

	std::string					buf;
	std::stringstream			ss(src);
	std::vector<std::string>	words;

	while (ss >> buf) {
		if (!buf.empty())
			words.push_back(buf);
	}
	return (words);
}

std::vector<t_token>	Lexer::str_to_token(std::string line) {

	std::vector<std::string>	words;
	std::vector<t_token>	token_list;
	t_token					token;

	words = split(line);
	return (token_list);
}

Lexer::SyntaxException::SyntaxException(unsigned int const line_nbr,
		unsigned int const column_nbr) :
	_line_nbr(line_nbr),
	_column_nbr(column_nbr)
{}

const char*		Lexer::SyntaxException::what(void) const throw() {

	std::stringstream err_msg;

	err_msg << "Line " << _line_nbr << ", Column " << _column_nbr  + 1 <<
		" : Syntax error.";
	return (err_msg.str().c_str());
}
