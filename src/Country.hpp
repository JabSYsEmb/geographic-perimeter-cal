#include "json.hpp"

namespace country
{
	struct points{
		double _lon;
		double _lat;
	};
	typedef struct points coordinate;

	class Country
	{
		private:
			std::string _name{};
			std::string _iso_a3{};			
			std::string _calcType{};
			coordinate _coordinate; 
			double _length{};
		public:
			Country(std::string name, std::string iso_a3, double lat, double lon, std::string calcType) 
			{
				_name = name;
				_iso_a3 = iso_a3;
				_calcType = calcType;
				_coordinate._lat = lat;
				_coordinate._lon = lon;
			}
			
			Country(std::string name, std::string iso_a3, double lat, double lon) 
			{
				_name = name;
				_iso_a3 = iso_a3;
				_coordinate._lat = lat;
				_coordinate._lon = lon;
			}

			Country(std::string name, std::string iso_a3, std::string calcType) 
			: _name{name}, _iso_a3{iso_a3}, _calcType{calcType} {};

			Country() {}

			std::string getName(void);
			std::string getISO(void);
			std::string getCalcType(void);
			nlohmann::json get_json(void);
			coordinate getCoordinate(void);
			void setLength(double _length);
			void setName(std::string _name);
			void setISO(std::string _iso_a3);
			void setCountry(country::Country _country);
			void setIsBorderOrCable(std::string _isBorderOrCable);
			bool is_borderType(void);
			double getLength(void);
			void toString();
	};

	void Country::setLength(double length)
	{
		_length = length;
	}

	void Country::toString()
	{
		std::cout << _name << " (" << _iso_a3 << ")" << std::endl;
 	}
	nlohmann::json Country::get_json(void)
	{
		nlohmann::json country_json;
		country_json["name"]   = _name;
		country_json["iso_a3"] = _iso_a3;
		if(is_borderType()) 
			country_json["border"] = _length; 
		else
			country_json["cable"] = _length;
		return country_json;
	}

	double Country::getLength(void)
	{
		return _length;
	}
	std::string Country::getName(void)
	{
		return _name;
	}

	std::string Country::getISO(void)
	{
		return _iso_a3;
	}
	

	coordinate Country::getCoordinate(void)
	{
		return _coordinate;
	}
		
	std::string Country::getCalcType(void)
	{
		return _calcType;
	}
	
	bool Country::is_borderType(void)
	{
		if(_calcType== "CABLE")
			return false;
		return true;
	}
}
