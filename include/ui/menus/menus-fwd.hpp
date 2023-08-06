#pragma once
#include "UserAction.hpp"
#include <optional>
#include <string_view>
#include <variant>
namespace Canvas {

struct MainMenu;
struct DirectoriesMenu;
struct SettingsMenu;
struct FindMenu;
struct WorkspaceMenu;

using Menus = std::variant<MainMenu, DirectoriesMenu, SettingsMenu, FindMenu,
                           WorkspaceMenu>;
using MenusHandler = std::optional<Menus>;
using maybe_event_menu = std::pair<std::optional<Canvas::Event>, Menus>;

} // namespace Canvas
