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

class AbstractVM
{
public:

	AbstractVM(void);
	AbstractVM(InputSource & src);
	virtual ~AbstractVM ();

private:

	std::vector<Instruction> _instructionList;
};

#endif
