#include "ui/canvas.hpp"

#include <optional>

namespace Canvas {
std::optional<Canvas::Event> CanvasManager::sf_event2canvas_event(sf::Event const &e) {
  (void)e;
  return {};
}
std::optional<Canvas::Event> CanvasManager::handle(Canvas::Event const &e) {
  (void)e;
  return {};
}
} // namespace Canvas
