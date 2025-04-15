#include "../include/Physics.h"

namespace TEM {
void Physics::RayCast(Ray &ray, Player &player, Maze &maze) {
  while (!ray.HitWall && ray.DistanceToWall < player.Depth) {
    ray.DistanceToWall += .1;
    int _testX = (player.Position.X + ray.X * ray.DistanceToWall);
    int _testY = (player.Position.Y + ray.Y * ray.DistanceToWall);
    if (_testX < 0 || _testX >= player.Depth + player.Position.X ||
        _testY < 0 || _testY >= player.Depth + player.Position.Y) {
      ray.HitWall = true;
      ray.DistanceToWall = player.Depth;
    } else {
      char testCell = maze.View[_testY * maze.GetW() + _testX];
      if (testCell == '#')
        ray.HitWall = true;
    }
  }
}
} // namespace TEM
