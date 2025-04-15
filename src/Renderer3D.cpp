#include "../include/Renderer3D.h"
#include "../include/Graphics.h"
#include "Physics.h"
#include "Structs.h"

namespace TEM {
Renderer3D::Renderer3D() {}
void Renderer3D::RenderWalls(tcod::Console &console, Player &player,
                             Maze &maze) {
  int _width = console.get_width();
  int _height = console.get_height();
  for (int x = 0; x < _width; x++) {
    Ray ray = player.MakeRay(x, _width);
    Physics::RayCast(ray, player, maze);
    double _h = static_cast<double>(_height);
    int celling = _h / 2.0 - _h * player.FieldOfView / ray.DistanceToWall;
    int floor = _height - celling;
    char wallShade = Graphics::GetWallShade(player.Depth, ray.DistanceToWall);
    for (int y = 0; y < _height; y++) {
      if (y <= celling) {
        console.at({x, y}).ch = ' ';
      } else if (y > celling && y <= floor) {
        console.at({x, y}).ch = wallShade;
      } else {
        console.at({x, y}).ch = '.';
      }
    }
  }
}
} // namespace TEM
