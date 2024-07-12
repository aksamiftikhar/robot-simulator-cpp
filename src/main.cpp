#include <chrono>
#include <iostream>
#include <thread>
#include "world.h"
#include "robot.h"

int main(int argc, char **argv)
{
  // You should customize this data structure and the World constructor to
  // match your chosen data structure.
  char myMap[7][7] = {
      {'1', '1', '1', '1', '1', '1', '1'},
      {'1', '0', '0', '0', '0', '0', '1'},
      {'1', '0', '0', '0', '0', '0', '1'},
      {'1', '0', '1', '1', '1', '1', '1'},
      {'1', '0', '0', '0', '0', '0', '1'},
      {'1', '0', '1', '0', '0', '0', '1'},
      {'1', '1', '1', '1', '1', '1', '1'},
  };

  // comment in main from second user

  // World w;      // uninitialized (empty) world
  World w(myMap); // world initialized to myMap

  // place a couple of robots in world, and run the world
  position p = {1, 1}; // position is defined in robot.h
  Robot r('+', p, 4, move_dir::RIGHT);
  r.setDirectionChangeMethod(direction_changer::CC_DIRECTION);
  w.addRobot(1, 1, &r);

  position p2 = {2, 3};
  Robot r2('-', p2, 2, move_dir::DOWN);
  r2.setDirectionChangeMethod(direction_changer::CC_DIRECTION);
  r2.setRobotDirection(move_dir::DOWN); // move_dir is defined in robot.h
  w.addRobot(2, 3, &r2);

  w.display();
  std::cout << "Initial world map with robots is shown above." << std::endl;
  std::cout << "Press Enter to start moving robots..." << std::endl;
  getchar();

  std::cout << "going to start the movement in 3 seconds ..." << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  std::cout << "going to start the movement in 2 seconds ..." << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  std::cout << "going to start the movement in 1 seconds ..." << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  std::cout << "movement started " << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(500));

  // start robots movement
  w.run();
}
