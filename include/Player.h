#ifndef PLAYER_H
#define PLAYER_H

#include "Creature.h"

namespace TEM {
class Player : public Creature {
private:
  double step_treshold = 2.0;
  double step_timer = 0.0;

public:
  Player();
  Player(Creature creature);
  Ray MakeRay(int x, int width);
  double weapon_delta = 75;
  const double FieldOfView = M_PI / 4;
  const double Depth = 16.0;
  bool CanStep();
  void UpdateStepTimer(double speed);
};
} // namespace TEM

#endif // !PLAYER_H
