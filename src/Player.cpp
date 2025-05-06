#include "../include/Player.h"
#include "Creature.h"
#include "Logger.h"
#include <cmath>

namespace TEM {
Player::Player() : Creature("You") {}
Player::Player(Creature creature) : Creature(creature) {}

Ray Player::MakeRay(int x, int width) {
  Ray r;
  r.Angle = System.Rotation + FieldOfView / 2 - x * FieldOfView / width;
  r.X = sin(r.Angle);
  r.Y = cos(r.Angle);
  return r;
}

bool Player::CanStep() {
  if (step_timer < .1) {
    step_timer = step_treshold;
    return true;
  }
  return false;
}

void Player::UpdateStepTimer(double speed) {
  if (step_timer > 0.0)
    step_timer -= speed;

  if (weapon_delta < 75)
    weapon_delta += 10.0;
}
} // namespace TEM
