#ifndef WORLD_H_
#define WORLD_H_

#include <vector>
#include "robot.h"

#define NUM_ROBOTS 7
#define NUM_ROWS 7
#define NUM_COLS 7

// Forward declaration
class Robot;
struct position;

// Define and implement the following class. Feel free to change the given
// interfaces and data structures to better match your design
class World {
    public:
        World(); // This will create an empty 7x7 world 
        World(char map[NUM_ROWS][NUM_COLS]); // This will initialize the world to map

        Robot *getRobot(int idx);
        char getMapPoint(int x, int y);
        void setMapPoint(int x, int y, char c); // places char c at (x,y) position on world map

        bool addRobot(int row, int col, Robot *r); // place robot at (row, col) position on world map
        bool addRobot(position p, Robot *r); // overloaded version
        void run(); // The run function must be called to keep the robots moving
        void display(); // display the world map

        static void moveRobotInWorld(World *w, int idx);
    private:
        char map_[NUM_ROWS][NUM_COLS]; // world map representated as 2D array of chars
        Robot *robots[NUM_ROBOTS];  // represents all robots on map
        int countRobots; // total number of robots currently on map
};

#endif
