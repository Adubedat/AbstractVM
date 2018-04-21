#include "Exceptions.hpp"
#include "InputSource.hpp"

SyntaxException::SyntaxException(std::string msg) :
	_msg(std::string(COL_RED) + "[Syntax error line " + std::to_string(InputSource::getLineNbr()) + "] " + std::string(COL_RES) + msg)
{}

const char*		SyntaxException::what(void) const throw() {

	return (_msg.c_str());
}

LexicalException::LexicalException(std::string msg) :
	_msg(std::string(COL_RED) + "[Lexical error line " + std::to_string(InputSource::getLineNbr()) + "] " + COL_RES + msg),
    std::invalid_argument("")
{}

const char*		LexicalException::what(void) const throw() {

	return (_msg.c_str());
}

RuntimeException::RuntimeException(std::string msg) :
	_msg(std::string(COL_RED) + "[Runtime error] " + COL_RES + msg),
    std::runtime_error("")
{}

const char*		RuntimeException::what(void) const throw() {

	return (_msg.c_str());
}

OutOfRangeException::OutOfRangeException(std::string msg) :
	_msg(std::string(COL_RED) + "[Out of range error line " + std::to_string(InputSource::getLineNbr()) + "] " + COL_RES + msg),
    std::out_of_range("")
{}

const char*		OutOfRangeException::what(void) const throw() {

	return (_msg.c_str());
}
