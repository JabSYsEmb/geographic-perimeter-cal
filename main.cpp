#include <iostream>
#include "parser.hpp"

using namespace parser;
int main(int argc, char **argv)
{
	auto parsedArguments = arguments(argc, argv);
//	std::cout << "-c : \t\t" << parsedArguments.countery_iso 
//		  << "\n-t : \t\t" << parsedArguments.calculateMode 
//		  << std::endl;	
	return 0;
}
