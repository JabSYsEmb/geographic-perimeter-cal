#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include "json.hpp"

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

	struct coordinate
	{
		double _x{};
		double _y{};
	};
	typedef struct coordinate coordinate;
	#include "MathPart.hpp"

	enum c_choice { ALL = 1, SINGLE }; // all for all countries, Single for a single country
	enum t_choice { BORDER = 1, SENSING_CABLE};

	void usage(void);
	void json_printer(json temp);
	void notFoundOperationError();
	void country_json_parser(json& data); // all argument handler
	void c_handler(std::string* cflag, char* optarg); // c parameter handler
	void t_handler(std::string* tflag, char* optarg); // t parameter handler
	void bss(const std::string& country_iso, json& data); // country geojson reader
	void assignCoordinates(coordinate* temp, json& _point); // assign a coordinate according to a point
	void calcBorderLength(const std::string& country_iso, json& data); // capital geogson reader
	void notFoundCountryError(bool isCountryFound, std::string country_iso); // notFoundError 
	void getCountryById(const std::string& country_iso, json& data, bool* isCountryFound); // in case just a country iso entered
	double calcDistanceFromArray(std::valarray<std::valarray<double>> array_points);

	json json_reader(std::string suffix);
	std::string stringCapitalizer(char* str);
	t_choice enum_calcType_setter(std::string str);
	c_choice enum_countries_setter(std::string str);
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

	void c_handler(std::string* cflag, char* optarg)
	{
		if (optarg) cflag->assign(stringCapitalizer(optarg));

		if (cflag->length() != 3)
		{
			cflag->assign(ALL_COUNTRY);
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
		if (optarg) tflag->assign(stringCapitalizer(optarg));
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
						getCountryById(country.iso, data, &isCountryFound);
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

	void getCountryById(const std::string& country_iso, json& data,bool* isCountryFound)
	{
		for (auto& _t : data["features"])
		if (_t["properties"]["iso3"] == country_iso)
		{
			json_printer(_t);
			json countries_data = parser::json_reader(COUNTRIES_JSON);
			calcBorderLength(country_iso, 
				       countries_data);
			*isCountryFound = true;
			break;
		}
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

	c_choice enum_countries_setter(std::string str)
	{
		c_choice choice;
		if ( str == ALL_COUNTRY ) choice = ALL;
		else choice = SINGLE;
		return choice;
	}

	t_choice enum_calcType_setter(std::string str)
	{
		t_choice choice;
		str == "BORDER" ? choice = BORDER : choice = SENSING_CABLE;
		return choice;
	}

	void calcBorderLength(const std::string& country_iso, json& data)
	{
		for (auto& _t : data["features"])
		if (_t["properties"]["ISO_A3"] == country_iso)
		{
			double distance{0};
			for (auto& _array_points : _t["geometry"]["coordinates"])
				{
					if(!_array_points[0][0].is_array())
					{
						distance += calcDistanceFromArray(_array_points);
					}
					else{
						for (size_t i = 0; i < _array_points.size(); i++)
						{
							distance += calcDistanceFromArray(_array_points[i]);
						}
					}
				}
			// return distance;
			std::cout << std::setprecision(1) << std::fixed << distance  << std::endl;
		}
	}

	double calcDistanceFromArray(std::valarray<std::valarray<double>> _array_points)
	{
		double distance{0};
		for (size_t i = 0; i < _array_points.size(); i++)
		{
			distance += calcDistance(_array_points[i], _array_points[(i+1)% _array_points.size()]);
		}
		return distance;
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
