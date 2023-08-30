#include "Canvas.hpp"
#include "UserAction.hpp"
#include "common/consts.hpp"
#include "common/setting.hpp"
#include "ui/code-blocks/CodeBlock.hpp"
#include "utils/overloaded.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>
#include <iterator>
#include <utility>

namespace Canvas {

auto EventDistributer::run() -> void {
  std::vector<Canvas::Event> event_queue1, event_queue2;
    // TODO: use GSL not_null
  auto *write_events = &event_queue1;
  auto *read_events = &event_queue2;
  // main loop
  while (m_ui.is_window_open()) {
    // for each member that can generate an event - generate and add the event
    // to the queue.
    // Giving the generators an iterator through which they will
    // insert is sortof a DIY RVO - we know that the returned value will be
    // place into the queue.
    auto back = std::back_inserter(*write_events);
    m_ui.generate_event(back);
    TODO(add_event(m_lsp.generate_event()));
    // empty the queue syncronicly - if things take time put a timer here and
    // let it run in the background or something - in the future
    if (!read_events->empty()) {
      handle_event(read_events->cbegin(), read_events->cend(), back);
    }
    read_events->clear();
    std::swap(write_events, read_events);
  }
}

auto EventDistributer::handle_event(
    std::input_iterator auto event_begin, std::input_iterator auto event_end,
    std::back_insert_iterator<std::vector<Canvas::Event>> back) -> void {
  m_ui.handle_on_satisfy(event_begin, event_end, back);
  TODO(add_event(m_lsp.handle_on_satisfy(event)));
}

} // namespace Canvas
