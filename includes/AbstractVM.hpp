/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractVM.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 17:02:51 by adubedat          #+#    #+#             */
/*   Updated: 2018/03/07 17:55:10 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACT_VM_HPP
# define ABSTRACT_VM_HPP

# include "InputSource.hpp"
# include "Parser.hpp"

class AbstractVM
{
public:

	AbstractVM(void)
	AbstractVM(InputSource const & src);
	virtual ~AbstractVM ();

private:

	std::vector<t_instruction> _instruction_list;
};

#endif
