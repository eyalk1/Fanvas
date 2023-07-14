#pragma once
// #include "CommonHandler.hpp"
#include "UIManager.hpp"
#include "consts.hpp"
#include "event_generator.hpp"
namespace CircularQ {
#include "../include/circularQueue.hpp"
}
#include <optional>

namespace Canvas {
// not sure what does this do - maybe will get deleted
class EventDistributer {
public:
  EventDistributer();
  auto run() -> void;
  auto add_event(std::optional<Canvas::Event>&& event) -> bool;
  auto handle_event(Canvas::Event const &) -> void;

private:
  void handle_hint(Canvas::Event const &);
  // std::array<event_generator, 1> eventers;
  UIHandler m_ui;
  CircularQ::circularQueue<Canvas::Event, MAX_NUMBER_OF_EVENTS> m_event_queue;
};
} // namespace Canvas
