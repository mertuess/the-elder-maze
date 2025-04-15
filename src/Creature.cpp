#include "../include/Creature.h"
#include "Entity.h"

namespace TEM {
Creature::Creature(
    Vector2D position, double rotation, unsigned short health,
    unsigned int level,
    std::vector<std::pair<unsigned short, unsigned short>> inventory)
    : Entity(position, rotation, inventory) {}
} // namespace TEM
