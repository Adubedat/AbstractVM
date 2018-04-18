/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 17:32:18 by adubedat          #+#    #+#             */
/*   Updated: 2018/03/07 21:34:50 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include "InputSource.hpp"
#include "AbstractVM.hpp"

int 	main(int argc, char **argv)
{
	(void)argv;
	if (argc > 1)
	{
		for (int i = 1; i < argc; ++i) {
			FileInputSource source(argv[i]);
			AbstractVM vm(source);
		}
	}
	else {
		StandardInputSource source;
		AbstractVM vm(source);
	}
	return (EXIT_SUCCESS);
}
