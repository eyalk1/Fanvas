#include "ui/menus/main_menu.hpp"
#include "ui/menus/menus.hpp"
#include "utils/utility.hpp"
#include <iostream>

namespace Canvas {
main_menu::main_menu() { std::cout << main_menu::text << std::endl; }
maybe_event_menu main_menu::handle(Canvas::Event e) {
    UNUSED(e);
    (void)e;
  // switch (e) {
  
  // }
    return {};
 }
} // namespace Canvas
