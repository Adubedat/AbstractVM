#ifndef TOKEN_HPP
# define TOKEN_HPP

# include <iostream>

struct	Token {

	enum class	Type {

				//Instructions

				Push,
				Pop,
				Dump,
				Assert,
				Add,
				Sub,
				Div,
				Mod,
				Print,
				Mul,
				Exit,

				//Operands

				Int8,
				Int16,
				Int32,
				Float,
				Double,

				//Values

				Number,

				//Delimiters

				OpenParenthesis,
				ClosedParenthesis
	};

    Token();
    Token(Token const &src);
	Token(Token::Type type);
	Token(Token::Type type, std::string value);

    Token   &operator=(Token const &rhs);

    virtual ~Token();

	Type 			type;
	std::string		value;
};

#endif
