#pragma once
#include "UIManager.hpp"
#include "common/consts.hpp"
namespace std {
template <typename T> class optional;
}

namespace Canvas {
// not sure what does this do - maybe will get deleted
class EventDistributer {
public:
  auto run() -> void;
  auto add_event(std::optional<Canvas::Event> &&event) -> void;
  auto handle_event(std::input_iterator auto event_begin,
                    std::input_iterator auto event_end,
                    std::back_insert_iterator<std::vector<Canvas::Event>> back)
      -> void;

private:
  auto handle_hint(Canvas::Event const &) -> void;
  UIHandler m_ui{};
};
} // namespace Canvas
