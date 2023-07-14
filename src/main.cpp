#include "../include/Canvas.hpp"
#include "../include/TextWindow.hpp"
#include "../include/WindowManager.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>
#include <iostream>
using namespace Canvas;

int main() {
  EventDistributer app;
  sf::Clock glob_time;
  app.run();
  return 0;
}
