#include "../include/MainMenu.h"
#include <libtcod/console_drawing.h>
#include <libtcod/console_printing.hpp>

namespace TEM {
MainMenu::MainMenu() : IsActive(true) {
  items.emplace_back("New Game", 0);
  items.emplace_back("Load Game", 1);
  items.emplace_back("Exit", 2);
  height = items.size() + 4;
}

void MainMenu::Render(tcod::Console &console) {
  int consoleWidth = console.get_width();
  int consoleHeight = console.get_height();

  menuX = consoleWidth / 2 - width / 2;
  menuY = consoleHeight - height - 15;
  tcod::draw_frame(console, {menuX, menuY, width, height},
                   {201, 205, 187, 186, 0, 186, 200, 205, 188}, std::nullopt,
                   std::nullopt);

  for (size_t i = 0; i < items.size(); ++i) {
    items[i].x = menuX + 2;
    items[i].y = menuY + 2 + i;

    if (i == selectedItem) {
      tcod::print(console, {items[i].x, items[i].y}, items[i].label,
                  TCOD_ColorRGB({255, 204, 0}), std::nullopt);
    } else {
      tcod::print(console, {items[i].x, items[i].y}, items[i].label,
                  TCOD_ColorRGB({255, 255, 255}), std::nullopt);
    }
  }
}

bool MainMenu::IsInMenu(Point2D position) {
  return position.X >= menuX && position.X < menuX + width &&
         position.Y >= menuY && position.Y < menuY + height;
}

int MainMenu::CheckMouseClick(Point2D mouse_pos) {
  for (size_t i = 0; i < items.size(); ++i) {
    int textX = (i == selectedItem) ? items[i].x : items[i].x + 2;
    int textWidth = items[i].label.length() + ((i == selectedItem) ? 2 : 0);

    if (mouse_pos.X >= textX && mouse_pos.X < textX + textWidth &&
        mouse_pos.Y == items[i].y) {
      selectedItem = i;
      return items[i].id;
    }
  }
  return -1;
}

int MainMenu::Update(int mouseX, int mouseY, bool mouseClick) {
  if (mouseClick && IsInMenu({mouseX, mouseY})) {
    return CheckMouseClick({mouseX, mouseY});
  }

  if (IsInMenu({mouseX, mouseY})) {
    for (size_t i = 0; i < items.size(); ++i) {
      int textX = (i == selectedItem) ? items[i].x : items[i].x + 2;
      int textWidth = items[i].label.length() + ((i == selectedItem) ? 2 : 0);

      if (mouseX >= textX && mouseX < textX + textWidth &&
          mouseY == items[i].y) {
        selectedItem = i;
        break;
      }
    }
  }

  return -1;
}

} // namespace TEM
