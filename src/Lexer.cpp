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

Token::Token(Token::Type type) : type(type), value("") {}

Lexer::Lexer(void) {}

Lexer::Lexer(InputSource &src) : _index(0) {

	_src = &src;
	_keywords["push"] = Token::Type::Push;
	_keywords["pop"] = Token::Type::Pop;
	_keywords["dump"] = Token::Type::Dump;
	_keywords["assert"] = Token::Type::Assert;
	_keywords["add"] = Token::Type::Add;
	_keywords["sub"] = Token::Type::Sub;
	_keywords["mul"] = Token::Type::Mul;
	_keywords["mod"] = Token::Type::Mod;
	_keywords["div"] = Token::Type::Div;
	_keywords["print"] = Token::Type::Print;
	_keywords["exit"] = Token::Type::Exit;
	_keywords["int8"] = Token::Type::Int8;
	_keywords["int16"] = Token::Type::Int16;
	_keywords["int32"] = Token::Type::Int32;
	_keywords["float"] = Token::Type::Float;
	_keywords["double"] = Token::Type::Double;
	_reserved_char['('] = Token::Type::OpenParenthesis;
	_reserved_char[')'] = Token::Type::ClosedParenthesis;
}

Lexer::Lexer(Lexer const & src) : _index(0){

	*this = src;
}

Lexer::~Lexer(void) {}

Lexer		&Lexer::operator=(Lexer const & rhs) {

	if (this != &rhs) {
		_src = rhs._src;
		_index = rhs._index;
		_keywords = rhs._keywords;
	}
	return (*this);
}

int						Lexer::get_next_tokens(std::vector<Token> *tokens) {

	std::string	line;

	if (_src->get_next_line(line)) {
			try {

				*tokens = line_to_tokens(line);
			} catch(std::exception &e) {

				std::cout << e.what() << std::endl;
			}
			return (1);
		}
		return (0);
}

std::vector<Token>	Lexer::line_to_tokens(std::string line) {

	std::vector<Token>			token_list;

	while (line[_index]) {
		if (line[_index] == ';')
			return(token_list);
		else if (isalpha(line[_index]))
			token_list.push_back(name());
		else if (isdigit(line[_index]))
			token_list.push_back(number());
		else if (line[_index] == ' ' || line[_index] == '\t')
			_index++;
		else {
			auto found = _reserved_char.find(line[_index]);
			if (found != _reserved_char.end()) {
				_index++;
				token_list.push_back(Token(found->second));
			}
			else {
				throw Lexer::SyntaxException("Error line " + std::to_string(_src->get_line_nbr()) + ": Unexpected character");
			}
		}
	}
	_index = 0;
	return (token_list);
}

Token								Lexer::name() {

	_index++;
	return (Token(Token::Type::Push));
}

Token								Lexer::number() {
	_index++;
	return (Token(Token::Type::Push));
}

Lexer::SyntaxException::SyntaxException(std::string msg) :
	_msg(msg)
{}

const char*		Lexer::SyntaxException::what(void) const throw() {

	return (_msg.c_str());
}
