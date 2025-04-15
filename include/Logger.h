#ifndef LOGGER_H
#define LOGGER_H

#include <chrono>
#include <fmt/chrono.h>
#include <fmt/core.h>

namespace TEM {
class Logger {
private:
  Logger();

public:
  template <typename... Args>
  static void Print(fmt::string_view fmt, Args &&...args) {
    fmt::print("[{:%H:%M}] {}", std::chrono::system_clock::now(),
               fmt::format(fmt, std::forward<Args>(args)...));
  }
};
} // namespace TEM

#endif // LOGGER_H
