#ifndef PLAYER_H
#define PLAYER_H

#include "Creature.h"
#include "Maze.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace TEM {
class Player : public Creature {
private:
public:
  Player(Vector2D position, double rotation, unsigned short health,
         unsigned int level,
         std::vector<std::pair<unsigned short, unsigned short>> inventory);
  unsigned int exp, to_next_level;
  void Move(TEM::Maze &maze, double speed);
  void Rotate(double speed);
  Ray MakeRay(int x, int width);
  const double FieldOfView = M_PI / 4;
  const double Depth = 16.0;
};
} // namespace TEM

#endif // !PLAYER_H
