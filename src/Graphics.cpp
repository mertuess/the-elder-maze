#include "../include/Graphics.h"

namespace TEM {
int Graphics::_wallShadeSymb[4] = {219, 178, 177, 176};
int Graphics::GetWallShade(double depth, double distanceToWall) {
  if (distanceToWall <= depth / 10.0) {
    return _wallShadeSymb[0];
  } else if (distanceToWall < depth / 8.0) {
    return _wallShadeSymb[1];
  } else if (distanceToWall < depth / 6.0) {
    return _wallShadeSymb[2];
  } else if (distanceToWall < depth / 4.0) {
    return _wallShadeSymb[3];
  }
  return ' ';
}
int *Graphics::GetWallShadeArr() { return _wallShadeSymb; }
} // namespace TEM
