#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>

namespace Canvas {

#define SettingsGetter(what, type, ...)                                        \
public:                                                                        \
  const auto &Get##what() const { return what; }                               \
                                                                               \
private:                                                                       \
  type what { __VA_ARGS__ }

#define SettingsSetter(what, type, ...)                                        \
public:                                                                        \
  auto &Set##what() { return what; }                                           \
  SettingsGetter(what, type, __VA_ARGS__)

class Settings {
  Settings() {
    std::string fontpath("/usr/share/fonts/truetype/freefont/FreeMono.ttf");
    if (!Font.loadFromFile(fontpath)) {
      throw "no font";
    }
  }
  friend auto GetSettings() -> const Settings &;
  friend auto SetSettings() -> Settings &;

public:
  SettingsGetter(Font, sf::Font);
  SettingsGetter(MaxTextWindowWidth, static constexpr uint, 99);
  SettingsGetter(TextSize, static constexpr uint, 26);
  SettingsGetter(HeaderPartialSizeMul, static constexpr uint, 1);
  SettingsGetter(HeaderPartialSizeDiv, static constexpr uint, 2);
  SettingsGetter(Slack, static constexpr float, 5);
  SettingsGetter(CodeBlockOutlineColor, const sf::Color, sf::Color::White);
  SettingsGetter(CodeBlockFillColor, const sf::Color, sf::Color::Transparent);
  SettingsGetter(CodeBlockOutlineThickness, const float, 1);
  SettingsGetter(CodeBlockHeaderStyle, static constexpr sf::Text::Style,
                 sf::Text::Style::Underlined);
  SettingsGetter(CodeBlockHighlightOutlineColor, const sf::Color,
                 sf::Color::Red);
  SettingsGetter(CodeBlockHoverFillColor, const sf::Color,
                 sf::Color(128, 128, 128));
  SettingsGetter(CodeBlockSelectOutlineThickness, static constexpr float, 4);
};

auto GetSettings() -> const Settings &;
auto SetSettings() -> Settings &;

} // namespace Canvas
