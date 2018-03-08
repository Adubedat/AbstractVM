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

Lexer::Lexer(InputSource const & src) {

	_src = &src;
}

Lexer::Lexer(Lexer const & src) {

	*this = src;
}

Lexer::Lexer(InputSource const & src){

}

Lexer		&Lexer::operator=(Lexer const & rhs) {

	if (this != rhs) {
		_token_list = rhs._token_list;
	}
}

Lexer::~Lexer(void) {}
