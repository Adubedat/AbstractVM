/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InputSource.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 16:31:10 by adubedat          #+#    #+#             */
/*   Updated: 2018/03/07 19:32:11 by adubedat         ###   ########.fr       */
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

	unsigned int			get_line_nbr(void) const;
	virtual	int				get_next_line(std::string *line) = 0;
	
protected:

	unsigned int	_line_nbr;
};

class	FileInputSource : public InputSource
{
public:

	FileInputSource(void);
	FileInputSource(FileInputSource const & src);
	FileInputSource(std::string file_name);
	virtual ~FileInputSource(void);

	std::ifstream				*get_ifs(void) const;
	virtual FileInputSource		&operator=(FileInputSource const & rhs);
	virtual	int					get_next_line(std::string *line);

private:

	std::ifstream	*_ifs;
};

class	StandardInputSource : public InputSource
{
public:

	StandardInputSource(void);
	StandardInputSource(StandardInputSource const & src);
	virtual	~StandardInputSource(void);

	virtual StandardInputSource		&operator=(StandardInputSource const & rhs);
	virtual int						get_next_line(std::string *line);

private:

	int				_eof;
};

#endif
