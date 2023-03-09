#ifndef USER_ACTIONS__HPP
#define USER_ACTIONS__HPP
#include "bit_set.hpp"
#include "consts.hpp"
#include <SFML/System/Vector2.hpp>
#include <string_view>
#include <variant>
namespace Canvas {

//TODO change o generic window command - add/set/remove + hover/select/highlight maybe add move too
struct hover_window {
  WindowSet set, unset;
};
struct add_select_window {
  WindowSet set;
};
struct deselect_window {
  WindowSet unset;
};
struct set_select_window {
  WindowSet set, unset;
};
struct set_highlight_window {
  WindowSet set, unset;
};
struct add_window {
  std::string_view header, source;
};
struct start_selection_rect {};
struct move_selection_rect {};
struct move_windows {
  WindowSet to_move;
  sf::Vector2f diff;
};
struct close_app {};
struct nothing_action {};

using UserAction = 
    std::variant<hover_window, deselect_window, add_select_window,
                 set_select_window, set_highlight_window, add_window, start_selection_rect,
                 move_selection_rect, move_windows, close_app, nothing_action>;

} // namespace Canvas
#endif //
