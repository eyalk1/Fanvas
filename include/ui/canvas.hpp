#pragma once
#include "UserAction.hpp"
#include <SFML/Window/Event.hpp>

namespace Canvas {

struct CanvasManager {
  [[nodiscard]] std::optional<Canvas::Event> sf_event2canvas_event(sf::Event const &e);
  [[nodiscard]] std::optional<Canvas::Event> handle(Canvas::Event const &e);

};
} // namespace Canvas
