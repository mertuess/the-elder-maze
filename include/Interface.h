#ifndef INTERFACE_H
#define INTERFACE_H

#include "Maze.h"
#include "Player.h"
#include "Structs.h"
#include <fmt/core.h>
#include <libtcod.h>

namespace TEM {
struct InterfaceConfig {
  short minimap_position_x, minimap_position_y;
  int panel_size = 20;
};
class Interface {
private:
  int panel_size;
  std::vector<std::vector<std::string>> asciiLines;
  std::vector<std::string> loadASCII(const std::string &filePath);
  void renderASCII(tcod::Console &console, std::vector<std::string> lines,
                   int x, int y, TCOD_ColorRGB color);
  void drawSeparator(tcod::Console &console, int x);
  const TCOD_ColorRGB COLOR_BG = {79, 32, 15};
  const TCOD_ColorRGB COLOR_FG = {188, 106, 60};
  const TCOD_ColorRGB COLOR_DARK = {56, 23, 11};

public:
  Interface(InterfaceConfig config);
  Point2D MapPosition;
  int weapon_delta;

  void DrawMap(tcod::Console &console, Maze &map, Player &player);
  void DrawPlayerInfo(tcod::Console &console, Player &player);
  void DrawMessages(tcod::Console &console);
  void DrawWeapon(tcod::Console &console);
};
} // namespace TEM

#endif // INTERFACE_H
