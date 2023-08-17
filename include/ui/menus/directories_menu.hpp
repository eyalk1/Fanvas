#pragma once
#include "ui/menus/menus-fwd.hpp"
#include <SFML/Window/Event.hpp>
namespace Canvas {

// v-split: left is list of open directories, right is a directory picker
// directory picker:
// mode 1: just a text box with completions
// mode 2: ranger style w/ arrows
// newMenuWindow(vsplit(getDirList(), searchBox()))
struct DirectoriesMenu {
  [[nodiscard]] std::optional<Canvas::Event> handle(Canvas::Event e);
  [[nodiscard]] std::optional<Canvas::Event> sf_event2canvas_event(sf::Event e);
};

} // namespace Canvas
