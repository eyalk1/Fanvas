#pragma once
#include "ui/menus/menus-fwd.hpp"
#include <string_view>
namespace Canvas {

struct main_menu {
  constexpr static std::string_view text =
      "d: manage directories\ns: settings\nq: quit and save\nw: open "
      "workspace\nf: find functions";
  main_menu();
  maybe_event_menu handle(Canvas::Event e);
};
} // namespace Canvas
