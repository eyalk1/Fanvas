#pragma once

#include <SFML/Graphics/Font.hpp>
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
  SettingsGetter(MaxTextWindowWidth, uint, 99);
  SettingsGetter(TextSize, int, 26);
  SettingsGetter(HeaderPartialSize, float, 0.5);
  SettingsGetter(Slack, uint, 5);

  // TODO make mouse pos a member of the App
  SettingsSetter(MousePos, sf::Vector2i);
  SettingsSetter(Time, sf::Time);
};

auto GetSettings() -> const Settings &;
auto SetSettings() -> Settings &;

} // namespace Canvas
