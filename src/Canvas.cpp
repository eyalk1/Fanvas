
#include "../include/Canvas.hpp"
#include "../include/TextWindow.hpp"
#include "../include/UIAction.hpp"
#include "../include/UserAction.hpp"
#include "../include/overloaded.hpp"
#include "consts.hpp"
#include "setting.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>
#include <utility>

namespace Canvas {

EventDistributer::EventDistributer() {}

auto EventDistributer::run() -> void {
  while (m_ui.is_window_open()) {
    // for each member that can generate an event - generate and add the event
    // to the queue
    add_event(m_ui.generate_event());
    // empty the queue syncronicly - if things take time put a timer here and
    // let it run in the background or something - in the future
    while (!m_event_queue.empty()) {
      auto event = m_event_queue.front();
      handle_event(event);
      m_event_queue.pop();
    }
  }
}

auto EventDistributer::add_event(std::optional<Canvas::Event> &&event) -> bool {
  return event ? m_event_queue.emplace(*event) : false;
}

auto EventDistributer::handle_event(Canvas::Event const &event) -> void {
  // for event handler check if event is good.
  // for (auto const &eventer : m_eventers) {
  //   eventer.handle_on_satisfy(event);
  // }
  // if there is a hint we will use it to short circuit the search for a
  // handler
  if (event.recipient_hint != Entities::NO_ONE) {
    handle_hint(event);
  } else {
    m_ui.handle_on_satisfy(event);
    // m_lsp.handle_on_satisfy(event);
  }
}

void EventDistributer::handle_hint(Canvas::Event const &event) {
  for (size_t i = 0; i < Entities::APP; i++) {
    switch (event.recipient_hint & i) {
    case Entities::UI:
      m_ui.handle_event(event);
      break;
    case Entities::LSP:
      PASS;
      break;
    case Entities::APP:
      PASS;
      // m_common_handler.handle_event(event);
      break;
    case Entities::NO_ONE:
      PASS;
    }
  }
}
// auto EventDistributer::handle_app_action(AppAction action) -> void {
//   auto ov = Overload{[this](close_app action) {
//                        (void)action;
//                        this->m_render_window.close();
//                      },
//                      [this](open_repo action) { this->open_dir(action.path);
//                      },
//     [this](findFunction action){

//       }};
//   std::visit(ov, action);
// }

} // namespace Canvas
