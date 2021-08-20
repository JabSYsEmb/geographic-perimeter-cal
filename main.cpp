#include <iostream>
#include "parser.hpp"

int main(int argc, char **argv)
{
	parser::parsedInput parsedInput = parser::inputParser(argc, argv);
	json capitals  = parser::json_reader("capitals.geojson");	
	json countries = parser::json_reader("countries.geojson");	
	parser::capital_parser(parsedInput.iso,capitals); 
	parser::country_parser(parsedInput.iso,countries);
	return 0;
}
