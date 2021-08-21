#ifndef _MATH_CODE
#define _MATH_CODE
#include <math.h>

#define PI 3.14159265358979323846
#define RADIO_TERRESTRE 6372797.56085
#define GRADOS_RADIANES PI / 180

double CalcGPSDistance(double latitud1, double longitud1, double& latitud2, double& longitud2);

double calcDistance(coordinate* first_point, double coordsX, double coordsY)
{	
	return double{CalcGPSDistance(first_point->_x,first_point->_y,coordsX,coordsY)};
}

double CalcGPSDistance(double latitud1, double longitud1, double& latitud2, double& longitud2){
    double haversine;
    double temp;
    double distancia_puntos;

    latitud1  = latitud1  * GRADOS_RADIANES;
    longitud1 = longitud1 * GRADOS_RADIANES;
    latitud2  = latitud2  * GRADOS_RADIANES;
    longitud2 = longitud2 * GRADOS_RADIANES;

    haversine = (pow(sin((1.0 / 2) * (latitud2 - latitud1)), 2)) + ((cos(latitud1)) * (cos(latitud2)) * (pow(sin((1.0 / 2) * (longitud2 - longitud1)), 2)));
    temp = 2 * asin(std::min(1.0, sqrt(haversine)));
    distancia_puntos = RADIO_TERRESTRE * temp;

   return distancia_puntos;
}

#endif
