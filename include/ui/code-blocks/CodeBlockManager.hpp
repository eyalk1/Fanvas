#pragma once
#include "bit_set/bit_set.hpp"
#include "common/consts.hpp"
#include "ui/code-blocks/CodeBlock.hpp"
#include "utils/utility.hpp"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>
#include <array>
#include <chrono>
#include <functional>
#include <optional>
#include <stack>

namespace Canvas {
class CodeBlocksManager : public sf::Drawable {
private:
  using maybe_window = std::optional<CodeBlock>;
  std::array<maybe_window, MAX_NUMBER_OF_WINDOWS> m_windows;

public:
  enum actions : size_t { decorate, move, number_of_possible_actions };
  // draw all the windows managed by the manager
  auto draw(sf::RenderTarget &target, sf::RenderStates states) const
      -> void override;

  // forward the parameters to a new allocated window object
  auto newCodeBlock(sf::String &&header, sf::String &&source)
      -> CodeBlock const &;
  // give a predicate return all the windows that satisfy it
  [[nodiscard]] auto findBlocks(auto p) const -> BlockSet;
  // apply an action to all the windows in the set
  template <CodeBlocksManager::actions TO_DO, typename... Args>
  auto apply(BlockSet windows, Args &&...args) -> void;
  auto deleteCodeBlock(BlockSet windows) -> void;

  [[nodiscard]] auto get_all_windows() -> BlockSet;

private:
  [[nodiscard]] auto findOpenspace(sf::Vector2f rec_size, BlockSet available_windows)
      -> sf::Vector2f;
};

// this function maps the actions enum to the actual textwindow API - this way
// we don't:
// 1. double the window API for forwarding
// 2. bleed details about the window objects themselves - having the user
//    provide a member-function-pointer
template <CodeBlocksManager::actions Actions> consteval auto action2function();

// IMPLEMENTATIONS

auto CodeBlocksManager::findBlocks(auto predicate) const -> BlockSet {
  int i = 0;
  BlockSet ret;
  for (auto const &window : m_windows) {
    if (window && predicate(window.value()))
      ret.add(i);
    i++;
  }
  return ret;
}

template <CodeBlocksManager::actions TO_DO, typename... Args>
auto CodeBlocksManager::apply(BlockSet windows, Args &&...args) -> void {
  for_indexes(windows, m_windows, action2function<TO_DO>(),
              std::forward<Args>(args)...);
}

template <CodeBlocksManager::actions Actions> consteval auto action2function() {
  if constexpr (Actions == CodeBlocksManager::actions::decorate) {
    return &CodeBlock::decorate;
  } else if constexpr (Actions == CodeBlocksManager::actions::move) {
    return &CodeBlock::move;
  }
}

} // namespace Canvas
