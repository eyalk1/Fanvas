#include "../include/Canvas.hpp"
#include "../include/ui/code-blocks/CodeBlock.hpp"
#include "../include/ui/code-blocks/CodeBlockManager.hpp"
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
