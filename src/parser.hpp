#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include "Country.hpp"
#include "argument_handler.hpp"

#define FLAGS "c:t:h"
#define DATA_DIRECTORY "/home/jabbar/SammTechnology/Perimeter_calculator/src/data/"
#define OUTPUT_FILE "./info.json"
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
	void country_json_parser(json& data);
	country::Country getCountry(json& data);
	void toJsonFormat(country::Country* country);
	void notFoundCountryError(std::string country_iso);
	void calcBorderLength(country::Country* country);
	void setBorderLength(country::Country* country, json& data);
	void setSensingCableLength(country::Country* country, json& data);
	country::Country getCountryById(const parsedInput& country, json& data); 
	void bss(const std::string& country_iso, json& data, json& countries_data);
	void getAllCountriesBorderCalculated(country::Country* _country,json& data,json& countries_data);
	void getAllCountriesSensingCableCalculated(country::Country* _country,json& data,json& countries_data);

	
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
	void bss(const parsedInput& country, json& data, json& countries_data)
	{
		// TO-DO:
		// countryNotFoundError func
		country::Country _country;
		switch (enum_countries_setter(country.iso))
		{
			case ALL:
				switch (enum_calcType_setter(country.calcType))
				{
					case BORDER:
						getAllCountriesBorderCalculated(&_country,data,countries_data);
						break;
					case SENSING_CABLE:
						getAllCountriesSensingCableCalculated(&_country,data,countries_data);
						break;
					case UNVALID:
						notFoundOperationError();
						break;
					default:
						country_json_parser(data);
						break;
				}
				break;
			case SINGLE_COUNTRY:
				_country = getCountryById(country, data);
				switch (enum_calcType_setter(country.calcType))
				{
					case BORDER:
						setBorderLength(&_country, countries_data);
						std::cout << _country.get_json().dump(3) << std::endl;
						toJsonFormat(&_country);
						break;
					case SENSING_CABLE:
						setSensingCableLength(&_country, countries_data);
						toJsonFormat(&_country);
						break;
					default:
						notFoundOperationError();
						break;
				}
				break;
		}
	}

	
	country::Country getCountryById(const parsedInput& parsedInput, json& data)
	{
		country::Country temp;
		for (auto& _t : data["features"])
		{	
			if (_t["properties"]["iso3"] == parsedInput.iso)
			{
				temp = country::Country(
					_t["properties"]["country"], 
					parsedInput.iso, 
					_t["geometry"]["coordinates"][0], 
					_t["geometry"]["coordinates"][1],
					parsedInput.calcType
					);

				return temp;
			}
		}
		notFoundCountryError(parsedInput.iso);
		return temp;
	}

	void getAllCountriesSensingCableCalculated(country::Country* _country,json& data,json& countries_data)
	{
		for (auto& _t : data["features"])
		{	
			*_country = country::Country(
				_t["properties"]["country"], 
				_t["properties"]["iso3"], 
				_t["geometry"]["coordinates"][0], 
				_t["geometry"]["coordinates"][1],
				"CABLE");
			setSensingCableLength(_country, countries_data);
			toJsonFormat(_country);
		}
	}

	void getAllCountriesBorderCalculated(country::Country* _country,json& data,json& countries_data)
	{
		for (auto& _t : data["features"])
		{	
			*_country = country::Country(
				_t["properties"]["country"], 
				_t["properties"]["iso3"], 
				_t["geometry"]["coordinates"][0], 
				_t["geometry"]["coordinates"][1],
				"BORDER");
			setBorderLength(_country, countries_data);
			toJsonFormat(_country);
		}
	}

	void setBorderLength(country::Country* country, json& data)
	{
		calcBorderLength(country, data);
	}

	void setSensingCableLength(country::Country* country, json& data)
	{
		foo(country, data);
	}
	
	void country_json_parser(json& data)
	{
		for (auto& _t : data["features"])
		{
			json_printer(_t);
		}
	}

	country::Country getCountry(json& data)
	{
		for (auto& _t : data["features"])
		{
			return country::Country(
					_t["properties"]["country"],
					_t["properties"]["iso3"],
					_t["geometry"]["coordinates"][0],
					_t["geometry"]["coordinates"][1]);
		}
		return country::Country();
	}

	void json_printer(json temp)
	{
		std::cout << std::setw(4) << temp << std::endl;
	}

	void notFoundCountryError(std::string country_iso)
	{
		std::cerr << "No such a country with (" << country_iso << ") has been found, try again!" 
				<< std::endl;
	}

	void notFoundOperationError()
	{
		std::cerr << 
		"Unvalid operation, it's possible only to have the border length or the sensing cable length calculated" 
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

	void toJsonFormat(country::Country* country)
	{
		std::string path =((std::string) "./") + OUTPUT_FILE;
		std::ofstream file;
		file.open(path, std::ios::out  | std::ios::app);
		if(file.is_open()){
			file << country->get_json() << std::endl;
		}else{
			std::ofstream file(OUTPUT_FILE);
			file <<	country->get_json() << std::endl;
		}
	}

}
#endif // PARSER_H
