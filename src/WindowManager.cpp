#include "../include/WindowManager.hpp"
#include "../include/bit_set.hpp"
#include "../include/utility.hpp"
#include "TextWindow.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
// #include "../include/multimax.hpp"
#include <algorithm>
#include <cmath>
#include <numeric>
#include <optional>
#include <utility>
namespace CircularQ {
#include "../include/circularQueue.hpp"
}
// forward declarations
namespace sf {
class Transformable;
}

namespace Canvas {
auto WindowManager::get_all_windows() -> WindowSet {
  // since findWindows already checks for nullopt we just want any window
  return findWindows([](auto const &window) { return true; });
}

auto WindowManager::newTextWindow(sf::String &&header, sf::String &&source)
    -> TextWindow const & {
  auto window_it = std::find(m_windows.begin(), m_windows.end(), std::nullopt);
  auto &window = window_it->emplace(header, source);

  auto target_size = window.getGlobalBounds();
  // windows that were already intersected cannot be intersected again - we
  // will filter them with this
  // we also make sure we don't include ourselves in the intersection group
  WindowSet available_windows = get_all_windows();
  available_windows.erase(window_it - m_windows.begin());

  auto where_to_place =
      findOpenspace({target_size.width, target_size.height}, available_windows);
  window.setPosition(where_to_place);

  // TODO: animate indication of where the new window is

  return window;
}

auto WindowManager::deleteTextWindow(WindowSet windows) -> void {
  for_indexes(windows, m_windows, [](auto &window) { window.reset(); });
}

auto WindowManager::draw(sf::RenderTarget &target,
                         sf::RenderStates states) const -> void {
  for_each_optional(m_windows, [&target, &states](auto const &window) {
    states.transform = window->getTransform();
    target.draw(*window, states);
  });
}

auto WindowManager::findOpenspace(sf::Vector2f rec_size,
                                  WindowSet available_windows) -> sf::Vector2f {
  // no windows? no problem!
  if (available_windows.empty())
    return {0, 0};

  auto const &slack = GetSettings().GetSlack();
  // get the starting position - top left point of all the windows
  // auto [min_x, min_y] = std::accumulate(
  //     available_windows.begin(), available_windows.end(),
  //     std::make_tuple(INFINITY, INFINITY), [this](auto tup, auto windex) {
  //       auto gb = m_windows[windex]->getGlobalBounds();
  //       return std::make_tuple(std::min(std::get<0>(tup), gb.left),
  //                              std::min(std::get<1>(tup), gb.top));
  //     });
  // auto [min_x, min_y] = std::ranges::accumulate(
  //     available_windows,
  //     std::make_tuple(INFINITY, INFINITY),
  //     [this](auto tup, auto windex) -> decltype(tup) {
  //       auto gb = m_windows[windex]->getGlobalBounds();
  //       return {std::min(std::get<0>(tup), gb.left),
  //               std::min(std::get<1>(tup), gb.top)};
  //     });
  // what i want:
  // avialable_windows | get_window | getbounds | get_values | extremafy
  // TODO use accumulate - lol didn't work ^
  float min_x = INFINITY;
  float min_y = INFINITY;
  for (auto window : available_windows) {
    auto gb = m_windows[window]->getGlobalBounds();
    min_x = std::min(min_x, gb.left);
    min_y = std::min(min_y, gb.top);
  }

  // start the BFS
  CircularQ::circularQueue<sf::Vector2f, MAX_NUMBER_OF_WINDOWS + 1> candidates(
      sf::Vector2f{min_x + slack, min_y + slack});
  // TODO: handle too many windows
  while (true) {
    // take a new candidate
    auto popped = candidates.front();
    candidates.pop();
    auto candidate = sf::FloatRect(popped.x, popped.y, rec_size.x, rec_size.y);

    // get all the windows it intersects with
    auto intersects = findWindows([candidate](auto const &window) {
      return window.getGlobalBounds().intersects(candidate);
    });
    // if non - we are done!
    if (intersects.empty())
      return {candidate.left, candidate.top};

    float max_x = -INFINITY;
    float max_y = -INFINITY;
    for (auto intersecter : intersects) {
      auto bounds = m_windows[intersecter]->getGlobalBounds();
      max_x = std::max(max_x, bounds.left + bounds.width);
      max_y = std::max(max_y, bounds.top + bounds.height);
    }

    // generate new candidates - the lowest and the rightest points of all the
    // intersections
    candidates.push(sf::Vector2f(candidate.left, max_y + slack));
    candidates.push(sf::Vector2f(max_x + slack, candidate.top));
    available_windows -= intersects;
  }
}

} // namespace Canvas
