#include "UIManager.hpp"
#include "../include/UserAction.hpp" // Canvas::Event
#include "../include/common/consts.hpp"
#include "../include/utils/overloaded.hpp"
#include "ui/menus/menus-fwd.hpp"
#include "ui/menus/workspace_menu.hpp"
#include "utils/utility.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iterator>
#include <variant>

namespace Canvas {
UIHandler::UIHandler()
    : title("some title"), m_render_window(sf::VideoMode(100, 100), title) {}

auto UIHandler::is_window_open() -> bool { return m_render_window.isOpen(); }

} // namespace Canvas
