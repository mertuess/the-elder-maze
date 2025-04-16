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
    int wallShade = Graphics::GetWallShade(player.Depth, ray.DistanceToWall);
    for (int y = 0; y < _height; y++) {
      auto &tile = console.at({x, y});
      int floorShade;
      double b = 1 - (y - _h / 2.0) / (_h / 2.0) - 1;
      if (std::abs(b) < .4) {
        floorShade = ' ';
      } else if (std::abs(b) < .6) {
        floorShade = Graphics::GetWallShadeArr()[3];
      } else if (std::abs(b) < .85) {
        floorShade = Graphics::GetWallShadeArr()[2];
      } else {
        floorShade = Graphics::GetWallShadeArr()[1];
      }
      if (y <= celling) {
        tile.ch = floorShade;
        tile.fg = TCOD_ColorRGB{41, 49, 51};
      } else if (y > celling && y <= floor) {
        tile.ch = wallShade;
        tile.fg = TCOD_ColorRGB{71, 74, 81};
      } else {
        tile.ch = floorShade;
        tile.fg = TCOD_ColorRGB{100, 100, 100};
      }
    }
  }
}
} // namespace TEM
