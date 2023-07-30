#pragma once
#include "ui/menus/menus-fwd.hpp"

namespace Canvas {

// on top is text box, on bottom is results
struct find_menu {
  maybe_event_menu handle(Canvas::Event e);
};

} // namespace Canvas
