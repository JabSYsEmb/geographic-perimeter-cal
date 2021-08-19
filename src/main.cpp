#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include "json.hpp"

using nlohmann::json;
int main(int argc, char** argv)
{
	if(argc == 2){
		std::cout << argv[0] << std::endl;
	}

	std::string absolutePath = "/home/jabbar/SammTechnology/Perimeter_calculator/src/data/";
	std::string suffix = "capitals.geojson";
	std::ifstream capitals(absolutePath+suffix);
	json capitals_info;
	capitals >> capitals_info;

	//if(capitals_info.contains("features"))
	//{
		//auto var = capitals_info.find("features");
		//std::cout << var.key() << std::endl;
	//}
	//else
		//std::cout << "Not found " << std::endl;

	for(auto& [key, value] : capitals_info.items()) 

	if(key == "features")
	{
		std::cout << key <<  " : " << value[2]["geometry"].dump(4) << '\n' << std::endl;
	}

	return 0;
}
