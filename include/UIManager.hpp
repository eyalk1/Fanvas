#ifndef UIHANDLER__HPP
#define UIHANDLER__HPP
#include "UserAction.hpp"
#include "ui/canvas.hpp"
#include "ui/menus/menus.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <iterator>
#include <string>
#include <string_view>

namespace Canvas {

struct UIHandler {
  [[nodiscard]] auto is_window_open() -> bool;
  // this function checks internal state to see if there is an event that the UI
  // produces e.g. user requested to add a directory for pulling functions from
  // if we handle the event here when we return it
  //(others might want to react as well)
  // we need to make sure that we don't react again.
  // since the event handling is hierarchial the way we would note the
  // unreacting component has to be hierarchial as well.
  // thus implementing is too complicated and hence it is not implemented.
  // we react only through the handle API.
  auto generate_event(std::output_iterator<Canvas::Event> auto to_push) -> void;
  // check if the event is handelable by the uihandler if so - handle
  auto handle_on_satisfy(std::input_iterator auto event_begin,
                         std::input_iterator auto event_end,
                         std::output_iterator<Canvas::Event> auto to_push)
      -> void;
  UIHandler();

private:
  // through this function we handle events from the outside
  auto handle_event(Canvas::Event const &event) -> void;

  // process generic sf event - turning it into a canvas event
  auto sf_event2canvas_event(sf::Event event,
                             std::output_iterator<Canvas::Event> auto to_push)
      -> void;

  std::string title;
  sf::RenderWindow m_render_window;

  // possible menus and screens are: search for function and/or add function,
  // manage directories - add/remove, settings(e.g. try to hijack lsp or diy?
  // colors?), choose workspace, canvas, menu picker
  MenusHandler m_ui_mode;
  CanvasManager m_canvas;
};
} // namespace Canvas

// implementations
namespace Canvas {
auto UIHandler::generate_event(std::output_iterator<Canvas::Event> auto to_push)
    -> void {
  sf::Event event;
  if (!m_render_window.pollEvent(event)) {
    return;
  }
  sf_event2canvas_event(event, to_push);
}
auto UIHandler::handle_on_satisfy(
    std::input_iterator auto event_begin, std::input_iterator auto event_end,
    std::output_iterator<Canvas::Event> auto to_push) -> void {
  for (; event_begin != event_end; event_begin++) {
    auto &event = *event_begin;
    m_ui_mode
        ? std::visit([&event, &to_push](
                         auto &menu) { return menu.handle(event, to_push); },
                     *m_ui_mode)
        : m_canvas.handle(event, to_push);
  }
}

auto UIHandler::sf_event2canvas_event(
    sf::Event event, std::output_iterator<Canvas::Event> auto to_push) -> void {
  /* we merge the state of the ui handler and the event and output a canvas
   * event.
   * This function does not dispatch! reasons:
    1. only one function does dispatching
    2. dispatch only upon Canvas::Event
    3. send an event to other entities (e.g. when opening a menu - get lsp
       status or any 3rd party info) - potentially asycn
   */

  /**
   * click/keypress on menu - menu event
   * click/keypress on canvas - window event
   *
   **/
  // std::optional<Canvas::Event> e =
  return m_ui_mode ? std::visit(
                         [to_push, event](auto &menu) {
                           return menu.sf_event2canvas_event(event, to_push);
                         },
                         *m_ui_mode)
                   : m_canvas.sf_event2canvas_event(event, to_push);
}
} // namespace Canvas
#endif // UIHANDLER__HPP
