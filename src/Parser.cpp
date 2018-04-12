/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 17:58:09 by adubedat          #+#    #+#             */
/*   Updated: 2018/03/07 18:12:52 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

Parser::Parser(void) {};

Parser::Parser(InputSource & src) {

	Lexer	lexer(src);
	std::vector<Token>	tokens;
	while (lexer.get_next_tokens(&tokens)) {
	//		if (tokens.size() > 0)
	//			std::cout << tokens[0].value << std::endl;
	}


}

Parser::~Parser(void) {};

std::vector<t_instruction>		Parser::get_instruction_list(void) {

	return (_instruction_list);
}
