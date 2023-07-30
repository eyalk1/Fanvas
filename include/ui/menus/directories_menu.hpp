#pragma once
#include "ui/menus/menus-fwd.hpp"
namespace Canvas {

// v-split: left is list of open directories, right is a directory picker
// directory picker:
// mode 1: just a text box with completions
// mode 2: ranger style w/ arrows
// newMenuWindow(vsplit(getDirList(), searchBox()))
struct directories_menu {
  maybe_event_menu handle(Canvas::Event e);
};

} // namespace Canvas
