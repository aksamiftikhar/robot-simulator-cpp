# Robot simulator
Multi-threaded Robot Movement Simulator

This program simulates autonomous robots running around a 2D world in a multi-threaded program environment. 

This project has two classes, Robot and World. The World class encapsulates a simple 2D world.

* The world map is represented by a 2D data structure of your choice with each
coordinate either blocked or unobstructed. The map is a rectangle of arbitrary
size that is blocked around the entire border and has arbitrary internal
coordinates blocked. You do not have to handle map configuration edge cases.
* World provides a way to place robots, and keeps track of the location of them.
Each robot exists in a single coordinate space. There can be up to a few robots
on the map at a time.
* World provides a movement API for the Robot class.
  * A robot can try to move a single space in any direction (holonomic), but if
   that space is blocked the robot does not move, rather it changes its direction. 
* World continuously displays the world (obstacles plus robots) to the terminal
using ASCII. Below is example output with two robots A and B

1111111\
1A00001\
100B001\
1001101\
1001101\
1000001\
1111111


The Robot class defines a simple autonomous robot.
* The robot should move based on some simple behavior (such as move one space a second in one direction until blocked, then move in another direction (random OR counter-clockwise). This behavior can be different for each instance of Robot and each robot can move with different speed (on a level of 1[slowest]-5[fastest]).
* Robot cannot interact with or have knowledge about the world beyond the move API.
* Each Robot instance runs independently and not depend on a global "tick" (ie, each is in a different thread).

This project can be built with CMake and Make by running the following command from the project directory:
```
mkdir build && cd build && cmake .. && make
```
