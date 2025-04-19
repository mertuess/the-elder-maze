#ifndef ENTITY_H
#define ENTITY_H

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include "Structs.h"

namespace TEM {
class Entity {
private:
public:
  Entity();
  Entity(Entity_System System);
  Entity_System System;
  Point2D ConvertPosition();
};
} // namespace TEM

#endif // !ENTITY_H
