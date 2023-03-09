#pragma once
#include "UIManager.hpp"
#include "WindowManager.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <optional>

namespace Canvas {
class App {
public:
  App(sf::VideoMode rw);
  auto handle_event(sf::Event) -> void;
  sf::RenderWindow m_render_window;
  WindowManager m_window_manager;
  UIHandler m_ui;
  WindowSet window_id;
private:
  auto handle_mouse(sf::Event mouse) -> void;
  auto handle_keypress(sf::Event keypress) -> void;
};
} // namespace Canvas
