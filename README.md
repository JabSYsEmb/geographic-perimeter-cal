## Border Security System

A Terminal-based application to calculate the distance among points provided by Geographic coordinate system see [countries.geojson](https://github.com/JabSYsEmb/Perimeter_calculator/blob/main/src/data/countries.geojson).

## Prerequisite

- cmake 3.15 and above
- c++17 

## Compilation of the project

At first, it's needed to change the path in [parser.hpp](https://github.com/JabSYsEmb/Perimeter_calculator/blob/main/src/parser.hpp) at the 111. line to point to the geojsons files and check if names are written correctly.

To compile the project, cd into the folder where the project has been downloaded then write the following:

``` bash
mkdir build && cd build
cmake ..
make 
```
The project should be compiled and if you type, you will see as in the screenshot below
``` bash 
ls -la 
```
(./content/screenshot.png)
