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
	AbstractVM vm;

	if (argc > 1)
	{
		FileInputSource source(argv[1]);
		vm = AbstractVM(source);
	}
	else {
		StandardInputSource source;
		vm = AbstractVM(source);
	}
	try {
		vm.execute();
	} catch (std::exception &e) {
		vm.cleanStack();
		std::cout << e.what() << std::endl;
		std::exit(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
