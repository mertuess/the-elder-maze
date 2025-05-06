#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "Structs.h"
#include <libtcod.h>
#include <string>
#include <vector>

class MenuItem {
public:
  std::string label;
  int id;
  int x, y;
  TEM::Point2D size;
  MenuItem(const std::string &label, int id)
      : label(label), id(id), x(0), y(0), size({0, 0}) {}
};

namespace TEM {
class MainMenu {
private:
  std::vector<MenuItem> items;
  std::vector<std::vector<std::string>> askiiLines;
  int logoX, logoY;
  int selectedItem = -1;
  int width = 150;
  int height;
  int menuX, menuY;
  std::vector<std::string> loadASCII(const std::string &filePath);
  void renderASCII(tcod::Console &console, std::vector<std::string> lines,
                   int x, int y, TCOD_ColorRGB color);
  Point2D renderASCIIText(tcod::Console &console, std::string text, int x,
                          int y, TCOD_ColorRGB color);

public:
  MainMenu();
  void Render(tcod::Console &console);
  bool IsInMenu(Point2D position);
  int Update(int mouseX, int mouseY, SDL_MouseButtonFlags flags);
  bool IsActive;
};
} // namespace TEM

#endif // !MAIN_MENU_H
