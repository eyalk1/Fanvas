#pragma once
#include "UserAction.hpp"
#include "ui/menus/menus-fwd.hpp"
#include <SFML/Window/Event.hpp>
namespace Canvas {

// list of settings with their values
// whenyou click a settings you can modify the value
struct SettingsMenu {
  [[nodiscard]] std::optional<Canvas::Event> handle(Canvas::Event e);
  [[nodiscard]] std::optional<Canvas::Event> sf_event2canvas_event(sf::Event e);
};
} // namespace Canvas
