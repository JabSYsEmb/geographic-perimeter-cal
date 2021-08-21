#ifndef _MATH_CODE
#define _MATH_CODE
#include <math.h>

#define RADIO_OF_EARTH 6372797.56085

double toRadians(double* degree);
float CalcHaversinDistance(double& latitud1, double& longitud1, double& latitud2, double& longitud2);

float calcDistance(std::valarray<double> point_1, std::valarray<double> point_2)
{
    return double{CalcHaversinDistance(point_1[0],point_1[1],point_2[0],point_2[1])};
}
float calcDistance(coordinate* previous_point, double coordsX, double coordsY)
{	
	return double{CalcHaversinDistance(previous_point->_x,previous_point->_y,coordsX,coordsY)};
}

float CalcHaversinDistance(double& latitud1, double& longitud1, double& latitud2, double& longitud2){
    double temp{0};
    double haversine{0};
    double distancia_puntos{0};
    // std::cout << "fist point \n[ " << latitud1 << "," << longitud1 << "]" << std::endl; 
    // std::cout << "second point \n[ " << latitud1 << "," << longitud2 << "]" << std::endl;
    latitud1  =  toRadians(&latitud1);
    longitud1 =  toRadians(&longitud1);
    latitud2  =  toRadians(&latitud2);
    longitud2 =  toRadians(&longitud2);

    haversine = (pow(sin((latitud2 - latitud1)/2), 2))
                + ((cos(latitud1)) * (cos(latitud2)) 
                * (pow(sin((longitud2 - longitud1)/2), 2)));
                
    temp = 2 * asin(std::min(1.0, sqrt(haversine)));
    distancia_puntos = RADIO_OF_EARTH * temp;
   return distancia_puntos;
}

double toRadians(double* degree) {
    return (*degree) * M_PI / 180;
}
#endif
