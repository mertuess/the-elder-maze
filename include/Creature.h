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
  double attack_timer = 0.0;
  double attack_treshold = 2.5;
  std::string name;

public:
  Creature(std::string name);
  Creature(Entity entity, std::string name);
  Creature(Entity entity, std::string name, unsigned int StartLevel,
           struct Equip Equip);

  bool IsAlive = true;
  Equip Equip;

  void Move(TEM::Maze &maze, double speedX, double speedY);
  void Rotate(double speed);
  void AddExp(unsigned int exp);
  void ChangeHealth(int modificator);
  short Attack();
  void UpdateAttack();

  unsigned int GetDamage() const;
  struct Scalable GetScalable() const;
  struct Characteristics GetCharacteristics() const;
};
} // namespace TEM

#endif // !CREATURE_H
