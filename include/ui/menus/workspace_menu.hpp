#pragma once
#include <SFML/Window/Event.hpp>
#include "ui/menus/menus-fwd.hpp"

namespace Canvas {
struct WorkspaceMenu {
  [[nodiscard]] std::optional<Canvas::Event> handle(Canvas::Event e);
  [[nodiscard]] std::optional<Canvas::Event> sf_event2canvas_event(sf::Event e);
};
} // namespace Canvas
