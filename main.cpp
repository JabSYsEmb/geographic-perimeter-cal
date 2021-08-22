#include <iostream>
#include "parser.hpp"

int main(int argc, char **argv)
{
	parser::parsedInput parsedInput = parser::inputParser(argc, argv);
	json data  = parser::json_reader("capitals.geojson");	
	json countries_data = parser::json_reader("countries.geojson");
	parser::bss(parsedInput,data,countries_data); 
	return 0;
}
