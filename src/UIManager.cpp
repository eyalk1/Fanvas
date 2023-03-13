#include "../include/UIManager.hpp"
#include "../include/UserAction.hpp"

namespace Canvas {
UIHandler::UIHandler(FindWindowsFromWindowManager find_windows)
    : m_find_windows(find_windows), m_selected_windows() {}
auto UIHandler::handle_event(sf::Event event) -> Actions {
  switch (event.type) {
  case sf::Event::KeyPressed:
  case sf::Event::KeyReleased:
    return handle_keypress(event.key);

  case sf::Event::MouseButtonPressed:
    return handle_mouse_press(event.mouseButton);
  case sf::Event::MouseButtonReleased:
    return handle_mouse_release(event.mouseButton);
  case sf::Event::MouseMoved:
    return handle_mouse_move(event.mouseMove);
  default:
    return {};
  }
}

auto UIHandler::handle_keypress(sf::Event::KeyEvent event) -> Actions {
  // escape should deselct everything
  // delete should delete selected entities
  switch (event.code) {
  case sf::Keyboard::Escape:
    return {close_app()};
    break;
  case sf::Keyboard::Space:
    return {add_window{.header = "header!!!",
                       .source = "source!\nblablabla\nyay!\n"}};

    break;
  default:
    return {};
    break;
  }
}
auto UIHandler::handle_mouse_release(sf::Event::MouseButtonEvent mouse)
    -> Actions {
  return Actions();
}

auto UIHandler::handle_mouse_move(sf::Event::MouseMoveEvent mouse) -> Actions {
  auto hovered_window = window_under_mouse(mouse.x, mouse.y);
  auto last_hovered =
      m_curr_hover == hovered_window ? WindowSet() : m_curr_hover;
  m_curr_hover = hovered_window;
  return {hover_window(m_curr_hover, last_hovered)};
}

auto UIHandler::handle_mouse_press(sf::Event::MouseButtonEvent mouse)
    -> Actions {
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
                                    WindowSet clicked_window) -> Actions {
  switch (is_ctrl) {
  case true:
    switch (on) {
    case canvas:
      return {};
    case window: {
      m_selected_windows.insert_range(clicked_window);
      auto last_highlight = m_highlight_window;
      m_highlight_window = clicked_window;
      return {add_select_window(clicked_window),
              set_highlight_window(clicked_window, last_highlight)};
    }
    case selected_window: {
      m_selected_windows -= clicked_window;
      auto last_highlight = m_highlight_window;
      m_highlight_window = clicked_window;
      return {deselect_window(clicked_window),
              set_highlight_window(WindowSet(), last_highlight)};
    }
    }
    break;
  case false:
    switch (on) {
    case canvas: {
      // two lines just to merge two bit_sets wtf
      WindowSet ret(clicked_window);
      ret.insert_range(m_selected_windows);
      return {deselect_window{ret},
              set_highlight_window(WindowSet(), ~WindowSet())};
    }
    case selected_window:
    case window: {
      auto to_deselect = m_selected_windows - clicked_window;
      m_selected_windows = clicked_window;
      auto last_highlight = m_highlight_window;
      m_highlight_window = clicked_window;
      return {set_select_window(clicked_window, to_deselect),
              set_highlight_window(m_highlight_window, last_highlight)};
    }
    }
  }
  __builtin_unreachable();
}

auto UIHandler::window_under_mouse(int x, int y) -> WindowSet {
  // we assume that the event is  return
  return m_find_windows([=](auto const &window) {
    return window.contains({x, y});
  });
}
} // namespace Canvas
