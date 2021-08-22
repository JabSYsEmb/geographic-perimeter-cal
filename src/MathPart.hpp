#ifndef _MATH_CODE
#define _MATH_CODE
#include <math.h>

#define RADIUS_OF_EARTH 6372797.56085

void calcBorderLength(country::Country* country , json& data);
// void calcSensingCableLength(country::Country* country, json& data);

double toRadians(double* degree);
double calcDistanceFromArray(std::valarray<std::valarray<double>> _array_points);
double calcDistance(std::valarray<double> point_1, std::valarray<double> point_2);
double CalcHaversinDistance(double latitud1, double longitud1, double latitud2, double longitud2);
double calcSensingCableLength(country::Country* country, std::valarray<std::valarray<double>> _array_points);

void calcBorderLength(country::Country* country, json& data)
{
    for (auto& _t : data["features"])
    if (_t["properties"]["ISO_A3"] == country->getISO())
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
        country->setLength(distance);
    }
}


void foo(country::Country* country, json& data)
{
    for (auto& _t : data["features"])
    if (_t["properties"]["ISO_A3"] == country->getISO())
    {
        for (auto& _array_points : _t["geometry"]["coordinates"])
            {
                if(!_array_points[0][0].is_array())
                {
                    country->setLength(calcSensingCableLength(country, _array_points));
                }
                else{
                    for (size_t i = 0; i < _array_points.size(); i++)
                    {
                        country->setLength(calcSensingCableLength(country, _array_points[i]));
                    }
                }
            }
    }
}

double calcSensingCableLength(country::Country* country, std::valarray<std::valarray<double>> _array_points)
{   
    double min
    {
        CalcHaversinDistance(
            country->getCoordinate()._lat,country->getCoordinate()._lat,
            _array_points[0][0], _array_points[0][1])
    };

    for (size_t i = 0; i < _array_points.size(); i++)
    {
        min = std::min(
            min,CalcHaversinDistance(country->getCoordinate()._lat,country->getCoordinate()._lat,
                                     _array_points[i][0], _array_points[i][1])
        );
    }
    return min;
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

double calcDistance(std::valarray<double> point_1, std::valarray<double> point_2)
{
    return double{CalcHaversinDistance(point_1[0],point_1[1],point_2[0],point_2[1])};
}


double CalcHaversinDistance(double latitud1, double longitud1, double latitud2, double longitud2){
    double temp{0};
    double haversine{0};
    double distancia_puntos{0};
    latitud1  =  toRadians(&latitud1);
    longitud1 =  toRadians(&longitud1);
    latitud2  =  toRadians(&latitud2);
    longitud2 =  toRadians(&longitud2);

    haversine = (pow(sin((latitud2 - latitud1)/2), 2))
                + ((cos(latitud1)) * (cos(latitud2)) 
                * (pow(sin((longitud2 - longitud1)/2), 2)));
                
    temp = 2 * asin(std::min(1.0, sqrt(haversine)));
    distancia_puntos = RADIUS_OF_EARTH * temp;
   return distancia_puntos;
}

double toRadians(double* degree) {
    return (*degree) * M_PI / 180;
}

#endif
