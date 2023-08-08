#pragma once
#include "UserAction.hpp"
#include <SFML/Window/Event.hpp>

namespace Canvas {

struct CanvasManager {
  std::optional<Canvas::Event> sf_event2canvas_event(sf::Event const &e);
  std::optional<Canvas::Event> handle(Canvas::Event const &e);

};
} // namespace Canvas
