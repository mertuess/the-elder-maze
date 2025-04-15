#ifndef GRAPHICS_H
#define GRAPHICS_H

namespace TEM {
class Graphics {
private:
  static char _wallShadeSymb[4];
  Graphics() {}

public:
  static char GetWallShade(double depth, double distanceToWall);
};
} // namespace TEM

#endif // GRAPHICS_H
