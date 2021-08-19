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
		std::string countery_iso{};
		std::string calculateMode{};
	};
	typedef struct parsedArguments parsedArguments;
	
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

	
	void json_reader()
	{
		std::string absolutePath = "/home/jabbar/SammTechnology/Perimeter_calculator/src/data/";
		std::string suffix = "capitals.geojson";
		try
		{
			std::ifstream capitals_json(absolutePath+suffix);
			json capitals_info;
			capitals_json >> capitals_info;

			for (auto& [key, value] : capitals_info.items()) 
			if (key == "features")
			{
				std::cout << key <<  " : " << value[2]["geometry"].dump(4) << '\n' << std::endl;
			}
			capitals_info = NULL;
			capitals_json.close();
		}
		catch(json::parse_error& ex)
		{
			std::cerr << "Parser error at byte [" << ex.byte << "]" << std::endl;
		}
	}

	parsedArguments arguments(int argc, char** arguments)
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

			while ((c = getopt(argc, arguments, "c:t:help")) != EOF)
			{
				switch (c) 
				{
					case 'c':
						if (optarg) cflag.assign(optarg);
						else std::cout << "-c country of interest. Default: All" << std::endl;
						if(cflag.length() != 3)
						{
							cflag.assign("All");
							break;
						}	
						break;
					case 't':
						if (optarg) tflag.assign(optarg);
						else std::cout << "type of calculation. Default: border" << std::endl;
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
}
