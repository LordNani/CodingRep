#include "Tools.h"
#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>
#include <list>
#include <vector>

int main() {
  int windowHeight,
      windowWidth; // Window size that is specified by user's input to GUI
  windowHeight = 768;
  windowWidth = 1024;
  sf::RenderWindow mainWindow(sf::VideoMode(windowWidth, windowHeight),
                              "MainWindow");
  mainWindow.setFramerateLimit(144);

  sf::Image image;
  image.create(windowWidth, windowHeight, sf::Color::White);
  sf::Texture canvas;
  sf::Sprite sprite;

  sf::Color currentColor = sf::Color::Black; // Color that user's chosen
  int currentTool = 0; // instrument that is currently chosen
  unsigned int thickness = 0;

  bool firstPoint = true;

  std::vector<std::pair<sf::Vertex, sf::Vertex>>
      vecLine; // Vector with all drawn Lines

  canvas.loadFromImage(image);
  sprite.setTexture(canvas);
  sf::Vector2i prevPos;
  while (mainWindow.isOpen()) {
    // canvas.loadFromImage(image);

    
    sf::Event event;
    while (mainWindow.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        mainWindow.close();
      else if ((event.type == sf::Event::MouseMoved) &&
               sf::Mouse::isButtonPressed(
                   sf::Mouse::Left)) // MouseMoved and leftClickHeld
      {
        switch (currentTool) {
        case 0: {
          vecLine =
              drawPencil(mainWindow, currentColor,
                         sf::Mouse::getPosition(mainWindow), thickness, 0);
		  prevPos = sf::Mouse::getPosition(mainWindow);
          break;
        }
        }
      } else if (event.type == sf::Event::MouseButtonPressed) {
        switch (currentTool) {
        case 0: {
          vecLine =
              drawPencil(mainWindow, currentColor,
                         sf::Mouse::getPosition(mainWindow), thickness, 1);
          break;
        }
        case 1: {
          vecLine = drawLine(mainWindow, currentColor,
                             sf::Mouse::getPosition(mainWindow));
          break;
        }
        }
      } else if (event.type == sf::Event::MouseButtonReleased) {

        canvas.update(mainWindow);
      }
    }

    mainWindow.clear();
    mainWindow.draw(sprite);
    for (auto const &i : vecLine) {
      sf::Vertex res[2];
      res[0] = i.first;
      res[1] = i.second;
      mainWindow.draw(res, 2, sf::Lines);
    }
    mainWindow.display();
  }

  return 0;
}
