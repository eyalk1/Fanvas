#include "../include/rectangles.hpp"
#include "../include/setting.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <cmath>
#include <vector>
namespace Canvas {

auto enclosing_rect(std::vector<sf::FloatRect *> const &recs) -> sf::FloatRect {
  float min_left = INFINITY, min_top = INFINITY, max_right = -INFINITY,
        max_bottom = -INFINITY;
  for (auto const &rec : recs) {
    min_left = std::min(min_left, rec->left);
    min_top = std::min(min_top, rec->top);
    max_right = std::max(max_right, rec->left + rec->width);
    max_bottom = std::max(max_bottom, rec->top + rec->height);
  }
  return {min_left, min_top, max_right - min_left, max_bottom - min_top};
}

auto addSlack(sf::FloatRect const &r) -> sf::FloatRect {
  auto const s = GetSettings().GetSlack();
  return {r.left - s, r.top - s, r.width + s + s, r.height + s + s};
}
} // namespace Canvas
