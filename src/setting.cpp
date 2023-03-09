#include "../include/setting.hpp"

namespace Canvas {
auto SetSettings() -> Settings & {
  static Settings s;
  return s;
}
auto GetSettings() -> const Settings & { return SetSettings(); }
} // namespace Canvas
