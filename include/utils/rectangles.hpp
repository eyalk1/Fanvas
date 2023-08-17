#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <vector>
namespace Canvas {

[[nodiscard]] auto enclosing_rect(std::vector<sf::FloatRect *> const &recs) -> sf::FloatRect;

[[nodiscard]] auto addSlack(sf::FloatRect const &r) -> sf::FloatRect;

} // namespace Canvas
