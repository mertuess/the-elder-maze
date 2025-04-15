#ifndef PHYSICS_H
#define PHYSICS_H

#include "Maze.h"
#include "Player.h"
#include "Structs.h"

namespace TEM {
class Physics {
private:
  Physics() {}

public:
  static void RayCast(Ray &ray, Player &player, Maze &maze);
};
} // namespace TEM

#endif // PHYSICS_H
