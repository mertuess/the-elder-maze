#ifndef CREATURE_H
#define CREATURE_H

#include "Entity.h"
#include "Maze.h"

namespace TEM {
class Creature : public Entity {
private:
  Scalable scalable;
  Characteristics characteristics;
  void level_up();
  void recalculate_characteristics();

public:
  Creature();
  Creature(Entity entity);
  Creature(Entity entity, unsigned int StartLevel, struct Equip Equip);

  bool IsAlive = true;
  Equip Equip;

  void Move(TEM::Maze &maze, double speed);
  void Rotate(double speed);
  void AddExp(unsigned int exp);
  void ChangeHealth(int modificator);

  unsigned int GetDamage() const;
  struct Scalable GetScalable() const;
  struct Characteristics GetCharacteristics() const;
};
} // namespace TEM

#endif // !CREATURE_H
