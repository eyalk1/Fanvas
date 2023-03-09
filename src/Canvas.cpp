
#include "../include/Canvas.hpp"
#include "../include/overloaded.hpp"
#include "TextWindow.hpp"
#include "UserAction.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>
#include <utility>

namespace Canvas {

App::App(sf::VideoMode rw)
    : m_render_window(rw, "Canvas"), m_window_manager(),
      m_ui(m_window_manager) {
  m_render_window.setFramerateLimit(60);
}

auto App::handle_event(sf::Event event) -> void {
  Actions cmd = m_ui.handle_event(event);
  for (auto const &maybe_command : cmd) {
    if (!maybe_command.has_value())
      break;
    auto &command = *maybe_command;

    if (std::holds_alternative<close_app>(command)) {
      m_render_window.close();
      return;
    }

    auto ov = Overload{
        [this](hover_window hv) {
          m_window_manager.apply<WindowManager::decorate>(
              hv.set, decorations::hover, decorations::hover);
          m_window_manager.apply<WindowManager::decorate>(
              hv.unset, decorations::hover, decorations::nothing);
        },
        [this](deselect_window rm) {
          m_window_manager.apply<WindowManager::decorate>(
              rm.unset, decorations::select, decorations::nothing);
        },
        [this](add_select_window add) {
          m_window_manager.apply<WindowManager::decorate>(
              add.set, decorations::select, decorations::select);
        },
        [this](set_select_window set) {
          m_window_manager.apply<WindowManager::decorate>(
              set.set, decorations::select, decorations::select);
          m_window_manager.apply<WindowManager::decorate>(
              set.unset, decorations::select, decorations::nothing);
        },
        [this](set_highlight_window window) {
          m_window_manager.apply<WindowManager::decorate>(
              window.set, decorations::highlight, decorations::highlight);
          m_window_manager.apply<WindowManager::decorate>(
              window.unset, decorations::highlight, decorations::nothing);
        },
        [this](add_window window) {
          m_window_manager.newTextWindow(std::string(window.header),
                                         std::string(window.source));
        },
        [this](start_selection_rect) {},
        [this](move_selection_rect) {},
        [this](move_windows) {},
        [this](close_app) { __builtin_unreachable(); },
        [](nothing_action) {}};
    std::visit(ov, command);
  }
}

// auto App::handle_mouserelease(sf::Event mouserelease) -> void {
//   // release after gathered with ctrl -> should leave selections
//   // release after moving/single clicks on window -> deselect window
//   // release after single click on background -> should deselect everything
//   // if after release there are intersections - move to the initial position
//   if (mouserelease.mouseButton.button == sf::Mouse::Button::Left) {
//     window_id.clear();
//   }
// }

// auto App::handle_mousemove(sf::Event mousemoved) -> void {
//   // move when pressed on one of selection -> move selection
//   // move when initialized an area to select -> resize area and de/select
//   // windows as they come in and out move when middle pressed -> move the
//   view auto new_mouse = sf::Mouse::getPosition(m_render_window); if
//   (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) == true &&
//       !window_id.empty()) {
//     m_window_manager.move(
//         window_id, sf::Vector2f(new_mouse - GetSettings().GetMousePos()));
//   }
//   SetSettings().SetMousePos() = new_mouse;
// }

// auto App::handle_mousepress(sf::Event mousepressed) -> void {
//   // press when on window -> select window and save position
//   // press when on window with ctrl -> add window to selection and save
//   position
//   // press on canvas -> deselect windows save position
//   // press middle -> save position
//   // double click should center the ziew on the click
//   if (mousepressed.mouseButton.button == sf::Mouse::Button::Left) {
//     auto window_under_mouse = m_window_manager.findWindows(
//         [mouse_pos = sf::Mouse::getPosition(m_render_window)](
//             auto const &window) { return window.contains(mouse_pos); });
//     // if we click on a window that is already selected than we make it the
//     only
//     // selected window even if we selected a lot with ctrl
//     if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
//       window_id |= window_under_mouse;
//       // m_window_manager.select(window_under_mouse);
//       SetSettings().SetMousePos() = {mousepressed.mouseButton.x,
//       mousepressed.mouseButton.y};
//     } else if (WindowManager::WindowSet other_windows =
//                    window_id - window_under_mouse;
//                !other_windows.empty()) {
//       //
//       m_window_manager.deselect(m_window_manager.findWindows(other_windows));

//       window_id = window_under_mouse;
//       // m_window_manager.select(window_under_mouse);
//       SetSettings().SetMousePos() = {mousepressed.mouseButton.x,
//       mousepressed.mouseButton.y};
//     }
//   } else if (mousepressed.mouseButton.button == sf::Mouse::Button::Middle) {

//   } else if (mousepressed.mouseButton.button == sf::Mouse::Button::Left) {
//   }
// }

} // namespace Canvas
