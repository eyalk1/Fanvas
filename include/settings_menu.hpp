#pragma once
#include "UImenus.hpp"
namespace Canvas {

  // list of settings with their values
  // whenyou click a settings you can modify the value
  struct settings_menu {
    maybe_event_menu handle(Canvas::Event e);
  };
}
