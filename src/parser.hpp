#include <unistd.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include "json.hpp"

using nlohmann::json;

namespace parser
{
	struct parsedArguments 
	{
		std::string iso{};
		std::string calculateMode{};
	};
	typedef struct parsedArguments parsedArguments;
	
	void usage(void);
	void c_handler(std::string* cflag, char* optarg);
	void t_handler(std::string* tflag, char* optarg);
	void json_reader(const parsedArguments& country_info);
	parsedArguments arguments(const int& argc, char** arguments);

	parsedArguments arguments(const int& argc, char** arguments)
	{
		std::string cflag{"All"};
		std::string tflag{"border"};
		if (argc <= 1)
		{
			std::cout << "Some arguments are missing, try again!\n"
				  << "Try 'bss -help -h' for more information" << std::endl;
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
		}
		return parsedArguments{cflag,tflag};
	}

	void c_handler(std::string* cflag, char* optarg)
	{
		if (optarg) cflag->assign(optarg);

		if (cflag->length() != 3)
		{
			cflag->assign("All");
		}	
	}

	void t_handler(std::string* tflag, char* optarg)
	{
		if (optarg) tflag->assign(optarg);
	}

	void json_reader(const parsedArguments& country_info)
	{
		std::string absolutePath = "/home/jabbar/SammTechnology/Perimeter_calculator/src/data/";
		std::string suffix = "capitals.geojson";
		try
		{
			json capitals_info;
			std::ifstream capitals_json(absolutePath+suffix);
			capitals_json >> capitals_info;

			if (country_info.iso == "All")
			{
				std::cout << "here" << std::endl;
				for (auto& _t : capitals_info["features"])
					std::cout << std::setw(3) << _t << std::endl;
			}
			else
			{
				for (auto& _t : capitals_info["features"])
				if (_t["properties"]["iso3"] == country_info.iso)
					std::cout << std::setw(3) << _t << std::endl;
			}
			capitals_info = NULL;
			capitals_json.close();
		}
		catch(json::parse_error& ex)
		{
			std::cerr << "Parser error at byte [" << ex.byte << "]" << std::endl;
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
