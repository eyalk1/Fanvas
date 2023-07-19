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
                           find_menu, workspace_menu, std::monostate>;
using maybe_event_menu = std::pair<std::optional<Canvas::Event>, Menus>;

} // namespace Canvas
