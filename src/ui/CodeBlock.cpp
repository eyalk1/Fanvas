#include "ui/code-blocks/CodeBlock.hpp"
#include "UserAction.hpp"
#include "common/setting.hpp"
#include "utils/rectangles.hpp"
#include "utils/utility.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>

namespace Canvas {
auto CodeBlock::draw(sf::RenderTarget &target, sf::RenderStates states) const
    -> void {
  states.transform = getTransform();
  target.draw(m_source, states);
  target.draw(m_header, states);
  target.draw(m_border, states);
}

auto CodeBlock::contains(sf::Vector2i pos) const -> bool {
  auto diff = getPosition();
  auto fpos = sf::Vector2f(pos);
  return m_border.getGlobalBounds().contains(
      {fpos.x - diff.x, fpos.y - diff.y});
}

auto CodeBlock::getGlobalBounds() const -> sf::FloatRect {
  auto pos = getPosition();
  auto bounds = m_border.getGlobalBounds();
  return {pos.x, pos.y, bounds.width, bounds.height};
}

auto CodeBlock::decorate(size_t decoration_filter, size_t to_decorate) -> void {
  if (decoration_filter & decorations::highlight) {
    m_border.setOutlineColor((to_decorate & decorations::highlight)
                                 ? sf::Color::Red
                                 : sf::Color::White);
  }
  if (decoration_filter & decorations::hover) {
    m_border.setFillColor((to_decorate & decorations::hover)
                              ? sf::Color(128, 128, 128, 128)
                              : sf::Color::Transparent);
  }
  if (decoration_filter & decorations::select) {
    m_border.setOutlineThickness((to_decorate & decorations::select)
                                     ? SELECTED_THICKNESS
                                     : DEFAULT_THICKNESS);
  }
}

CodeBlock::CodeBlock(sf::String source, sf::String header)
    : m_source(sf::Text(source, GetSettings().GetFont(),
                        GetSettings().GetTextSize())),
      m_header(sf::Text(header, GetSettings().GetFont(),
                        GetSettings().GetTextSize() *
                            GetSettings().GetHeaderPartialSizeMul() /
                            GetSettings().GetHeaderPartialSizeDiv())),
      m_border() {
  // TODO: take values from settings
  m_border.setOutlineColor(sf::Color::White);
  m_border.setFillColor(sf::Color::Transparent);
  m_border.setOutlineThickness(DEFAULT_THICKNESS);
  m_header.setStyle(sf::Text::Underlined);

  m_header.setPosition(0, 0);
  auto header_bounds = m_header.getGlobalBounds();
  m_source.setPosition(0, header_bounds.top + header_bounds.height);
  auto source_bounds = m_source.getGlobalBounds();

  auto rect = addSlack(enclosing_rect({&header_bounds, &source_bounds}));
  m_border.setPosition(rect.left, rect.top);
  m_border.setSize({rect.width, rect.height});
}
} // namespace Canvas
