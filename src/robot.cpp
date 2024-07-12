#include <iostream>
#include <cstdlib>
#include <ctime>

#include "robot.h"
#include "world.h"

Robot::Robot()
{
    // git change: initialize all data members
    name = 'A'; /* default robot name */
    robot_world_pos.x = -1;
    robot_world_pos.y = -1;           // initial position is undefined
    setSpeed(2);                      // default speed level
    robot_direction = move_dir::LEFT; // default robot direction
}
Robot::Robot(char nm)
{
    name = nm;
    setPosition(-1, -1);              // initial position is undefined
    setSpeed(2);                      // default speed level
    robot_direction = move_dir::LEFT; // default robot direction
}
Robot::Robot(char nm, position pos)
{
    name = nm;
    setPosition(pos);
    setSpeed(2);                      // default speed level
    robot_direction = move_dir::LEFT; // default robot direction
}

Robot::Robot(char nm, position pos, int spd)
{
    name = nm;
    setPosition(pos);
    setSpeed(spd);                    // default speed level
    robot_direction = move_dir::LEFT; // default robot direction
}

Robot::Robot(char nm, position pos, int spd, move_dir dir)
{
    name = nm;
    setPosition(pos);
    setSpeed(spd); // default speed level
    setRobotDirection(dir);
}
char Robot::getName()
{
    return name;
}
position Robot::getPosition()
{
    return robot_world_pos;
}
void Robot::setPosition(int x, int y)
{
    robot_world_pos.x = x;
    robot_world_pos.y = y;
}

void Robot::setPosition(position p)
{
    setPosition(p.x, p.y);
}
// move robot in world rWorld
void Robot::move(World *rWorld)
{
    // get x and y offsets for robot movement according to its current direction
    position offset = getMovementOffset(robot_direction);
    // calculate new x,y position of robot (but don't move the robot yet)
    int newx = robot_world_pos.x + offset.x;
    int newy = robot_world_pos.y + offset.y;

    // check whether the robot can move to the new position?
    // Robot can move only if the new position is empty (unblocked) cell.
    if (rWorld->getMapPoint(newx, newy) == '0')
    {
        /* This block moves the robot to new position and updates the world map. */
        // reset old robot position
        rWorld->setMapPoint(robot_world_pos.x, robot_world_pos.y, '0');
        robot_world_pos.x = newx;
        robot_world_pos.y = newy;
        // move robot to new position
        rWorld->setMapPoint(robot_world_pos.x, robot_world_pos.y, getName());
    }
    else
    {
        // Keep on changing robot direction until an empty cell is found
        do
        {
            /*
             * change robot current direction:
             *      (counter-clockwise:   use getCcDirection)
             *      (random:              use getRandomDirection)
             */
            if (directionChangeMethod == direction_changer::RANDOM_DIRECTION)
                robot_direction = getRandomDirection();
            else
                robot_direction = getCcDirection();
            offset = getMovementOffset(robot_direction);
            // calculate new x,y position of robot (but don't move the robot yet)
            newx = robot_world_pos.x + offset.x;
            newy = robot_world_pos.y + offset.y;

        } while (rWorld->getMapPoint(newx, newy) != '0'); // check for empty cell at (newx, newy)
        // empty cell is found, so update robot coordinates to new position
        // but first reset old robot position
        rWorld->setMapPoint(robot_world_pos.x, robot_world_pos.y, '0');
        robot_world_pos.x = newx;
        robot_world_pos.y = newy;
        // move robot to new position
        rWorld->setMapPoint(robot_world_pos.x, robot_world_pos.y, getName());
    }
}
// randomly chooses and returns new robot direction
move_dir Robot::getRandomDirection()
{
    // current robot direction number for comparison with new direction number
    int currDirectionNum = static_cast<int>(robot_direction);
    /*
     * keep on generating new direction until it is different from
     * current robot direction.
     */
    int rNum; // this will store the randomly generated number
    srand(time(0));
    do
    {
        rNum = static_cast<int>(rand() % 4);
    } while (rNum == currDirectionNum); // check if the new (generated) direction is different from current robot direction

    return static_cast<move_dir>(rNum);
}
// return the next direction in counter-clockwise way
move_dir Robot::getCcDirection()
{
    return static_cast<move_dir>((static_cast<int>(robot_direction) + 1) % 4);
}
// Returns position offsets according to robot movement direction
// Right:   (+1, 0)
// Left:    (-1, 0)
// Up:      (0, -1)
// Down:    (0, +1)
position Robot::getMovementOffset(move_dir dir)
{
    position offset;
    if (dir == move_dir::RIGHT)
    {
        offset.x = +1;
        offset.y = 0;
    }
    else if (dir == move_dir::LEFT)
    {
        offset.x = -1;
        offset.y = 0;
    }
    else if (dir == move_dir::UP)
    {
        offset.x = 0;
        offset.y = -1;
    }
    else
    {
        offset.x = 0;
        offset.y = +1;
    }

    return offset;
}

move_dir Robot::getRobotDirection()
{
    return robot_direction;
}
void Robot::setRobotDirection(move_dir md)
{
    robot_direction = md;
}

void Robot::setSpeed(int spd) // 5 levels: 1-5 (higher the level, faster the robot)
{
    speed = (6 - spd) * 300; // each level reduces a delay of 300 milliseconds
}
int Robot::getSpeed()
{
    return speed;
}

void Robot::setDirectionChangeMethod(direction_changer methodID) // methodID: CC_DIRECTION->1, RANDOM_DIRECTION->2
{
    directionChangeMethod = methodID;
}
