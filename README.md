## Border Security System

A Terminal-based application to calculate the distance among points provided by Geographic coordinate system see [countries.geojson](https://github.com/JabSYsEmb/Perimeter_calculator/blob/main/src/data/countries.geojson).

## Prerequisite

- cmake 3.15 and above
- c++17 

## Compilation of the project

At first, it's needed to change the path in [parser.hpp](https://github.com/JabSYsEmb/Perimeter_calculator/blob/main/src/parser.hpp#L111) at the 111. line to point to the geojsons files and check if names are written correctly.

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
![default trace](./content/screenshot.png)

Now, we need to execute the application in terminal 
``` 
./bss -c [ISO_A3] -t [border/center]
ISO_A3         : country of interest {Default: All} [not case-sensitive]
border/center  : type of calculation {Default: border}
```
Examples:
```
For calculate border of Azerbaijan
./bss -c {AZE or aze} -t border
For calculate sensing cable length of Azerbaijan
./bss -c AZE -t cable
```
