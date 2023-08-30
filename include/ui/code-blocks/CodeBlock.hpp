#pragma once

#include "bit_set/bit_set.hpp"
#include "common/consts.hpp"
#include "common/setting.hpp"
#include "utils/rectangles.hpp"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>
#include <array>

namespace Canvas {

enum decorations : size_t {
  select,
  deselect,
  hover,
  dehover,
  highlight,
  dehighlight,
  number_of_decorations,
};

class CodeBlock : public sf::Drawable, public sf::Transformable {
public:
  CodeBlock(sf::String header, sf::String source_code);
  auto draw(sf::RenderTarget &target, sf::RenderStates states) const
      -> void override;

  [[nodiscard]] auto getGlobalBounds() const -> sf::FloatRect;
  [[nodiscard]] auto contains(sf::Vector2i) const -> bool;
  auto decorate(std::size_t decoration_filter) -> void;

private:
  sf::Text m_source;
  sf::Text m_header;
  sf::RectangleShape m_border;
};
} // namespace Canvas
