#include "../include/Interface.h"
#include "Constants.h"
#include "Global.h"
#include "Logger.h"
#include <fmt/format.h>
#include <fstream>
#include <libtcod/console_printing.hpp>
#include <vector>

namespace TEM {
TEM::Interface::Interface(InterfaceConfig config)
    : MapPosition({config.minimap_position_x, config.minimap_position_y}),
      panel_size(config.panel_size) {
  asciiLines.push_back(loadASCII("./resources/ascii/sword"));
  asciiLines.push_back(loadASCII("./resources/ascii/sword_2"));
}

void TEM::Interface::DrawMap(tcod::Console &console, Maze &map,
                             Player &player) {
  for (int h = 0; h < map.GetH(); h++) {
    for (int w = 0; w < map.GetW(); w++) {
      console.at({w + MapPosition.X, h + MapPosition.Y}).ch =
          map.View[h * map.GetW() + w];
    }
  }
  tcod::draw_frame(console,
                   {MapPosition.X, MapPosition.Y, map.GetW(), map.GetH()},
                   {201, 205, 187, 186, 0, 186, 200, 205, 188},
                   TCOD_ColorRGB({188, 106, 60}), TCOD_ColorRGB({79, 32, 15}));
  console
      .at({player.ConvertPosition().X + MapPosition.X,
           player.ConvertPosition().Y + MapPosition.Y})
      .ch = 2;
}

void TEM::Interface::DrawWeapon(tcod::Console &console) {
  int x = console.get_width() - asciiLines[0][0].length() + weapon_delta - 75;
  renderASCII(console, asciiLines[0], x, 0, TCOD_ColorRGB({255, 255, 255}));
}

void TEM::Interface::DrawPlayerInfo(tcod::Console &console, Player &player) {
  int _h = console.get_height();
  int _w = console.get_width();

  // Draw panel frame
  tcod::draw_frame(console, {0, _h - panel_size - 2, _w, panel_size + 2},
                   {201, 205, 187, 186, 0, 186, 200, 205, 188}, COLOR_FG,
                   COLOR_BG);
  tcod::draw_frame(console, {1, _h - panel_size - 1, _w - 2, panel_size},
                   {219, 219, 219, 219, 0, 219, 219, 219, 219}, COLOR_BG,
                   COLOR_BG);

  // Draw log frame
  tcod::draw_frame(console, {1, _h - panel_size - 1, 50, panel_size}, {},
                   COLOR_DARK, COLOR_DARK);

  // Player Info
  drawSeparator(console, 51);
  auto s = player.GetScalable();
  auto c = player.GetCharacteristics();
  std::array<std::string, 5> info{
      fmt::format("Level: {}", s.Level),
      fmt::format("Experience: {}/{}", s.Experience, s.Threshold),
      fmt::format("Health: {}/{}", c.Health, s.MaxHP),
      fmt::format("Damage: {}-{}", c.Damage - TEM::DAMAGE_DISPERSION,
                  c.Damage + TEM::DAMAGE_DISPERSION),
      fmt::format("Armor: {}", c.Armor)};

  for (int i = 0; i < info.size() * 2; i += 2) {
    tcod::print(console, {53, console.get_height() - panel_size + i},
                info[i / 2], TCOD_ColorRGB({255, 255, 255}), std::nullopt);
  }
  drawSeparator(console, 81);
}

void TEM::Interface::DrawMessages(tcod::Console &console) {
  int _x = 1;
  int _y = console.get_height() - panel_size - 1;
  for (int i = 0; i < TEM::Global::messages.size(); i++) {
    tcod::print(console, {_x, _y + i}, TEM::Global::messages[i], COLOR_FG,
                COLOR_DARK);
  }
}

std::vector<std::string> Interface::loadASCII(const std::string &filePath) {
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

void Interface::renderASCII(tcod::Console &console,
                            std::vector<std::string> lines, int x, int y,
                            TCOD_ColorRGB color) {
  if (lines.empty())
    return;

  for (size_t i = 0; i < lines.size(); ++i) {
    std::string line = lines[i];
    for (size_t j = 0; j < line.size(); ++j) {
      if (line[j] == ' ')
        continue;
      console.at(static_cast<int>(x + j), static_cast<int>(y + i)).fg = color;
      console.at(static_cast<int>(x + j), static_cast<int>(y + i)).ch = line[j];
    }
  }
}

void Interface::drawSeparator(tcod::Console &console, int x) {
  console.at({x, console.get_height() - panel_size - 2}).ch = 203;
  console.at({x, console.get_height() - 1}).ch = 202;
  for (int y = console.get_height() - panel_size - 1;
       y < console.get_height() - 1; y++) {
    console.at({x, y}).fg = TCOD_ColorRGB(COLOR_FG);
    console.at({x, y}).ch = 186;
  }
}
} // namespace TEM
