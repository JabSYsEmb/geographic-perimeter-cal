#ifndef PARSER_H
#define PARSER_H
#include <unistd.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include "json.hpp"

using nlohmann::json;

namespace parser
{ 
	struct parsedInput 
	{
		std::string iso{};
		std::string calculateMode{};
	};
	typedef struct parsedInput parsedInput;

	struct coordinate
	{
		double _x{};
		double _y{};
	};
	typedef struct coordinate coordinate;
	#include "MathPart.hpp"

	enum choice { ALL = 1, SINGLE }; // all for all countries, Single for a single country

	void usage(void);
	void json_printer(json temp);
	void all_handler(json& data); // all argument handler
	void c_handler(std::string* cflag, char* optarg); // c parameter handler
	void t_handler(std::string* tflag, char* optarg); // t parameter handler
	void assignCoordinates(coordinate* temp, json& _point); // assign a coordinate according to a point
	void country_parser(const std::string& country_iso, json& data); // country geojson reader
	void capital_parser(const std::string& country_iso, json& data); // capital geogson reader
	void notFoundCountryError(bool isCountryFound, std::string country_iso); // notFoundError 
	void single_handler(const std::string& country_iso, json& data, bool* isCountryFound); // in case just a country iso entered

	json json_reader(std::string suffix);
	std::string stringCapitalizer(char* str);
	choice enum_countries_setter(std::string str);
	parsedInput inputParser(const int& argc, char** arguments);
	
	parsedInput inputParser(const int& argc, char** arguments)
	{
		std::string cflag{"All"};
		std::string tflag{"border"};
		if (argc <= 1)
		{
			std::cout << "Some arguments are missing, try again!\n"
				  << "Try 'bss -help -h' for more information" << std::endl;
			return parsedInput{cflag,tflag};
		}
		else
		{
			int c{0};
			while ((c = getopt(argc, arguments, "c:t:h")) != EOF)
			{
				switch (c) 
				{
					case 'c':
						c_handler(&cflag, optarg);
						break;
					case 't':
						t_handler(&tflag, optarg);
						break;
					case 'h':
						parser::usage();
						break;
					default:
						break;
				}
			}
			return parsedInput{cflag,tflag};
		}
	}

	void c_handler(std::string* cflag, char* optarg)
	{
		if (optarg) cflag->assign(stringCapitalizer(optarg));

		if (cflag->length() != 3)
		{
			cflag->assign("All");
		}	
	}

	std::string stringCapitalizer(char* str)
	{
		std::string capitalizedString{};
		while(*str != '\0')
		{
			if(*str >= 97)
				*str = *str - 32;
			capitalizedString.push_back(*str);
			++(str);
		}
		return capitalizedString;
	}
	
	void t_handler(std::string* tflag, char* optarg)
	{
		if (optarg) tflag->assign(optarg);
	}

	json json_reader(std::string suffix)
	{
		std::string absolutePath = "/home/jabbar/SammTechnology/Perimeter_calculator/src/data/";
		try
		{
			json capitals_info;
			std::ifstream capitals_json(absolutePath+suffix);
			capitals_json >> capitals_info;
			return capitals_info;
		}
		catch(json::parse_error& ex)
		{
			std::cerr << "Parser error at byte [" << ex.byte << "]" << std::endl;
			std::cerr << "The json file was unreachable, check if the file exists" << std::endl;
			return nullptr;
		}
	}

	void capital_parser(const std::string& country_iso, json& data)
	{
		bool isCountryFound{false};
		switch (enum_countries_setter(country_iso))
		{
			case ALL:
				all_handler(data);
				isCountryFound = true;
				break;
			case SINGLE:
				single_handler(country_iso, data, &isCountryFound);
				break;
		}
		notFoundCountryError(isCountryFound, country_iso);
	}

	void single_handler(const std::string& country_iso, json& data,bool* isCountryFound)
	{
		for (auto& _t : data["features"])
		if (_t["properties"]["iso3"] == country_iso)
		{
			json_printer(_t);
			json countries_data = parser::json_reader("countries.geojson");
			country_parser(country_iso, 
				       countries_data);
			*isCountryFound = true;
			break;
		}
	}

	void all_handler(json& data)
	{
		for (auto& _t : data["features"])
		{
			json_printer(_t);
		}
	}

	void json_printer(json temp)
	{
		std::cout << std::setw(4) << temp << std::endl;
	}

	choice enum_countries_setter(std::string str)
	{
		choice choice;
		if ( str == "All" ) choice = ALL;
		else choice = SINGLE;
		return choice;
	}

	void country_parser(const std::string& country_iso, json& data)
	{
		for (auto& _t : data["features"])
		if (_t["properties"]["ISO_A3"] == country_iso)
		{
			bool first_point = true;
			coordinate temp;
			double distance{0};
			for (auto& _array_points : _t["geometry"]["coordinates"])
			for (auto& _point : _array_points)
			{
				if(first_point)
				{
					assignCoordinates(&temp,_point);
					first_point = false;	
				}
				else
				{
					distance += calcDistance(&temp, _point[0], _point[1]);
					assignCoordinates(&temp,_point);
				}
			}
			std::cout << std::setprecision(1) << std::fixed << distance  << std::endl;
		break;
		}
	}

	void assignCoordinates(coordinate* temp, json& _point)
	{
		temp->_x = _point[0];
		temp->_y = _point[1];
	}

	void notFoundCountryError(bool isCountryFound, std::string country_iso)
	{
		if(!isCountryFound)
		{
			std::cerr << "Nothing has been found with '" 
				  << country_iso
				  << "' ISO code" 
				  << std::endl;
		}

	}

	void usage(void)
	{
		std::cout << "Usage: bss [options] ..." 
			  << "\nOptions:\n" 
			  << "-c\t\tcountry of interest. Default: All\n"
			  << "-t\t\ttype of calculation. Default: border\n"
			  << "\nExamples:\n\t\t"
			  << "bss -c AEZ -t border\n"
			  << "\t\tbss -c KSA -t center\n"
			  << std::endl;
	}
}
#endif // PARSER_H
