#include "../include/Player.h"
#include "Creature.h"
#include <cmath>

namespace TEM {
Player::Player() : Creature() {}
Player::Player(Creature creature) : Creature(creature) {}

Ray Player::MakeRay(int x, int width) {
  Ray r;
  r.Angle = System.Rotation + FieldOfView / 2 - x * FieldOfView / width;
  r.X = sin(r.Angle);
  r.Y = cos(r.Angle);
  return r;
}
} // namespace TEM
