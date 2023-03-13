
#include "../include/Canvas.hpp"
#include "../include/overloaded.hpp"
#include "../include/TextWindow.hpp"
#include "../include/UserAction.hpp"
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

    auto ov = Overload{
        [this](WindowAction action) {handle_window_action(action);},
        [this](AppAction action) { m_render_window.close(); },
    };
    std::visit(ov, command);
  }
}

auto App::handle_window_action(WindowAction action) -> void {
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
      [this](move_windows) {},
  };
  std::visit(ov, action);
}

} // namespace Canvas
