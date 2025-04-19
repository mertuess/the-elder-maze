#ifndef PLAYER_H
#define PLAYER_H

#include "Creature.h"

namespace TEM {
class Player : public Creature {
private:
public:
  Player();
  Player(Creature creature);
  Ray MakeRay(int x, int width);
  const double FieldOfView = M_PI / 4;
  const double Depth = 16.0;
};
} // namespace TEM

#endif // !PLAYER_H
