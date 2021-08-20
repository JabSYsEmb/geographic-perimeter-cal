namespace country
{
	class Coordinates
	{
		private:
			int coordinates[]; 
		public:
			Coordinates(const int* arrayCoordinates) const 
			{
				this.coordinates{arrayCoordinates};	
			};
			~Coordinates() = default;
	}	

	class Country
	{
		private:
			std::string _name{};
			std::string _iso_a3{};			
			bool _isBorderOrCable{}; //True -> Border, false -> Cable
		public:
			Country(std::string name, std::string iso_a3, bool isBorder) : 
				_name{name}, _iso_a3{iso_a3}, _isBorderOrCable{isBorder} {}

			int getBorderLength (const Coordinates& coordinates)
			{
				return nullptr;
			}

			int getDistanceToCapital (const Coordinates& coordinates)
			{
				return nullptr;
			}
		
	}
}
