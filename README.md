# RoverC++ Project

#overview

This project is split into a controller library and a rover library. The latter contains the rover model its a description of its constraints.
The controller library contains a facility to control up to for independent instances. As I was bound to C++14, there you will not find any usage 
of concept, which would have been nice. Most of the interfaces between the roverLib and the controllerLib are checked during compile time.
## build instructions

```
cd <path for the repo>
git clone --recursive https://github.com/lukasTolksdorf/RoverCpp.git .
cd RoverC++
mkdir build && cd build
cmake -GNinja ..
ninja
```

## Run Application with example input
```
cd build
cat ../common/example/test.txt | ./RoverController/RoverController
```
## Run Test
the roverLib and the controller lib both come with Unit test with a cmake target, namely Ut_controllerLib and Ut_roverLib
```
cd build
cmake -GNinja ..
ninja Ut_<libName>
./<libName>/test/Ut_<libName>
```