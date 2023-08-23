#pragma once
#include "ui/menus/menus-fwd.hpp"
#include <SFML/Window/Event.hpp>

namespace Canvas {

// on top is text box, on bottom is results
struct FindMenu {
  void handle(Canvas::Event e,
              std::output_iterator<Canvas::Event> auto to_push);
  void sf_event2canvas_event(sf::Event e,
                             std::output_iterator<Canvas::Event> auto to_push);
};
//implementations
void FindMenu::handle(Canvas::Event e,
                      std::output_iterator<Canvas::Event> auto to_push) {
  (void)to_push;
  (void)e;
}
void FindMenu::sf_event2canvas_event(
    sf::Event e, std::output_iterator<Canvas::Event> auto to_push) {
  (void)to_push;
  (void)e;
}

} // namespace Canvas
