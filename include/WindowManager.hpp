#pragma once
#include "TextWindow.hpp"
#include "utility.hpp"
#include "consts.hpp"
#include "bit_set.hpp"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>
#include <array>
#include <chrono>
#include <functional>
#include <optional>
#include <stack>

namespace Canvas {
//TODO: make template taking amount of windows?
class WindowManager : public sf::Drawable {
private:
  using maybe_window = std::optional<TextWindow>;
  std::array<maybe_window, MAX_NUMBER_OF_WINDOWS> m_windows;

public:
  enum actions : size_t { decorate, move, action_amount };
  // draw all the windows managed by the manager
  auto draw(sf::RenderTarget &target, sf::RenderStates states) const
      -> void override;

  // forward the parameters to a new allocated window object
  auto newTextWindow(sf::String &&header, sf::String &&source)
      -> TextWindow const &;
  // give a predicate return all the windows that satisfy it
  auto findWindows(auto p) const -> WindowSet;
  // apply an action to all the windows in the set
  template <WindowManager::actions TO_DO, typename... Args>
  auto apply(WindowSet windows, Args &&...args) -> void;
  auto deleteTextWindow(WindowSet windows) -> void;

  auto get_all_windows() -> WindowSet;
private:
  auto findOpenspace(sf::Vector2f rec_size, WindowSet available_windows)
      -> sf::Vector2f;
};

// this function maps the actions enum to the actual textwindow API - this way
// we don't:
// 1. double the window API for forwarding
// 2. bleed details about the window objects themselves - having the user
//    provide a member-function-pointer
template <WindowManager::actions Actions> consteval auto action2function();

// IMPLEMENTATIONS

auto WindowManager::findWindows(auto predicate) const
    -> WindowSet {
  int i = 0;
  WindowSet ret;
  for (auto const &window : m_windows) {
    if (window && predicate(window.value()))
      ret.add(i);
    i++;
  }
  return ret;
}

template <WindowManager::actions TO_DO, typename... Args>
auto WindowManager::apply(WindowSet windows, Args &&...args) -> void {
  for_indexes(windows, m_windows, action2function<TO_DO>(),
              std::forward<Args>(args)...);
}

template <WindowManager::actions Actions>
consteval auto action2function() {
  if constexpr (Actions == WindowManager::actions::decorate) {
    return &TextWindow::decorate;
  } else if constexpr (Actions == WindowManager::actions::move) {
    return &TextWindow::move;
  }
}

} // namespace Canvas
