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
  App app(sf::VideoMode(600, 600));
  sf::Clock glob_time;
  while (app.m_render_window.isOpen()) {
    SetSettings().SetTime() = glob_time.getElapsedTime();
    glob_time.restart();

    sf::Event event;
    while (app.m_render_window.pollEvent(event)) {
      app.handle_event(event);
    }

    app.m_render_window.clear();
    app.m_render_window.draw(app.m_window_manager);
    app.m_render_window.display();
  }
  return 0;
}
