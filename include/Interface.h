#ifndef INTERFACE_H
#define INTERFACE_H

#include "Maze.h"
#include "Player.h"
#include "Structs.h"
#include <libtcod.h>

namespace TEM {
struct InterfaceConfig {
  short minimap_position_x, minimap_position_y;
};
class Interface {
private:
public:
  Interface(InterfaceConfig config);
  Point2D MapPosition;
  void OutMap(tcod::Console &console, Maze &map, Player &player);
};
} // namespace TEM

#endif // INTERFACE_H
