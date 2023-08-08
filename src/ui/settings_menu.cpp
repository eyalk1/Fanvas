#include "ui/menus/settings_menu.hpp"
#include "ui/menus/menus.hpp"
#include "utils/utility.hpp"
#include <iostream>
#include <optional>

namespace Canvas {
// settings_menu::settings_menu() { std::cout << settings_menu::text <<
// std::endl; }
std::optional<Canvas::Event> SettingsMenu::handle(Canvas::Event e) {
  (void)e;
  // switch (e) {

  // }
  return {};
}
std::optional<Canvas::Event> SettingsMenu::sf_event2canvas_event(sf::Event e) {
  (void)e;
  return {};
}
} // namespace Canvas
