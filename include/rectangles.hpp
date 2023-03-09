#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <vector>
namespace Canvas {

auto enclosing_rect(std::vector<sf::FloatRect *> const &recs) -> sf::FloatRect;

auto addSlack(sf::FloatRect const &r) -> sf::FloatRect;

} // namespace Canvas
