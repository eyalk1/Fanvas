#include "ui/menus/directories_menu.hpp"
#include "ui/menus/menus.hpp"
#include "utils/utility.hpp"
#include <iostream>
#include <optional>

namespace Canvas {
// directories_menu::directories_menu() { std::cout << "directories_menu::text
// "<< std::endl; }
std::optional<Canvas::Event> DirectoriesMenu::handle(Canvas::Event e) {
  (void)e;
  // switch (e) {

  // }
  return {};
}
std::optional<Canvas::Event> DirectoriesMenu::sf_event2canvas_event(sf::Event e){
    (void)e;
    return{};
  }
} // namespace Canvas
