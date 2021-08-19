#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include "json.hpp"

using nlohmann::json;
int main(int argc, char** argv)
{
	if(argc == 1)
	{
		std::cout << "Some arguments are missing, try again!\n"
			  << "Try 'bss --help' for more information" << std::endl;
		return 0;
	}
	else
	{
		int c{0};
		char cflag[4] = "All";
		char tflag[7] = "border";

		while((c = getopt (argc, argv, "c::t::") != EOF))
		{
			switch (c) 
			{
				case 'c':
					cflag = optarg;
					break;
				case 't':
					tflag = optarg;
					break;
				case default:
					std::cout << optarg << " isn't a known parameter" << std::endl;
					break;	
			}
		}
		std::string absolutePath = "/home/jabbar/SammTechnology/Perimeter_calculator/src/data/";
		std::string suffix = "capitals.geojson";
		try
		{
			std::ifstream capitals_json(absolutePath+suffix);
			json capitals_info;
			capitals_json >> capitals_info;

			for(auto& [key, value] : capitals_info.items()) 
			if(key == "features")
			{
				std::cout << key <<  " : " << value[2]["geometry"].dump(4) << '\n' << std::endl;
			}
			capitals_info = NULL;
			capitals_json.close();
		}
		catch(json::parse_error& ex)
		{
			std::cerr << "Parser error at byte " << ex.byte << std::endl;
		}
		return 0;
	}

}
