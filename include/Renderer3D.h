#ifndef RENDERER_H
#define RENDERER_H

#include "Maze.h"
#include "Player.h"
#include "libtcod.h"

namespace TEM {
class Renderer3D {
private:
public:
  Renderer3D();
  void RenderWalls(tcod::Console &console, Player &player, Maze &maze);
};
} // namespace TEM

#endif // RENDERER_H
