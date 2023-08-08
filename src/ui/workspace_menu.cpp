#include "ui/menus/workspace_menu.hpp"
#include "ui/menus/menus.hpp"
#include "utils/utility.hpp"
#include <iostream>

namespace Canvas {
// workspace_menu::workspace_menu() { std::cout << workspace_menu::text <<
// std::endl; }
std::optional<Canvas::Event> WorkspaceMenu::handle(Canvas::Event e) {
  (void)e;
  // switch (e) {

  // }
  return {};
}
std::optional<Canvas::Event> WorkspaceMenu::sf_event2canvas_event(sf::Event e) {
  (void)e;
  return {};
}
} // namespace Canvas
