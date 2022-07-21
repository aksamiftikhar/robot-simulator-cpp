#include <iostream>
#include <thread>
#include <chrono>
#include <pthread.h>
#include <thread>


#include "world.h"
#include "robot.h"

World::World(char map[7][7]) {
  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 7; j++) {
      map_[i][j] = map[i][j];
    }
  }
  countRobots = 0;
}

World::World() {
  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 7; j++) {
        if(i==0 || j==0 || i==6 || j==6)
            map_[i][j] = '1';
        else
            map_[i][j] = '0';
    }
  }
  countRobots = 0;
}
/*  places robot in world map, if the position at (row, col) is free and 
*   the world is not too much populated (number of total robots after adding 
*   Robot r is less than the allowed limit).
*/ 
bool World::addRobot(int row, int col, Robot *r) {
    // check if currently 
    if(countRobots < NUM_ROBOTS)
    {   
        if(map_[row][col]=='0')
        {
            map_[row][col] = r->getName();        
            robots[countRobots++] = r;
            return true;
        }
        else
        {
            std::cout << "Error: cannot place robot at (" << row << ", " 
                      << col << "). Position already occupied!" << std::endl;
            return false;
        }
    }
    else
    {
        std::cout << "Error: cannot place robot at (" << row << ", " 
                      << col << "). There are already too many robots!" << std::endl;
        return false;    
    }
}
bool World::addRobot(position p, Robot *r) {
    int x = p.x;
    int y = p.y;
    return addRobot(x, y, r);
}


void World::moveRobotInWorld(World *w, int idx)
{
    Robot *r = w->getRobot(idx);
    while (true) {
        r->move(w);
        std::this_thread::sleep_for(std::chrono::milliseconds(r->getSpeed()));
    }
}

Robot *World::getRobot(int idx)
{
    return robots[idx];
}
// This methods run multiple threads for moving each robot
void World::run() {
    // Number of threads are equal to number of robots placed in world
    std::thread *robotThreads[countRobots];
        
    for(int i=0;i<countRobots;i++)
        // create/run (spawn) thread for each robot movement
        robotThreads[i] = new std::thread(World::moveRobotInWorld, this, i); // i is the robot number
    
    // display world map with robots continuously
    while(true)
    {
        display();
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
}

void World::display() {
  // "Clear" screen
  static int i = 0;
  for (int i = 0; i < 25; i++)
    std::cout << std::endl;
//   std::cout << i++ << " " << countRobots << std::endl;
  
  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 7; j++) {
      std::cout << map_[i][j] << ' ' ;
    }
    std::cout << std::endl << std::endl;
  }
}


char World::getMapPoint(int x, int y)
{
    return map_[x][y];
}

void World::setMapPoint(int x, int y, char c)
{
    map_[x][y] = c;
}
