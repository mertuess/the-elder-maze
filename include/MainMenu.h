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
  MenuItem(const std::string &label, int id)
      : label(label), id(id), x(0), y(0) {}
};

namespace TEM {
class MainMenu {
private:
  std::vector<MenuItem> items;
  int selectedItem = -1;
  int width = 15;
  int height;
  int menuX, menuY;

public:
  MainMenu();
  void Render(tcod::Console &console);
  bool IsInMenu(Point2D position);
  int CheckMouseClick(Point2D mouse_pos);
  int Update(int mouseX, int mouseY, bool mouseClick);
  bool IsActive;
};
} // namespace TEM

#endif // !MAIN_MENU_H
