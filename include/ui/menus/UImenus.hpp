#pragma once
#include "UserAction.hpp"
#include <optional>
#include <string_view>
#include <variant>
namespace Canvas {

struct main_menu;
struct directories_menu;
struct settings_menu;
struct find_menu;
struct workspace_menu;

using Menus = std::variant<main_menu, directories_menu, settings_menu,
                           find_menu, workspace_menu, std::nullopt_t>;
using maybe_event_menu = std::pair<std::optional<Canvas::Event>, Menus>;

struct main_menu {
  constexpr static std::string_view text =
      "d: manage directories\ns: settings\nq: quit and save\nw: open "
      "workspace\nf: find functions";
  // TODO use temporary reference
  // (non-copyable/non-moveable wrapper)
  main_menu(){};
  maybe_event_menu handle(Canvas::Event e);
};

// v-split: left is list of open directories, right is a directory picker
// directory picker:
// mode 1: just a text box with completions
// mode 2: ranger style w/ arrows
// newMenuWindow(vsplit(getDirList(), searchBox()))
struct directories_menu {
  maybe_event_menu handle(Canvas::Event e);
};

// list of settings with their values
// whenyou click a settings you can modify the value
struct settings_menu {
  maybe_event_menu handle(Canvas::Event e);
};

// on top is text box, on bottom is results
struct find_menu {
  maybe_event_menu handle(Canvas::Event e);
};

struct workspace_menu {
  maybe_event_menu handle(Canvas::Event e);
};

} // namespace Canvas
