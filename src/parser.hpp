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

	void usage(void);
	json json_reader(std::string suffix);
	std::string stringCapitalizer(char* str);
	void c_handler(std::string* cflag, char* optarg);
	void t_handler(std::string* tflag, char* optarg);
	parsedInput inputParser(const int& argc, char** arguments);
	void capital_parser(const parsedInput& country_info, json& data); 

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

	void t_handler(std::string* tflag, char* optarg)
	{
		if (optarg) tflag->assign(optarg);
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

	void capital_parser(const parsedInput& country_info, json& data)
	{
		bool isCountryInData{false};
		if (country_info.iso == "All")
		{
			for (auto& _t : data["features"])
				std::cout << std::setw(3) << _t << std::endl;
		}
		else
		{
			for (auto& _t : data["features"])
			if (_t["properties"]["iso3"] == country_info.iso)
			{
				std::cout << std::setw(3) << _t << std::endl;
				isCountryInData = true;
			}
		}
		if(!isCountryInData)
		{
			std::cout << "Nothing has been found with '" 
				  << country_info.iso 
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
