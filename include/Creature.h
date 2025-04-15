#ifndef CREATURE_H
#define CREATURE_H

#include "Entity.h"

namespace TEM {
class Creature : public Entity {
private:
public:
  Creature(Vector2D position, double rotation, unsigned short health,
           unsigned int level,
           std::vector<std::pair<unsigned short, unsigned short>> inventory);
  unsigned short health;
  unsigned int level;
};
} // namespace TEM

#endif // !CREATURE_H
