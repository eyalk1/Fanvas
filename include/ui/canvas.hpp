#pragma once
#include "UserAction.hpp"
#include "code-blocks/CodeBlockManager.hpp"
#include <SFML/Window/Event.hpp>

namespace Canvas {

struct CanvasManager {
  auto sf_event2canvas_event(sf::Event const &event,
                             std::output_iterator<Canvas::Event> auto to_push)
      -> void;

  auto handle(Canvas::Event const &e,
              std::output_iterator<Canvas::Event> auto to_push) -> void;

  // take specific sf event and 1: return events for the external world, 2:
  // handle internal affects. this could be only no.1 but sending an event that
  // you know you're gonna handle is stupid
  enum surface { canvas, block, selected_block };
  auto handle_keypress(sf::Event::KeyEvent event,
                       std::output_iterator<Canvas::Event> auto to_push)
      -> void;
  auto handle_mouse_press(sf::Event::MouseButtonEvent mouse,
                          std::output_iterator<Canvas::Event> auto to_push)
      -> void;
  auto handle_mouse_release(sf::Event::MouseButtonEvent mouse,
                            std::output_iterator<Canvas::Event> auto to_push)
      -> void;
  auto handle_mouse_move(sf::Event::MouseMoveEvent mouse,
                         std::output_iterator<Canvas::Event> auto to_push)
      -> void;
  auto mouse_press_to_actions(bool is_ctrl, surface on, BlockSet clicked_block,
                              std::output_iterator<Canvas::Event> auto to_push)
      -> void;

  // handle actual dispatching of the internal events
  auto update_mouse_hover(sf::Event::MouseMoveEvent mouse,
                          std::output_iterator<Canvas::Event> auto to_push)
      -> void;
  auto add_block(std::string_view header, std::string_view source) -> void;
  auto
  decorate_block(optarray<std::tuple<decorations, BlockSet, BlockSet>, 3> decs,
                 std::output_iterator<Canvas::Event> auto to_push) -> void;
  // auto select_block(std::output_iterator<Canvas::Event> auto to_push,
  //                   BlockSet clicked, BlockSet last = {}) -> void;
  // auto highlight_block(std::output_iterator<Canvas::Event> auto to_push,
  //                      BlockSet clicked, BlockSet last = {}) -> void;
  // auto hover_block(std::output_iterator<Canvas::Event> auto to_push,
  //                  BlockSet last_hovered) -> void;
  // utilities
  [[nodiscard]] auto block_under_mouse(int x, int y) -> BlockSet;

  CodeBlocksManager m_block_manager;
  BlockSet m_curr_hover;
  BlockSet m_selected_blocks;
  BlockSet m_highlight_block;
};
} // namespace Canvas
// implementations
#include "common/consts.hpp"
#include "ui/code-blocks/CodeBlock.hpp"
#include "utils/utility.hpp"

#include <iterator>

namespace Canvas {
using decoration = std::tuple<decorations, BlockSet, BlockSet>;
using decoration_set = optarray<decoration, 3>;
auto CanvasManager::sf_event2canvas_event(
    sf::Event const &event, std::output_iterator<Canvas::Event> auto to_push)
    -> void {
  switch (event.type) {
  case sf::Event::KeyPressed:  //!< A key was pressed (data in event.key)
  case sf::Event::KeyReleased: //!< A key was released (data in event.key)
    handle_keypress(event.key, to_push);
    break;
  case sf::Event::MouseButtonPressed: //!< A mouse button was pressed (data in
                                      //!< event.mouseButton)
    return handle_mouse_press(event.mouseButton, to_push);
    break;
  case sf::Event::MouseButtonReleased: //!< A mouse button was released (data in
                                       //!< event.mouseButton)
    return handle_mouse_release(event.mouseButton, to_push);
    break;
  case sf::Event::MouseMoved: //!< The mouse cursor moved (data in
                              //!< event.mouseMove)
    return handle_mouse_move(event.mouseMove, to_push);
    break;
  default:
    break;
  }
}
auto CanvasManager::handle(Canvas::Event const &e,
                           std::output_iterator<Canvas::Event> auto to_push)
    -> void {
  (void)e;
  (void)to_push;
}
auto CanvasManager::handle_keypress(
    sf::Event::KeyEvent event, std::output_iterator<Canvas::Event> auto to_push)
    -> void {
  // escape should deselct everything
  // delete should delete selected entities
  switch (event.code) {
  case sf::Keyboard::Escape:
    to_push = Canvas::Event(close_app());
    break;
  case sf::Keyboard::Space:
    TODO(enter main menu);
    break;
  default:
    break;
  }
}
auto CanvasManager::handle_mouse_release(
    sf::Event::MouseButtonEvent mouse,
    std::output_iterator<Canvas::Event> auto to_push) -> void {
  (void)mouse;
  (void)to_push;
}

auto CanvasManager::handle_mouse_move(
    sf::Event::MouseMoveEvent mouse,
    std::output_iterator<Canvas::Event> auto to_push) -> void {
  update_mouse_hover(mouse, to_push);
}

auto CanvasManager::handle_mouse_press(
    sf::Event::MouseButtonEvent mouse,
    std::output_iterator<Canvas::Event> auto to_push) -> void {
  auto clicked_block = block_under_mouse(mouse.x, mouse.y);
  surface on = clicked_block.empty()                         ? canvas
               : (clicked_block & m_selected_blocks).empty() ? block
                                                             : selected_block;
  bool is_ctrl = sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) ||
                 sf::Keyboard::isKeyPressed(sf::Keyboard::RControl);
  mouse_press_to_actions(is_ctrl, on, clicked_block, to_push);
}

