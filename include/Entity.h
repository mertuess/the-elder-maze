#ifndef ENTITY_H
#define ENTITY_H

#include "Structs.h"
#include <vector>

namespace TEM {
class Entity {
private:
public:
  Entity(Vector2D position, double rotation,
         std::vector<std::pair<unsigned short, unsigned short>> inventory);
  Vector2D Position;
  double Rotation;
  std::vector<std::pair<unsigned short, unsigned short>> Inventory;
  Point2D ConvertPosition();
};
} // namespace TEM

#endif // !ENTITY_H
