#ifndef STRUCTS_H
#define STRUCTS_H

namespace TEM {
struct MazeCell {
  bool WLeft = true, WTop = true, Visited = false, Opened = false;
};
struct Point2D {
  int X;
  int Y;
};
} // namespace TEM

#endif // !STRUCTS_H
