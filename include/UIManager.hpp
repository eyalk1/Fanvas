#ifndef UIHANDLER__HPP
#define UIHANDLER__HPP
#include "UserAction.hpp"
#include "WindowManager.hpp"
#include <SFML/Window/Event.hpp>
#include <list>

namespace Canvas {

using Actions = std::array<std::optional<Canvas::UserAction>,
                           MAX_NUMBER_OF_ACTIONS_PER_EVENT>;

struct FindWindowsFromWindowManager {
  FindWindowsFromWindowManager(WindowManager &wm) : wm(wm) {}
  auto operator()(auto p) { return wm.findWindows(p); }

private:
  WindowManager &wm;
};

struct UIHandler {
  UIHandler(FindWindowsFromWindowManager find_windows);
  // TODO: make return a bunch of events?
  auto handle_event(sf::Event event) -> Actions;

private:
  auto handle_keypress(sf::Event::KeyEvent event) -> Actions;
  auto handle_mouse_press(sf::Event::MouseButtonEvent mouse) -> Actions;
  auto handle_mouse_release(sf::Event::MouseButtonEvent mouse) -> Actions;
  auto handle_mouse_move(sf::Event::MouseMoveEvent mouse) -> Actions;
  FindWindowsFromWindowManager m_find_windows;
  WindowSet m_curr_hover;
  WindowSet m_selected_windows;
  WindowSet m_highlight_window;
  struct Click {
    bool ctrl;
    sf::Vector2f initial_location;
  };
  Click mouse_press;
  auto window_under_mouse(int x, int y) -> WindowSet;
};
} // namespace Canvas
#endif // UIHANDLER__HPP
