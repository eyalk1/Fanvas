#pragma once
#include "ui/menus/menus-fwd.hpp"

namespace Canvas {
struct workspace_menu {
  maybe_event_menu handle(Canvas::Event e);
};
} // namespace Canvas
