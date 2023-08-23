#pragma once
#include "ui/menus/menus-fwd.hpp"
#include <SFML/Window/Event.hpp>
#include <string_view>
namespace Canvas {

struct MainMenu {
  constexpr static std::string_view text =
      "d: manage directories\ns: settings\nq: quit and save\nw: open "
      "workspace\nf: find functions";
  MainMenu();
  void handle(Canvas::Event e,
              std::output_iterator<Canvas::Event> auto to_push);
  void sf_event2canvas_event(sf::Event e,
                             std::output_iterator<Canvas::Event> auto to_push);
};
// implementations
void MainMenu::handle(Canvas::Event e,
                      std::output_iterator<Canvas::Event> auto to_push) {
  (void)to_push;
  (void)e;
}
void MainMenu::sf_event2canvas_event(
    sf::Event e, std::output_iterator<Canvas::Event> auto to_push) {
  (void)to_push;
  (void)e;
}
} // namespace Canvas
