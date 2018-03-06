/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InputSource.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 16:31:08 by adubedat          #+#    #+#             */
/*   Updated: 2018/03/06 19:14:52 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "InputSource.hpp"

InputSource::InputSource(void) : _line_nbr(0) {}

InputSource::InputSource(InputSource const & src) {

	*this = src;
}

InputSource::~InputSource(void) {}

InputSource		&InputSource::operator=(InputSource const & rhs) {

	if (this != &rhs) {
		_line_nbr = rhs._line_nbr;
	}
	return *this;
}

unsigned int	InputSource::get_line_nbr(void) const {

	return (_line_nbr);
}

FileInputSource::FileInputSource(void) {}

FileInputSource::~FileInputSource(void) {}

std::string				FileInputSource::get_next_line(void) {

	return ("file");
}

StandardInputSource::StandardInputSource(void) {}

StandardInputSource::~StandardInputSource(void) {}

std::string				StandardInputSource::get_next_line(void) {

	return ("standard");
}
