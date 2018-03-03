#include <iostream>
#include <fstream>

int main(int argc, char **argv)
{
	std::ifstream ifs;

	if (argc > 1)
	{
		for (int i = 1; i < argc; ++i)
			std::cout << argv[i] << std::endl;
	}
	else
		std::cout << "read stdin" << std::endl;
	return (EXIT_SUCCESS);
}

/*
 * un enum de TokenType (instr, les 5 operands et (??separator??))
 * un enum instr
 * un enum operand
 * struct Token {Tokentype, Value, ??line??}
 *
 * Faire une classe Lexer avec regexp qui fait passer une liste de tokens au parser :
 * - ctrl syntaxique de chaque mot
 *
 * Faire une classe Parser qui parse la liste de token et check les fautes de grammaire
 *
 * Faire une classe Execution qui distribue les token instr via pointeur sur fonction
 *
 * Faire une classe Operand appelee par instruction qui cree les valeurs sur la stack et fait les operations
*/
