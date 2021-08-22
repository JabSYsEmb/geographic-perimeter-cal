namespace country
{
	class Country
	{
		private:
			std::string _name{};
			std::string _iso_a3{};			
			double borderLength{};
			double lengthOfCable{};
			std::string _isBorderOrCable{}; 
		public:
			Country(std::string name, std::string iso_a3, std::string isBorder) : _name{name}, _iso_a3{iso_a3}, _isBorderOrCable{isBorder} {};
			Country() {}

			void setName(std::string _name);
			void setISO(std::string _iso_a3);
			void setBorderLength(double _borderLength);
			void setLengthOfcable(double _lengthOfCable);
			void setIsBorderOrCable(std::string _isBorderOrCable);
			void toString();
	};

	void Country::setLengthOfcable(double _lengthOfCable)
	{
		lengthOfCable = _lengthOfCable;
	}
	void Country::setBorderLength(double _borderLength)
	{
		borderLength = _borderLength;
	}
	void Country::toString()
	{
		std::cout << _name << " (" << _iso_a3 << ")" << std::endl;
 	}
}
