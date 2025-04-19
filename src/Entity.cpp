#include "../include/Entity.h"
#include "Structs.h"

namespace TEM {
Entity::Entity() : System({{.0, .0}, .0}) {}
Entity::Entity(Entity_System System) : System(System) {}
Point2D Entity::ConvertPosition() {
  return {static_cast<int>(System.Position.X),
          static_cast<int>(System.Position.Y)};
}
} // namespace TEM
