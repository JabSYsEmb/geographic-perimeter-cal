#include <iostream>
#include "parser.hpp"

using namespace parser;
int main(int argc, char **argv)
{
	auto parsedArguments = arguments(argc, argv);
	json_reader(parsedArguments);
	return 0;
}
