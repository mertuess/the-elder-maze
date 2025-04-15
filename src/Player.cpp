#include "../include/Player.h"
#include "Creature.h"
#include "Logger.h"
#include <cmath>

namespace TEM {
Player::Player(Vector2D position, double rotation, unsigned short health,
               unsigned int level,
               std::vector<std::pair<unsigned short, unsigned short>> inventory)
    : Creature(position, rotation, health, level, inventory) {
  to_next_level = 2500;
  exp = 0;
}

void Player::Move(Maze &maze, double speed) {
  Creature::Entity::Position.X += std::sin(Creature::Entity::Rotation) * speed;
  Creature::Entity::Position.Y += std::cos(Creature::Entity::Rotation) * speed;
  Point2D converted_pos = ConvertPosition();

  if (maze.View[converted_pos.Y * maze.GetW() + converted_pos.X] == '#') {
    Creature::Entity::Position.X -=
        std::sin(Creature::Entity::Rotation) * speed;
    Creature::Entity::Position.Y -=
        std::cos(Creature::Entity::Rotation) * speed;
  }
  TEM::Logger::Print("Player Info:\n\tPosition: [{}, {}]\n\tRotation: {}",
                     Creature::Entity::Position.X, Creature::Entity::Position.Y,
                     Creature::Entity::Rotation);
}

void Player::Rotate(double speed) {
  Creature::Entity::Rotation += M_PI / 2 * speed;
  TEM::Logger::Print("Player Info:\n\tPosition: [{}, {}]\n\tRotation: {}",
                     Creature::Entity::Position.X, Creature::Entity::Position.Y,
                     Creature::Entity::Rotation);
}

Ray Player::MakeRay(int x, int width) {
  Ray rRay;
  rRay.Angle =
      Creature::Entity::Rotation + FieldOfView / 2 - x * FieldOfView / width;
  rRay.X = std::sin(rRay.Angle);
  rRay.Y = std::cos(rRay.Angle);
  return rRay;
}
} // namespace TEM
