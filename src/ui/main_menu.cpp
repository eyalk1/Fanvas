#include "ui/menus/main_menu.hpp"
#include "ui/menus/menus.hpp"
#include "utils/utility.hpp"
#include <iostream>
#include <optional>

namespace Canvas {
MainMenu::MainMenu() { std::cout << MainMenu::text << std::endl; }
std::optional<Canvas::Event> MainMenu::handle(Canvas::Event e) {
  (void)e;
  // switch (e) {

  // }
  return {};
}
std::optional<Canvas::Event> MainMenu::sf_event2canvas_event(sf::Event e){
    (void)e;
    return{};
  }
} // namespace Canvas
