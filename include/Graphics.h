#ifndef GRAPHICS_H
#define GRAPHICS_H

namespace TEM {
class Graphics {
private:
  static int _wallShadeSymb[4];
  Graphics() {}

public:
  static int GetWallShade(double depth, double distanceToWall);
  static int *GetWallShadeArr();
};
} // namespace TEM

#endif // GRAPHICS_H
