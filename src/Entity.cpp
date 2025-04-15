#include "../include/Entity.h"

namespace TEM {
Entity::Entity(Vector2D position, double rotation,
               std::vector<std::pair<unsigned short, unsigned short>> inventory)
    : Inventory(inventory), Position(position), Rotation(rotation) {}
Point2D Entity::ConvertPosition() {
  return {static_cast<int>(Position.X), static_cast<int>(Position.Y)};
}
} // namespace TEM
