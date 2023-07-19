#include "../include/UIManager.hpp"
#include "../include/UserAction.hpp" // Canvas::Event
#include "UImenus.hpp"
#include "consts.hpp"
#include "overloaded.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
namespace Canvas {
UIHandler::UIHandler()
    : title("shit ass piss"), m_render_window(sf::VideoMode(100, 100), title),
      m_block_manager() {}

auto UIHandler::generate_event() -> std::optional<Canvas::Event> {
  sf::Event event;
  if (m_render_window.pollEvent(event)) {
    return hadle_sf_event(event);
  }
  return std::nullopt;
}

auto UIHandler::is_window_open() -> bool { return m_render_window.isOpen(); }

auto UIHandler::handle_sf_event(sf::Event event)
    -> std::optional<Canvas::Event> {
  if (m_ui_mode.index() == 5) {
      m_ui_mode
    }
    
  switch (event.type) {
  case sf::Event::KeyPressed:  //!< A key was pressed (data in event.key)
  case sf::Event::KeyReleased: //!< A key was released (data in event.key)

    return handle_keypress(event.key);

    break;
  case sf::Event::MouseButtonPressed: //!< A mouse button was pressed (data in
                                      //!< event.mouseButton)
    return handle_mouse_press(event.mouseButton);
    break;
  case sf::Event::MouseButtonReleased: //!< A mouse button was released (data in
                                       //!< event.mouseButton)
    return handle_mouse_release(event.mouseButton);
    break;
  case sf::Event::MouseMoved: //!< The mouse cursor moved (data in
                              //!< event.mouseMove)
    return handle_mouse_move(event.mouseMove);
    break;
  default:
    break;
  }
  return {};
}

auto UIHandler::handle_keypress(sf::Event::KeyEvent event)
    -> std::optional<Canvas::Event> {
  // escape should deselct everything
  // delete should delete selected entities
  switch (event.code) {
  case sf::Keyboard::Escape:
    m_render_window.close();
    return Canvas::Event(close_app());
    break;
  case sf::Keyboard::Space:
    TODO(enter main menu);
    return {};
    break;
  default:
    return {};
    break;
  }
}

auto UIHandler::handle_on_satisfy(Canvas::Event const &event)
    -> std::optional<Canvas::Event> {
  auto [new_event, new_ui_mode] =
      std::visit(Overload{[event](auto &menu) -> maybe_event_menu {
                            return menu.handle(event);
                          },
                          [](std::nullopt_t) -> maybe_event_menu {
                            return {};
                          }},
                 m_ui_mode);
  m_ui_mode = new_ui_mode;
  return new_event;
}

auto UIHandler::handle_mouse_release(sf::Event::MouseButtonEvent mouse)
    -> std::optional<Canvas::Event> {
  (void)mouse;
  return {};
}

auto UIHandler::handle_mouse_move(sf::Event::MouseMoveEvent mouse)
    -> std::optional<Canvas::Event> {
  update_mouse_hover(mouse);
  return {};
}

auto UIHandler::handle_mouse_press(sf::Event::MouseButtonEvent mouse)
    -> std::optional<Canvas::Event> {
  auto clicked_block = block_under_mouse(mouse.x, mouse.y);
  surface on = clicked_block.empty() ? canvas
               : (clicked_block & m_selected_blocks).empty()
                   ? block
                   : selected_block;
  bool is_ctrl = sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) ||
                 sf::Keyboard::isKeyPressed(sf::Keyboard::RControl);
  return mouse_press_to_actions(is_ctrl, on, clicked_block);
}

auto UIHandler::mouse_press_to_actions(bool is_ctrl, surface on,
                                       BlockSet clicked_block)
    -> std::optional<Canvas::Event> {
  auto last_highlight = m_highlight_block;
  if (is_ctrl) {
    switch (on) {
    case canvas:
      return {};
      break;
    case block:
      m_selected_blocks.insert_range(clicked_block);
      m_highlight_block = clicked_block;
      select_block(clicked_block);
      highlight_block(clicked_block, last_highlight);
      return {};
      break;
    case selected_block:
      m_selected_blocks -= clicked_block;
      m_highlight_block = clicked_block;
      select_block({}, clicked_block);
      highlight_block({}, last_highlight);
    default:
      break;
    }
  } else {
    switch (on) {
    case canvas: {
      // two lines just to merge two bit_sets wtf
      BlockSet ret(clicked_block);
      ret.insert_range(m_selected_blocks);
      select_block({}, ret);
      highlight_block(BlockSet(), ~BlockSet());
    } break;
    case selected_block:
      break;
    case block: {
      auto to_deselect = m_selected_blocks - clicked_block;
      m_selected_blocks = clicked_block;
      last_highlight = m_highlight_block;
      m_highlight_block = clicked_block;
      select_block(clicked_block, to_deselect);
      highlight_block(m_highlight_block, last_highlight);
    }
    default:
      break;
    }
  }
  __builtin_unreachable();
}

auto UIHandler::update_mouse_hover(sf::Event::MouseMoveEvent mouse) -> void {
  auto hovered_block = block_under_mouse(mouse.x, mouse.y);
  auto last_hovered =
      m_curr_hover == hovered_block ? BlockSet() : m_curr_hover;
  m_curr_hover = hovered_block;
  m_block_manager.apply<CodeBlocksManager::decorate>(
      m_curr_hover, decorations::hover, decorations::hover);
  m_block_manager.apply<CodeBlocksManager::decorate>(
      last_hovered, decorations::hover, decorations::nothing);
}

auto UIHandler::select_block(BlockSet clicked, BlockSet last) -> void {
  m_block_manager.apply<CodeBlocksManager::decorate>(
      clicked, decorations::select, decorations::select);
  m_block_manager.apply<CodeBlocksManager::decorate>(last, decorations::select,
                                                      decorations::nothing);
}
auto UIHandler::highlight_block(BlockSet current, BlockSet last) -> void {
  m_block_manager.apply<CodeBlocksManager::decorate>(
      current, decorations::highlight, decorations::highlight);
  m_block_manager.apply<CodeBlocksManager::decorate>(
      last, decorations::highlight, decorations::nothing);
}
auto UIHandler::block_under_mouse(int x, int y) -> BlockSet {
  return m_block_manager.findBlocks([=](auto const &block_in_question) {
    return block_in_question.contains({x, y});
  });
}
void UIHandler::add_block(std::string_view header, std::string_view source) {
  m_block_manager.newCodeBlock(std::string(header), std::string(source));
}
} // namespace Canvas
