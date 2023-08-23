#pragma once
#include "UserAction.hpp"
#include "ui/menus/menus-fwd.hpp"
#include <SFML/Window/Event.hpp>
namespace Canvas {

// list of settings with their values
// whenyou click a settings you can modify the value
struct SettingsMenu {
  void handle(Canvas::Event e,
              std::output_iterator<Canvas::Event> auto to_push);
  void sf_event2canvas_event(sf::Event e,
                             std::output_iterator<Canvas::Event> auto to_push);
};
} // namespace Canvas
// impementations
namespace Canvas {
void SettingsMenu::handle(Canvas::Event e,
                          std::output_iterator<Canvas::Event> auto to_push) {
  (void)to_push;
  (void)e;
}
void SettingsMenu::sf_event2canvas_event(
    sf::Event e, std::output_iterator<Canvas::Event> auto to_push) {
  (void)to_push;
  (void)e;
}
} // namespace Canvas
