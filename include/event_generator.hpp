#pragma once
#include "UserAction.hpp"
#include <optional>
namespace Canvas {

// template <typename derived> class event_generator {
// public:
//   auto generate_event() -> std::optional<Canvas::Event> {
//     derived &self = static_cast<derived&>(*this);
//     return self.generate_event_impl();
//   }
//   auto handle_on_satisfy(Canvas::Event const &event) -> void {
//     derived &self = static_cast<derived&>(*this);
//     self.handle_on_satisfy_impl(event);
//   }
// };

} // namespace Canvas
