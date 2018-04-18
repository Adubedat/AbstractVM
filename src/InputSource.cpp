/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InputSource.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 16:31:08 by adubedat          #+#    #+#             */
/*   Updated: 2018/03/07 19:31:06 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "InputSource.hpp"

InputSource::InputSource(void) {}

InputSource::~InputSource(void) {}

unsigned int		InputSource::getLineNbr() {

	return (_lineNbr);
}

bool				InputSource::isCin() {
	return (false);
}

unsigned int InputSource::_lineNbr = 0;

/*
 *		File Input Class
*/

FileInputSource::FileInputSource(void) {}

FileInputSource::FileInputSource(FileInputSource const & src) {

	*this = src;
}

FileInputSource::FileInputSource(std::string file_name) {

	try {
		_ifs = new std::ifstream(file_name, std::ifstream::in);
		_ifs->exceptions(std::ifstream::failbit);
	} catch (const std::exception & e) {
		std::cerr << "Error when opening file" << std::endl;
	}
}

FileInputSource::~FileInputSource(void) {

	try {
		delete _ifs;
	} catch (const std::exception & e) {
		std::cerr << "Error when closing file stream" << std::endl;
	}
}

std::ifstream	*FileInputSource::get_ifs(void) const{

	return (_ifs);
}

FileInputSource	&FileInputSource::operator=(FileInputSource const & rhs) {

	if (this != &rhs) {

		_ifs = rhs.get_ifs();
	}
	return (*this);
}

int				FileInputSource::getNextLine(std::string &line) {

	if (getline(*_ifs, line)) {
		InputSource::_lineNbr += 1;
		return (1);
	}
	return (0);
}

/*
 *		Standard Input Class
*/

StandardInputSource::StandardInputSource(void) : _eof(0) {}

StandardInputSource::StandardInputSource(StandardInputSource const & src) {

	*this = src;
}

StandardInputSource::~StandardInputSource(void) {}

StandardInputSource		&StandardInputSource::operator=(StandardInputSource const & rhs) {

	if (this != &rhs) {
		_eof = rhs._eof;
	}
	return (*this);
}

bool			StandardInputSource::isCin() {
	return (true);
}

int				StandardInputSource::getNextLine(std::string &line) {

	if (_eof)
		return (0);
	getline(std::cin, line);
	InputSource::_lineNbr += 1;
	if ((line).find(";;") != std::string::npos)
		_eof = 1;
	return (1);
}
