#include "Creature.h"
#include "Constants.h"
#include "Entity.h"
#include "Global.h"
#include "Logger.h"
#include <chrono>
#include <random>

namespace TEM {
Creature::Creature() : Entity() { recalculate_characteristics(); }
Creature::Creature(Entity entity) : Entity(entity) {
  recalculate_characteristics();
}
Creature::Creature(Entity entity, unsigned int StartLevel, struct Equip Equip)
    : Entity(entity), scalable({StartLevel, 0, 0}), Equip(Equip),
      characteristics({100, 0, 0, 0, 0}) {
  recalculate_characteristics();
}

void Creature::Move(Maze &maze, double speed) {
  if (!IsAlive)
    return;
  System.Position.X += sin(System.Rotation) * speed;
  System.Position.Y += cos(System.Rotation) * speed;
  Point2D converted_pos = ConvertPosition();

  if (maze.View[converted_pos.Y * maze.GetW() + converted_pos.X] == '#') {
    System.Position.X -= sin(System.Rotation) * speed;
    System.Position.Y -= cos(System.Rotation) * speed;
  }
}

void Creature::Rotate(double speed) {
  if (!IsAlive)
    return;
  System.Rotation += M_PI / 2 * speed;
}

void Creature::ChangeHealth(int modificator) {
  if (static_cast<int>(characteristics.Health) +
          static_cast<int>(modificator) <=
      0) {
    IsAlive = false;
    return;
  }
  characteristics.Health += modificator;
}

void Creature::AddExp(unsigned int exp) {
  scalable.Experience += exp;
  level_up();
}

void Creature::recalculate_characteristics() {
  characteristics.DefaultDamage = 10 + scalable.Level * 3;
  characteristics.DefaultArmor = 4 + scalable.Level;
  characteristics.Damage = characteristics.DefaultDamage; // + Weapon
  characteristics.Armor = characteristics.DefaultArmor;   // + Equip
}

void Creature::level_up() {
  if (scalable.Experience <= scalable.Threshold)
    return;

  TEM::Global::SendMessage("Level up!");

  scalable.Experience = 0;
  scalable.Level++;
  scalable.Threshold = scalable.Level * 1000;
  scalable.MaxHP = 100 + (scalable.Level - 1) * 25;
  characteristics.Health = scalable.MaxHP;
  recalculate_characteristics();
}

struct Scalable Creature::GetScalable() const { return scalable; }
struct Characteristics Creature::GetCharacteristics() const {
  return characteristics;
}
unsigned int Creature::GetDamage() const {
  std::random_device r;
  std::default_random_engine e(r());
  e.seed(std::chrono::system_clock::now().time_since_epoch().count());
  std::uniform_int_distribution<int> dist(
      characteristics.Damage - TEM::DAMAGE_DISPERSION,
      characteristics.Damage + TEM::DAMAGE_DISPERSION);
  return dist(e);
}
} // namespace TEM
