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
  std::optional<Canvas::Event> handle(Canvas::Event e);
  std::optional<Canvas::Event> sf_event2canvas_event(sf::Event e);
};
} // namespace Canvas
