#ifndef UIHANDLER__HPP
#define UIHANDLER__HPP
#include "UserAction.hpp"
#include "common/consts.hpp"
#include "ui/code-blocks/CodeBlockManager.hpp"
#include "ui/menus/menus.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <string>
#include <string_view>

namespace Canvas {

struct UIHandler {
  auto is_window_open() -> bool;
  // this function checks internal state to see if there is an event that the UI
  // produces e.g. user requested to add a directory for pulling functions from
  auto generate_event() -> std::optional<Canvas::Event>;
  // check if the event is handelable by the uihandler if so - handle
  auto handle_on_satisfy(Canvas::Event const &event)
      -> std::optional<Canvas::Event>;
  UIHandler();

private:
  enum surface { canvas, block, selected_block };
  // through this function we handle events from the outside
  auto handle_event(Canvas::Event const &event) -> void;

  // process generic sf event - turning it into a canvas event
  auto handle_sf_event(sf::Event event) -> std::optional<Canvas::Event>;

  // take specific sf event and 1: return events for the external world, 2:
  // handle internal affects. this could be only no.1 but sending an event that
  // you know you're gonna handle is stupid
  auto handle_keypress(sf::Event::KeyEvent event)
      -> std::optional<Canvas::Event>;
  auto handle_mouse_press(sf::Event::MouseButtonEvent mouse)
      -> std::optional<Canvas::Event>;
  auto handle_mouse_release(sf::Event::MouseButtonEvent mouse)
      -> std::optional<Canvas::Event>;
  auto handle_mouse_move(sf::Event::MouseMoveEvent mouse)
      -> std::optional<Canvas::Event>;
  auto mouse_press_to_actions(bool is_ctrl, surface on, BlockSet clicked_block)
      -> std::optional<Canvas::Event>;

  // handle actual dispatching of the internal events
  auto update_mouse_hover(sf::Event::MouseMoveEvent mouse) -> void;
  void add_block(std::string_view header, std::string_view source);
  auto select_block(BlockSet clicked, BlockSet last = {}) -> void;
  auto highlight_block(BlockSet clicked, BlockSet last = {}) -> void;
  std::string title;
  sf::RenderWindow m_render_window;

  // possible menus and screens are: search for function and/or add function,
  // manage directories - add/remove, settings(e.g. try to hijack lsp or diy?
  // colors?), choose workspace, canvas, menu picker
  Menus m_ui_mode;

  CodeBlocksManager m_block_manager;
  BlockSet m_curr_hover;
  BlockSet m_selected_blocks;
  BlockSet m_highlight_block;
  // utilities
  auto block_under_mouse(int x, int y) -> BlockSet;
};
} // namespace Canvas
#endif // UIHANDLER__HPP
