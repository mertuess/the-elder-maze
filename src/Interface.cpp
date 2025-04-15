#include "../include/Interface.h"

namespace TEM {
TEM::Interface::Interface(InterfaceConfig config)
    : MapPosition({config.minimap_position_x, config.minimap_position_y}) {}

void TEM::Interface::OutMap(tcod::Console &console, Maze &map, Player &player) {
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
} // namespace TEM
