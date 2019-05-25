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
  sf::Image image;
  image.create(windowWidth, windowHeight, sf::Color::White);
  sf::Texture canvas;
  sf::Sprite sprite;

  sf::Color currentColor = sf::Color::Black; // Color that user's chosen
  int currentTool = 1; // instrument that is currently chosen

  int mousedown = 0;
  bool firstPoint = true;
  std::vector<std::pair<sf::Vertex, sf::Vertex>>
	  vecLine;  // Vector with all drawn Lines

  canvas.loadFromImage(image);
  sprite.setTexture(canvas);


   

  while (mainWindow.isOpen()) {
    canvas.loadFromImage(image);

    sf::Vector2i prevPos;
    sf::Event event;
    while (mainWindow.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        mainWindow.close();
      else if ((event.type == sf::Event::MouseMoved) &&
               (mousedown == 1)) // MouseMoved and leftClickHeld
      {
        /*sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f((float)prevPos.x, (float)prevPos.y)),
            sf::Vertex(sf::Vector2f(sf::Mouse::getPosition(mainWindow).x,
                                    sf::Mouse::getPosition(mainWindow).y))};
        prevPos = sf::Mouse::getPosition(mainWindow);
                mainWindow.draw(line, 2, sf::Lines);*/

      } else if (event.type == sf::Event::MouseButtonPressed) {
        
        mousedown = 1;
		if (currentTool == 1) {
			vecLine = drawLine(mainWindow, currentColor, sf::Mouse::getPosition(mainWindow));
		}
        /* sf::Vertex line[] = {
             sf::Vertex(sf::Vector2f(sf::Mouse::getPosition(mainWindow).x,
                                     sf::Mouse::getPosition(mainWindow).y)),
             sf::Vertex(sf::Vector2f(sf::Mouse::getPosition(mainWindow).x,
                                     sf::Mouse::getPosition(mainWindow).y))};
         prevPos = sf::Mouse::getPosition(mainWindow);
         
                  */
      } else if (event.type == sf::Event::MouseButtonReleased) {
        mousedown = 0;
        canvas.update(mainWindow);
      }
    }

    mainWindow.clear();
    mainWindow.draw(sprite);
	for (auto const& i : vecLine) {
		sf::Vertex res[2];
		res[0] = i.first;
		res[1] = i.second;
		mainWindow.draw(res, 2, sf::Lines);
	}
    mainWindow.display();
  }

  return 0;
}
