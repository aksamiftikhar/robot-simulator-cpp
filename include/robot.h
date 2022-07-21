#ifndef ROBOT_H_
#define ROBOT_H_

#include "world.h"



// Forward declaration
class World;

struct position
{
    int x, y;
};
enum class move_dir {RIGHT=0, UP=1, LEFT=2, DOWN=3};
enum class direction_changer {CC_DIRECTION = 1, RANDOM_DIRECTION = 2};

// Define and implement the following class
class Robot {
    private: 
        char name;
        position robot_world_pos; // robot position assuming a specific world coordinates
        move_dir robot_direction; // each robot can move in its own direction
        int speed;                // each robot can move at a different speed -> 5 levels: 1-5 (higher the level, faster the robot)
        direction_changer directionChangeMethod; // each robot can move either counter-clockwise or randomly in case it cannot move further in its currect direction

        static position getMovementOffset(move_dir); // Returns position offsets according to robot movement direction
        move_dir getRandomDirection(); // randomly chooses and returns new robot direction
        move_dir getCcDirection();     // return the next direction in counter-clockwise way
    
    public:
        Robot();          // robot intialized with default class members
        Robot(char nm); 
        Robot(char nm, position pos); 
        Robot(char nm, position pos, int spd);
        Robot(char nm, position pos, int spd, move_dir dir);

        /*
        * getter/setter methods
        */
        char getName();
        position getPosition();
        void setPosition(int x, int y);
        void setPosition(position p);
        void setSpeed(int spd); // 5 levels: 1-5 (higher the level, faster the robot)
        int getSpeed();
        move_dir getRobotDirection();
        void setRobotDirection(move_dir);
        void setDirectionChangeMethod(direction_changer methodID); // methodID: CC_DIRECTION->1, RANDOM_DIRECTION->2

        /*
        * move the robot with respect to the world represented by w
        */
        void move(World *w);
};


#endif
