#ifndef MAZE_H
#define MAZE_H

#include "Structs.h"
#include <string>
#include <vector>

namespace TEM {
class Maze {
private:
  short width, height;
  short real_w, real_h;
  std::vector<std::vector<MazeCell>> maze;
  void carve(Point2D position);
  void convert();

public:
  Maze(short width, short height);
  void Generate();
  std::string View;
  Point2D EndPoint;

  // Getters
  std::vector<std::vector<MazeCell>> GetMaze() const;
  short GetW() const;
  short GetH() const;
};
} // namespace TEM

#endif // !MAZE_H
