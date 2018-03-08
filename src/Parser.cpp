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

Parser::Parser(InputSource const & src) {

	Lexer	lexer(src);
	vector<t_token>	tokens;

	while (lexer.get_next_tokens(*tokens)) {
		std::cout << "token line received." << std::endl;
	}
	
}

Parser::~Parser(void) {};
