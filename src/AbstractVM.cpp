/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractVM.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 17:02:53 by adubedat          #+#    #+#             */
/*   Updated: 2018/03/07 17:58:03 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AbstractVM.hpp"

AbstractVM::AbstractVM(void) {}

AbstractVM::AbstractVM(InputSource const & src){

	Parser	parser(src);
	_instruction_list = parser.get_instruction_list;
}

AbstractVM::~AbstractVM(void) {}
