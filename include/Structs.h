#ifndef STRUCTS_H
#define STRUCTS_H

#include "Enums.h"
#include <string>
namespace TEM {
struct MazeCell {
  bool WLeft = true, WTop = true, Visited = false, Opened = false;
};
struct Point2D {
  int X;
  int Y;
};
struct Vector2D {
  double X;
  double Y;
};
struct Ray {
  double Angle;
  double X;
  double Y;
  double DistanceToWall = 0;
  bool HitWall = false;
};
struct ItemInfo {
  std::string name;
  std::string description;
  double hp_modificator;
  unsigned short attack_modificator;
  unsigned short armor_modificator;
  EquipType equip_type;
};
} // namespace TEM

#endif // !STRUCTS_H
