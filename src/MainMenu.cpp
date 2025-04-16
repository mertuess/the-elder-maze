#include "../include/MainMenu.h"
#include "Logger.h"
#include <fstream>
#include <libtcod/console_drawing.h>
#include <libtcod/console_printing.hpp>
namespace TEM {
MainMenu::MainMenu() : IsActive(true) {
  askiiLines.push_back(loadASCII("./resources/ascii/alphabet"));
  askiiLines.push_back(loadASCII("./resources/ascii/logo"));
  askiiLines.push_back(loadASCII("./resources/ascii/skull"));
  items.emplace_back("New Game", 0);
  items.emplace_back("Load Game", 1);
  items.emplace_back("Exit", 2);
  height = items.size() * 8;
}

void MainMenu::Render(tcod::Console &console) {
  renderASCII(console, askiiLines[2],
              console.get_width() - askiiLines[2][0].length() + 25,
              console.get_height() / 2 - askiiLines[2].size() / 2,
              TCOD_ColorRGB({100, 100, 100}));
  renderASCII(console, askiiLines[1], 5, 5, TCOD_ColorRGB({255, 255, 255}));
  int consoleWidth = console.get_width();
  int consoleHeight = console.get_height();

  menuX = 5;
  menuY = consoleHeight - height - 15;
  for (size_t i = 0; i < items.size(); ++i) {
    items[i].x = menuX;
    items[i].y = menuY + i * 8;

    if (i == selectedItem) {
      items[i].size = renderASCIIText(console, items[i].label, items[i].x,
                                      items[i].y, TCOD_ColorRGB({255, 204, 0}));
    } else {
      items[i].size =
          renderASCIIText(console, items[i].label, items[i].x, items[i].y,
                          TCOD_ColorRGB({255, 255, 255}));
    }
  }
}

bool MainMenu::IsInMenu(Point2D position) {
  return position.X >= menuX && position.X < menuX + width &&
         position.Y >= menuY && position.Y < menuY + height;
}

int MainMenu::Update(int mouseX, int mouseY, bool mouseClick) {
  if (mouseClick && IsInMenu({mouseX, mouseY})) {
    return items[selectedItem].id;
  }

  if (IsInMenu({mouseX, mouseY})) {
    for (size_t i = 0; i < items.size(); ++i) {
      if (mouseX >= items[i].x && mouseX < items[i].x + items[i].size.X &&
          mouseY >= items[i].y && mouseY < items[i].y + items[i].size.Y) {
        selectedItem = i;
        break;
      }
    }
  }

  return -1;
}

std::vector<std::string> MainMenu::loadASCII(const std::string &filePath) {
  std::ifstream file(filePath);
  std::vector<std::string> output;
  if (!file.is_open()) {
    TEM::Logger::Print("Failed to load logo file: {}\n", filePath);
    return {};
  }

  std::string line;
  while (std::getline(file, line)) {
    output.push_back(line);
  }
  file.close();
  return output;
}

void MainMenu::renderASCII(tcod::Console &console,
                           std::vector<std::string> lines, int x, int y,
                           TCOD_ColorRGB color) {
  if (lines.empty())
    return;

  for (size_t i = 0; i < lines.size(); ++i) {
    tcod::print(console, {x, static_cast<int>(y + i)}, lines[i], color,
                std::nullopt);
  }
}

Point2D MainMenu::renderASCIIText(tcod::Console &console, std::string text,
                                  int x, int y, TCOD_ColorRGB color) {
  Point2D size = {0, 6};
  int char_h = 6;
  int next_pos_x = 0;
  if (askiiLines[0].empty())
    return size;

  for (int i = 0; i < text.length(); ++i) {
    char ch = text[i];
    int charID = std::toupper(ch) - 'A';
    if (ch == ' ') {
      next_pos_x += 10;
      size.X += 10;
      continue;
    }
    int char_w = askiiLines[0][charID * char_h].length() / 2;
    size.X += 10;
    for (size_t j = 0; j < char_h; ++j) {
      tcod::print(console, {x + next_pos_x, static_cast<int>(y + j)},
                  askiiLines[0][charID * char_h + j], color, std::nullopt);
    }
    next_pos_x += char_w;
  }

  return size;
}

} // namespace TEM
