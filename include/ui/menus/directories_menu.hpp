#pragma once
#include "ui/menus/menus-fwd.hpp"
#include <SFML/Window/Event.hpp>
namespace Canvas {

// v-split: left is list of open directories, right is a directory picker
// directory picker:
// mode 1: just a text box with completions
// mode 2: ranger style w/ arrows
// newMenuWindow(vsplit(getDirList(), searchBox()))
struct DirectoriesMenu {
  void handle(Canvas::Event e,
              std::output_iterator<Canvas::Event> auto to_push);
  void sf_event2canvas_event(sf::Event e,
                             std::output_iterator<Canvas::Event> auto to_push);
};
// implementations
void DirectoriesMenu::handle(Canvas::Event e,
                             std::output_iterator<Canvas::Event> auto to_push) {
  (void)to_push;
  (void)e;
}
void DirectoriesMenu::sf_event2canvas_event(
    sf::Event e, std::output_iterator<Canvas::Event> auto to_push) {
  (void)to_push;
  (void)e;
}

} // namespace Canvas
