/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractVM.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 17:02:51 by adubedat          #+#    #+#             */
/*   Updated: 2018/03/07 20:47:16 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACT_VM_HPP
# define ABSTRACT_VM_HPP

# include "InputSource.hpp"
# include "Parser.hpp"
# include <deque>

class AbstractVM
{
public:

	AbstractVM(void);
	AbstractVM(AbstractVM const &src);
	AbstractVM(InputSource & src);

	AbstractVM	&operator=(AbstractVM const &rhs);
	
	static std::deque<IOperand const *>		&getStack();
	static void    cleanStack();
	void    execute();

	virtual ~AbstractVM ();

private:

	std::vector<Instruction>			_instructionList;
	static std::deque<IOperand const *>	_stack;
};

#endif
