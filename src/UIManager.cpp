#include "../include/UIManager.hpp"
#include "../include/UserAction.hpp"
#include "consts.hpp"
#include <SFML/Window/VideoMode.hpp>
#include <expected>
namespace Canvas {
UIHandler::UIHandler()
    : title("shit ass piss"), m_render_window(sf::VideoMode(100, 100), title),
      m_window_manager() {}

auto UIHandler::generate_event_impl() -> std::optional<Canvas::Event> {
  sf::Event event;
  if (m_render_window.pollEvent(event)) {
    return process_sf_event(event);
  }
  return std::nullopt;
}

auto UIHandler::is_window_open() -> bool { return m_render_window.isOpen(); }

auto UIHandler::process_sf_event(sf::Event event)
    -> std::optional<Canvas::Event> {
  switch (event.type) {
  case sf::Event::KeyPressed:
  case sf::Event::KeyReleased:
    return handle_keypress(event.key);

    break;
  case sf::Event::MouseButtonPressed:
    return handle_mouse_press(event.mouseButton);
    break;
  case sf::Event::MouseButtonReleased:
    return handle_mouse_release(event.mouseButton);
    break;
  case sf::Event::MouseMoved:
    return handle_mouse_move(event.mouseMove);
    break;
  default:
      break;
  }
  return {};
}

auto UIHandler::handle_keypress(sf::Event::KeyEvent event)
    -> std::optional<Canvas::Event> {
  // escape should deselct everything
  // delete should delete selected entities
  switch (event.code) {
  case sf::Keyboard::Escape:
    m_render_window.close();
    return Canvas::Event(close_app());
    break;
  case sf::Keyboard::Space:
    add_window("sample header", "source\nbla\blablabla\nnotjs");
    return {};
    break;
  default:
    return {};
    break;
  }
}
void UIHandler::add_window(std::string_view header, std::string_view source) {
  m_window_manager.newTextWindow(std::string(header), std::string(source));
}

auto UIHandler::handle_event(Canvas::Event event) -> void {
  (void)event;
  PASS;
}

auto UIHandler::handle_mouse_release(sf::Event::MouseButtonEvent mouse)
    -> std::optional<Canvas::Event> {
  (void)mouse;
  return {};
}

auto UIHandler::handle_mouse_move(sf::Event::MouseMoveEvent mouse)
    -> std::optional<Canvas::Event> {
  update_mouse_hover(mouse);
  return {};
}

auto UIHandler::handle_mouse_press(sf::Event::MouseButtonEvent mouse)
    -> std::optional<Canvas::Event> {
  auto clicked_window = window_under_mouse(mouse.x, mouse.y);
  surface on = clicked_window.empty() ? canvas
               : (clicked_window & m_selected_windows).empty()
                   ? window
                   : selected_window;
  bool is_ctrl = sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) ||
                 sf::Keyboard::isKeyPressed(sf::Keyboard::RControl);
  return mouse_press_to_actions(is_ctrl, on, clicked_window);
}

auto UIHandler::mouse_press_to_actions(bool is_ctrl, surface on,
                                       WindowSet clicked_window)
    -> std::optional<Canvas::Event> {
  auto last_highlight = m_highlight_window;
  if (is_ctrl) {
    switch (on) {
    case canvas:
      return {};
      break;
    case window:
      m_selected_windows.insert_range(clicked_window);
      m_highlight_window = clicked_window;
      select_window(clicked_window);
      highlight_window(clicked_window, last_highlight);
      return {};
      break;
    case selected_window:
      m_selected_windows -= clicked_window;
      m_highlight_window = clicked_window;
      select_window({}, clicked_window);
      highlight_window({}, last_highlight);
    }
  } else {
    switch (on) {
    case canvas: {
      // two lines just to merge two bit_sets wtf
      WindowSet ret(clicked_window);
      ret.insert_range(m_selected_windows);
      select_window({}, ret);
      highlight_window(WindowSet(), ~WindowSet());
    } break;
    case selected_window:
      break;
    case window:
      auto to_deselect = m_selected_windows - clicked_window;
      m_selected_windows = clicked_window;
      auto last_highlight = m_highlight_window;
      m_highlight_window = clicked_window;
      select_window(clicked_window, to_deselect);
      highlight_window(m_highlight_window, last_highlight);
    }
  }
  __builtin_unreachable();
}

auto UIHandler::update_mouse_hover(sf::Event::MouseMoveEvent mouse) -> void {
  auto hovered_window = window_under_mouse(mouse.x, mouse.y);
  auto last_hovered =
      m_curr_hover == hovered_window ? WindowSet() : m_curr_hover;
  m_curr_hover = hovered_window;
  m_window_manager.apply<WindowManager::decorate>(
      m_curr_hover, decorations::hover, decorations::hover);
  m_window_manager.apply<WindowManager::decorate>(
      last_hovered, decorations::hover, decorations::nothing);
}

auto UIHandler::select_window(WindowSet clicked, WindowSet last) -> void {
  m_window_manager.apply<WindowManager::decorate>(clicked, decorations::select,
                                                  decorations::select);
  m_window_manager.apply<WindowManager::decorate>(last, decorations::select,
                                                  decorations::nothing);
}
auto UIHandler::highlight_window(WindowSet current, WindowSet last) -> void {
  m_window_manager.apply<WindowManager::decorate>(
      current, decorations::highlight, decorations::highlight);
  m_window_manager.apply<WindowManager::decorate>(last, decorations::highlight,
                                                  decorations::nothing);
}
auto UIHandler::window_under_mouse(int x, int y) -> WindowSet {
  return m_window_manager.findWindows([=](auto const &window) {
    return window.contains({x, y});
  });
}
} // namespace Canvas
