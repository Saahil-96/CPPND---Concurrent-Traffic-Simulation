# CPPND: Program a Concurrent Traffic Simulation

<img src="data/traffic_simulation.gif"/>

This is the project for the fourth course in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213): Concurrency. 

## Dependencies for Running Locally
* cmake >= 2.8
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* OpenCV >= 4.1
  * The OpenCV 4.1.0 source code can be found [here](https://github.com/opencv/opencv/tree/4.1.0)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./traffic_simulation`.

## Project Summary

This concurrent traffic simulation should run with red lights controlling traffic, just as in the .gif file above. This project uses different threads to simulate each car and using mutex locks, make sure that each resource that is being shared by all threads is locked and unlocked properly. It is also made sure that appropriate futures and promises are used to allow communication between main and thread and proper notification systems are created for each thread to communicate and know when the traffic light at the intersection turns green. This system also uses a double ended queue to handle messages to make sure that FIFO is followed for all the cars at the intersection.

## Steps Followed by code

1. Simulate environment and start traffic lights to alternate between 4 to 6 milliseconds
2. Start multiple cars on separate threads
3. Cars slow down to 10% speed when 10% of the path remains
4. Once it gets to the intersection, it waits for the traffic light to turn green 
5. Once the traffic light turns green, it lets the promises to all the cars know
6. The thread then permits cars to cross the intersection in the same order they came

**This code makes sure that every time the mutual resources are used, they are locked and unlocked respectively.

## Keywords

C++, Simulation, Synchronization, Threads, Mutex, Promises, Futures
