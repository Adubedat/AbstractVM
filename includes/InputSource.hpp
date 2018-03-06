/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InputSource.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 16:31:10 by adubedat          #+#    #+#             */
/*   Updated: 2018/03/06 19:14:54 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_SOURCE_HPP
# define INPUT_SOURCE_HPP

# include <iostream>
# include <fstream>

class	InputSource
{
public:

	InputSource(void);
	InputSource(InputSource const & src);
	virtual ~InputSource(void);

	InputSource				&operator=(InputSource const & rhs);
	unsigned int			get_line_nbr(void) const;
	virtual	std::string		get_next_line(void) = 0;

private:

	unsigned int	_line_nbr;
};

class	FileInputSource : public InputSource
{
public:

	FileInputSource(void);
	virtual ~FileInputSource(void);
	
	virtual	std::string		get_next_line(void);

private:

	std::ifstream	_ifs;
};

class	StandardInputSource : public InputSource
{
public:

	StandardInputSource(void);
	virtual	~StandardInputSource(void);

	virtual std::string	get_next_line(void);
};

#endif
