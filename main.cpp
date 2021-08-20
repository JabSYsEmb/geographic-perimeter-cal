#include <iostream>
#include "parser.hpp"

int main(int argc, char **argv)
{
	parser::parsedInput parsedInput = parser::inputParser(argc, argv);
	json data = parser::json_reader("capitals.geojson");	
	parser::capital_parser(parsedInput,data); 
	return 0;
}
