#include "ui/menus/find_menu.hpp"
#include "ui/menus/menus.hpp"
#include "utils/utility.hpp"
#include <iostream>
#include <optional>

namespace Canvas {
// find_menu::find_menu() { std::cout << find_menu::text << std::endl; }
std::optional<Canvas::Event> FindMenu::handle(Canvas::Event e) {
  (void)e;
  // switch (e) {

  // }
  return {};
}
std::optional<Canvas::Event> FindMenu::sf_event2canvas_event(sf::Event e) {
  (void)e;
  return {};
}
} // namespace Canvas
