#pragma once
#include "ui/menus/menus-fwd.hpp"
#include <SFML/Window/Event.hpp>

namespace Canvas {

// on top is text box, on bottom is results
struct FindMenu {
  std::optional<Canvas::Event> handle(Canvas::Event e);
  std::optional<Canvas::Event> sf_event2canvas_event(sf::Event e);
};

} // namespace Canvas
