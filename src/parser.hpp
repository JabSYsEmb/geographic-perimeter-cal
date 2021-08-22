#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include "json.hpp"
#include "argument_handler.hpp"
#include "Country.hpp"

#define FLAGS "c:t:h"
#define ALL_COUNTRY "All"
#define CALC_BORDER "border"
#define COUNTRIES_JSON "countries.geojson"
#define DATA_DIRECTORY "/home/jabbar/SammTechnology/Perimeter_calculator/src/data/"

using nlohmann::json;

namespace parser
{ 
	struct parsedInput 
	{
		std::string iso{};
		std::string calcType{};
	};
	typedef struct parsedInput parsedInput;

	#include "MathPart.hpp"

	void usage(void);
	void json_printer(json temp);
	void notFoundOperationError();
	void country_json_parser(json& data); // all argument handler

	void bss(const std::string& country_iso, json& data); // country geojson reader
	void calcBorderLength(const std::string& country_iso, json& data); // capital geogson reader
	void notFoundCountryError(bool isCountryFound, std::string country_iso); // notFoundError 
	country::Country getCountryById(const parsedInput& country, json& data,bool* isCountryFound); // in case just a country iso entered

	json json_reader(std::string suffix);
	parsedInput inputParser(const int& argc, char** arguments);
	
	parsedInput inputParser(const int& argc, char** arguments)
	{
		std::string cflag{ALL_COUNTRY};
		std::string tflag{CALC_BORDER};
		if (argc <= 1)
		{
			std::cout << "Some arguments are missing, try again!\n"
				  << "Try 'bss -help -h' for more information" << std::endl;
			return parsedInput{cflag,tflag};
		}
		else
		{
			int c{0};
			while ((c = getopt(argc, arguments, FLAGS)) != EOF)
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

	json json_reader(std::string suffix)
	{
		std::string absolutePath = DATA_DIRECTORY;
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

	// border security system _main_
	void bss(const parsedInput& country, json& data)
	{
		bool isCountryFound{false};
		switch (enum_countries_setter(country.iso))
		{
			case ALL:
				switch (enum_calcType_setter(country.calcType))
				{
					case BORDER:
						country_json_parser(data);
						break;
					case SENSING_CABLE:
						break;
				}
				isCountryFound = true;
				break;
			case SINGLE:
				switch (enum_calcType_setter(country.calcType))
				{
					case BORDER:
						getCountryById(country, data, &isCountryFound).toString();
						break;
					case SENSING_CABLE:
						break;
					default:
						notFoundOperationError();
						break;
				}
				break;
		}
		notFoundCountryError(isCountryFound, country.iso);
		data=nullptr;
	}

	country::Country getCountryById(const parsedInput& country, json& data,bool* isCountryFound)
	{
		country::Country temp;
		for (auto& _t : data["features"])
		{	
			if (_t["properties"]["iso3"] == country.iso)
			{
				temp = country::Country(_t["properties"]["country"] ,country.iso,country.calcType);
				json countries_data = parser::json_reader(COUNTRIES_JSON);
				calcBorderLength(country.iso, 
						countries_data);
				*isCountryFound = true;
				return temp;
			}
		}
		return temp;
	}

	void country_json_parser(json& data)
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

	void notFoundOperationError()
	{
		std::cerr << 
		"Unvalid operation, it's possible only to have calculate the border length or the sensing cable length" 
		<< std::endl;
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