auto CanvasManager::mouse_press_to_actions(
    bool is_ctrl, surface on, BlockSet clicked_block,
    std::output_iterator<Canvas::Event> auto to_push) -> void {
  auto last_highlight = m_highlight_block;
  if (is_ctrl) {
    switch (on) {
    case canvas:
      break;
    case block:
      m_selected_blocks.insert_range(clicked_block);
      m_highlight_block = clicked_block;
      decorate_block(
          decoration_set{decoration{decorations::select, clicked_block, {}},
                         decoration{decorations::highlight, clicked_block,
                                    last_highlight}},
          to_push);
      break;
    case selected_block:
      m_selected_blocks -= clicked_block;
      m_highlight_block = clicked_block;
      decorate_block(
          decoration_set{
              decoration{decorations::select, {}, clicked_block},
              decoration{decorations::highlight, {}, last_highlight}},
          to_push);
    default:
      break;
    }
  } else {
    switch (on) {
    case canvas: {
      // two lines just to merge two bit_sets wtf
      BlockSet ret(clicked_block);
      ret.insert_range(m_selected_blocks);
      decorate_block(decoration_set{decoration{decorations::select, {}, ret},
                                    decoration{decorations::highlight,
                                               BlockSet(), ~BlockSet()}},
                     to_push);
    } break;
    case selected_block:
      break;
    case block: {
      auto to_deselect = m_selected_blocks - clicked_block;
      m_selected_blocks = clicked_block;
      last_highlight = m_highlight_block;
      m_highlight_block = clicked_block;
      decorate_block(
          decoration_set{
              decoration{decorations::select, clicked_block, to_deselect},
              decoration{decorations::highlight, m_highlight_block,
                         last_highlight}},
          to_push);
    }
    default:
      break;
    }
  }
  __builtin_unreachable();
}

auto CanvasManager::update_mouse_hover(
    sf::Event::MouseMoveEvent mouse,
    std::output_iterator<Canvas::Event> auto to_push) -> void {
  auto hovered_block = block_under_mouse(mouse.x, mouse.y);
  auto last_hovered = m_curr_hover == hovered_block ? BlockSet() : m_curr_hover;
  m_curr_hover = hovered_block;
  decorate_block(decoration_set{decoration{decorations::hover, m_curr_hover,
                                           last_hovered}},
                 to_push);
}
auto CanvasManager::decorate_block(
    decoration_set decs, std::output_iterator<Canvas::Event> auto to_push)
    -> void {
  DecorationCmd cmd{};
  for_each_optional(decs, [&cmd](auto const &dec) {
    switch (std::get<0>(dec)) {
    case decorations::hover:
      cmd.hover = std::get<1>(dec);
      cmd.dehover = std::get<2>(dec);
      break;
    case decorations::highlight:
      cmd.highlight = std::get<1>(dec);
      cmd.dehighlight = std::get<2>(dec);
      break;
    case decorations::select:
      cmd.select = std::get<1>(dec);
      cmd.deselect = std::get<2>(dec);
      break;
    default:
      break;
    }
  });
  to_push = cmd;
}

} // namespace Canvas
