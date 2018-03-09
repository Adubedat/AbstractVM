/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 14:45:56 by adubedat          #+#    #+#             */
/*   Updated: 2018/03/07 21:05:32 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_HPP
# define LEXER_HPP

# include "InputSource.hpp"
# include <vector>
# include <exception>
# include <stdexcept>
# include <sstream>
# include <regex>

enum 				e_tokenType {

					Instruction,
					Int8,
					Int16,
					Int32,
					Float,
					Double,
};

typedef struct		s_token {

	e_tokenType		token_type;
	std::string		value;
}					t_token;

class Lexer
{
public:

	Lexer(void);
	Lexer(InputSource & src);
	Lexer(Lexer const &src);
	virtual ~Lexer(void);

	Lexer	&operator=(Lexer const & src);
	int		get_next_tokens(std::vector<t_token> *tokens);

	class	SyntaxException : public std::exception
	{
	public:
		SyntaxException(unsigned int const line_nbr, unsigned int const column_nbr);
		virtual const char* what(void) const throw();
	private:
		unsigned int	_line_nbr;
		unsigned int	_column_nbr;
	};

private:

	InputSource	*_src;

	std::vector<t_token>	str_to_token(std::string line);
	t_token					get_instruction(std::string	instruction, size_t column_nbr);
	e_tokenType				get_operand(std::string	operand, size_t column_nbr);
	std::string				get_operand_value(e_tokenType type, std::string value,
			size_t column_nbr);
};

#endif
