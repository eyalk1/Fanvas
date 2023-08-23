#pragma once
#include "ui/menus/menus-fwd.hpp"
#include <SFML/Window/Event.hpp>

namespace Canvas {
struct WorkspaceMenu {
  void handle(Canvas::Event e,
              std::output_iterator<Canvas::Event> auto to_push);
  void sf_event2canvas_event(sf::Event e,
                             std::output_iterator<Canvas::Event> auto to_push);
};
void WorkspaceMenu::handle(Canvas::Event e,
                           std::output_iterator<Canvas::Event> auto to_push) {
  (void)to_push;
  (void)e;
}
void WorkspaceMenu::sf_event2canvas_event(
    sf::Event e, std::output_iterator<Canvas::Event> auto to_push) {
  (void)to_push;
  (void)e;
}
} // namespace Canvas
