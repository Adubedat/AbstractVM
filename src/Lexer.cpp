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

std::vector<t_token>	Lexer::str_to_token(std::string line) {

	std::vector<t_token>	token_list;
	t_token					token;
	std::size_t				found;
	std::size_t				start;

	line.push_back('\n');
	start = 0;
	found = line.find_first_of("; (\n");
	while (found != std::string::npos) {

		if (line[found] == ';')
			return (token_list);
		else if (line[found] == ' ' || line[found] == '\n') {
			if (found - start < 3)
				;
			try {
				token = get_instruction(line.substr(start, found - start), start);
				token_list.push_back(token);
			} catch (Lexer::SyntaxException const & e) {
				std::cerr << e.what() << std::endl;
			}
		}
		else if (line[found] == '(') {
			try {
				token.token_type = get_operand(line.substr(start, found - start), start);
				start = found + 1;
				found = line.find_first_of(")", start);
				token.value = get_operand_value(token.token_type,
						line.substr(start, found - start), start);
			   	token_list.push_back(token);
			} catch (Lexer::SyntaxException const & e) {
				std::cerr << e.what() << std::endl;
			}
		}
		start = found + 1;
		found = line.find_first_of("; (\n", start);
	}
	return (token_list);
}

t_token					Lexer::get_instruction(std::string instruction,
		size_t column_nbr) {

	std::vector<std::string> instr_list;
	t_token	token;
	
	instr_list.push_back("push");
	instr_list.push_back("pop");
	instr_list.push_back("dump");
	instr_list.push_back("assert");
	instr_list.push_back("add");
	instr_list.push_back("sub");
	instr_list.push_back("mul");
	instr_list.push_back("div");
	instr_list.push_back("mod");
	instr_list.push_back("print");
	instr_list.push_back("exit");

	if (find(instr_list.begin(), instr_list.end(), instruction) == instr_list.end())
		throw Lexer::SyntaxException(_src->get_line_nbr(), column_nbr);
	token.token_type = Instruction;
	token.value = instruction;
	return (token);
}

e_tokenType				Lexer::get_operand(std::string operand, size_t column_nbr) {

	if (operand.compare("int8") == 0)
		return (Int8);
	if (operand.compare("int16") == 0)
		return (Int16);
	if (operand.compare("int32") == 0)
		return (Int32);
	if (operand.compare("float") == 0)
		return (Float);
	if (operand.compare("double") == 0)
		return (Double);
//	else
//		throw Lexer::SyntaxException(_src->get_line_nbr(), column_nbr);
}

std::string				Lexer::get_operand_value(e_tokenType type,
	std::string value, size_t column_nbr) {

	std::regex int_r("[-]?[0..9]+");	
	std::regex float_r("[-]?[0..9]+.[0..9]+");

//	if ((type == Float || type == Double) && !std::regex_match(value, float_r))
//		throw Lexer::SyntaxException(_src->get_line_nbr(), column_nbr);

//	else if ((type == Int8 || type == Int16 || type == Int32)
//			&& !std::regex_match(value, int_r))
//		throw Lexer::SyntaxException(_src->get_line_nbr(), column_nbr);
	return (value);
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
