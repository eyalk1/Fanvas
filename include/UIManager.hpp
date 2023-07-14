#ifndef UIHANDLER__HPP
#define UIHANDLER__HPP
#include "event_generator.hpp"
#include "UserAction.hpp"
#include "WindowManager.hpp"
#include "consts.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <string>
#include <string_view>

namespace Canvas {

struct UIHandler : public event_generator<UIHandler> {
  friend class event_generator<UIHandler>;

  UIHandler();
  // through this function we handle events from the outside
  auto handle_event(Canvas::Event event) -> void;

  auto is_window_open() -> bool;

private:
  // this function checks internal state to see if there is an event that the UI
  // produces e.g. user requested to add a directory for pulling functions from
  auto generate_event_impl() -> std::optional<Canvas::Event>;
  // check if the event is handelable by the uihandler if so - handle
  auto handle_on_satisfy_impl(Canvas::Event const &event) -> void;

  enum surface { canvas, window, selected_window };

  // process generic sf event - turning it into a canvas event
  auto process_sf_event(sf::Event event) -> std::optional<Canvas::Event>;

  // take specific sf event and 1: return events for the external world, 2:
  // handle internal affects. this could be only no.1 but sending an event that
  // you know you're gonna handle is stupid
  auto handle_keypress(sf::Event::KeyEvent event) -> std::optional<Canvas::Event>;
  auto handle_mouse_press(sf::Event::MouseButtonEvent mouse) -> std::optional<Canvas::Event>;
  auto handle_mouse_release(sf::Event::MouseButtonEvent mouse) -> std::optional<Canvas::Event>;
  auto handle_mouse_move(sf::Event::MouseMoveEvent mouse)
      -> std::optional<Canvas::Event>;
  auto mouse_press_to_actions(bool is_ctrl, surface on,
                              WindowSet clicked_window)
      -> std::optional<Canvas::Event>;

  // handle actual dispatching of the internal events
  auto update_mouse_hover(sf::Event::MouseMoveEvent mouse) -> void;
  void add_window(std::string_view header, std::string_view source);
  auto select_window(WindowSet clicked, WindowSet last = {}) -> void;
  auto highlight_window(WindowSet clicked, WindowSet last = {}) -> void;
  std::string title;
  sf::RenderWindow m_render_window;
  WindowManager m_window_manager;
  WindowSet m_curr_hover;
  WindowSet m_selected_windows;
  WindowSet m_highlight_window;
  // utilities
  auto window_under_mouse(int x, int y) -> WindowSet;
  };
} // namespace Canvas
#endif // UIHANDLER__HPP
