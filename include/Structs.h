#ifndef STRUCTS_H
#define STRUCTS_H

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
struct Entity_System {
  Vector2D Position;
  double Rotation;
};
struct Scalable {
  unsigned int Level = 1;
  unsigned long int Experience = 0;
  unsigned long int Threshold = Level * 1000;
  unsigned int MaxHP = 100 + (Level - 1) * 25;
};
struct Characteristics {
  unsigned int Health = 100;
  unsigned int DefaultDamage = 0;
  unsigned int DefaultArmor = 0;
  unsigned int Damage = 0;
  unsigned int Armor = 0;
};
struct Equip {};
} // namespace TEM

#endif // !STRUCTS_H
