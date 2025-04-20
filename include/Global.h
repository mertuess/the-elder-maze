#ifndef GLOBAL_H
#define GLOBAL_H

#include <fmt/core.h>
#include <string>
#include <vector>

namespace TEM {
class Global {
private:
  Global();

public:
  static std::vector<std::string> messages;
  template <typename... Args>
  static void SendMessage(fmt::string_view fmt, Args &&...args) {
    if (messages.size() >= 11) {
      messages.erase(messages.begin());
    }
    messages.push_back(fmt::format(fmt, std::forward<Args>(args)...));
  }
};
} // namespace TEM

#endif // GLOBAL_H
