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

// TODO: delete nothing - use deselect like everywhere else
enum decorations : size_t {
  select = 0,
  hover = 1 << 1,
  highlight = 1 << 2,
  nothing
};

constexpr auto SELECTED_THICKNESS = 4;
constexpr auto DEFAULT_THICKNESS = 1;

class CodeBlock : public sf::Drawable, public sf::Transformable {
public:
  CodeBlock(sf::String header, sf::String source_code);
  auto draw(sf::RenderTarget &target, sf::RenderStates states) const
      -> void override;

  [[nodiscard]] auto getGlobalBounds() const -> sf::FloatRect;
  [[nodiscard]] auto contains(sf::Vector2i) const -> bool;
  auto decorate(size_t decoration_filter, size_t to_decorate) -> void;

private:
  sf::Text m_source;
  sf::Text m_header;
  sf::RectangleShape m_border;
};
} // namespace Canvas
