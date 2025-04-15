#include "../include/Maze.h"

#include "../include/Logger.h"
#include <random>
#include <stdexcept>

namespace TEM {
// Public methods
Maze::Maze(short width, short height)
    : width(width), height(height), real_w(width * 2 + 1),
      real_h(width * 2 + 1) {
  if (width < 0 || height < 0) {
    throw std::invalid_argument(
        "Wrong sizes of map! Width and height can't be less then 0");
  }

  maze.resize(height, std::vector<MazeCell>(width));
  View.resize(real_w * real_h, '.');
  for (int h = 1; h <= real_h; h++) {
    View[real_w * h - 1] = '#';
  }
  for (int w = 0; w < real_w; w++) {
    View[real_h * real_w - real_w + w] = '#';
  }
}

std::vector<std::vector<MazeCell>> Maze::GetMaze() const { return maze; }
short Maze::GetW() const { return real_w; }
short Maze::GetH() const { return real_h; }

void Maze::Generate() {
  Logger::Print("Start maze generation\n");
  carve({0, 0});
  convert();
}

// Private methods
void Maze::carve(Point2D position) {
  try {
    maze[position.Y][position.X].Visited = true;
    maze[position.Y][position.X].Opened = false;
    std::vector<std::pair<int, int>> directions = {
        {0, -1}, // Top
        {1, 0},  // Right
        {0, 1},  // Bottom
        {-1, 0}  // Left
    };

    static auto rng = std::default_random_engine{};
    rng.seed(std::chrono::system_clock::now().time_since_epoch().count());
    std::shuffle(std::begin(directions), std::end(directions), rng);

    for (const auto &dir : directions) {
      int nx = position.X + dir.first;
      int ny = position.Y + dir.second;

      if (nx >= 0 && nx < width && ny >= 0 && ny < height &&
          !maze[ny][nx].Visited) {
        if (dir.first == 1) { // Right
          maze[ny][nx].WLeft = false;
        } else if (dir.first == -1) { // Left
          maze[position.Y][position.X].WLeft = false;
        } else if (dir.second == 1) { // Bottom
          maze[ny][nx].WTop = false;
        } else if (dir.second == -1) { // Top
          maze[position.Y][position.X].WTop = false;
        }
        EndPoint.X = nx * 2 + 1;
        EndPoint.Y = ny * 2 + 1;
        carve({nx, ny});
      }
    }
  } catch (const std::exception &ex) {
    Logger::Print("Exception catched: {0}!\n", ex.what());
  }
}

void Maze::convert() {
  Logger::Print("Final End point is: [ {0}, {1} ]\n", EndPoint.X, EndPoint.Y);
  Logger::Print("Convert maze to array...\n");
  try {
    for (int y = 0; y < height; ++y) {
      for (int x = 0; x < width; ++x) {
        View[y * real_w * 2 + x * 2] = '#';
        if (maze[y][x].WLeft)
          View[y * real_w * 2 + x * 2 + real_w] = '#';
        if (maze[y][x].WTop)
          View[y * real_w * 2 + x * 2 + 1] = '#';
      }
    }
    View[EndPoint.Y * real_w + EndPoint.X] = 'E';
    Logger::Print("Converted!\n");
  } catch (const std::exception &ex) {
    Logger::Print("Exception catched: {0}!\n", ex.what());
  }
}
} // namespace TEM
