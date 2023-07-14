#ifndef USER_ACTIONS__HPP
#define USER_ACTIONS__HPP
#include "bit_set.hpp"
#include "consts.hpp"
#include <SFML/System/Vector2.hpp>
#include <string_view>
#include <variant>
namespace Canvas {

// ~~~~~~~~~~~~~~~~~~window commands~~~~~~~~~~~~~~~~~~~~~~~~~~~
// TODO: moveto only variant without inheritence
struct window_command {
  // MUST BE EMPTY SO WE WON'T USE VIRTUAL INHERITANCE!!
};
struct window_apply_command : public window_command {
  window_apply_command(WindowSet set) : set(set) {}
  WindowSet set;
};
struct window_unapply_command : public window_command {
  window_unapply_command(WindowSet unset) : unset(unset) {}
  WindowSet unset;
};
struct window_set_command : public window_apply_command,
                            public window_unapply_command {
  window_set_command(WindowSet set, WindowSet unset)
      : window_apply_command(set), window_unapply_command(unset) {}
  using window_apply_command::set;
  using window_unapply_command::unset;
};
// concrete window commands
struct hover_window : public window_set_command {
  hover_window(WindowSet set, WindowSet unset)
      : window_set_command(set, unset) {}
};
struct add_select_window : public window_apply_command {
  add_select_window(WindowSet set) : window_apply_command(set) {}
};
struct deselect_window : public window_unapply_command {
  deselect_window(WindowSet unset) : window_unapply_command(unset) {}
};
struct set_select_window : public window_set_command {
  set_select_window(WindowSet set, WindowSet unset)
      : window_set_command(set, unset) {}
};
struct set_highlight_window : public window_set_command {
  set_highlight_window(WindowSet set, WindowSet unset)
      : window_set_command(set, unset) {}
};
struct add_window : public window_command {
  std::string_view header, source;
};
struct move_windows : public window_apply_command {
  move_windows(WindowSet set) : window_apply_command(set) {}
  sf::Vector2f diff;
};
using WindowAction =
    std::variant<hover_window, add_select_window, deselect_window,
                 set_select_window, set_highlight_window, add_window,
                 move_windows>;

//~~~~~~~~~~~~~~~~~App commands~~~~~~~~~~~~~~~~~~~~~

struct close_app {};

struct open_repo {
  open_repo(std::string_view path_to_repo) : path(path_to_repo) {}
  std::string_view path;
};

using AppAction = std::variant<close_app, open_repo>;

//~~~~~~~~~~~~~~~User Commands~~~~~~~~~~~~~~~~~~~
struct Event {
  using data_t = std::variant<WindowAction, AppAction>;
  operator data_t&() { return data; }
  Entities recipient_hint;
  Event(data_t data, Entities hint = Entities::NO_ONE)
      : recipient_hint(hint), data(data){};

private:
  std::variant<WindowAction, AppAction> data;
};

using AppCmd = std::array<std::optional<Canvas::Event>,
                          MAX_NUMBER_OF_APP_ACTIONS_PER_UI_EVENT>;

} // namespace Canvas
#endif //
