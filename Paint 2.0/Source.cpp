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
  mainWindow.setFramerateLimit(2000);

  sf::Image image;
  image.create(1920, 1080, sf::Color::White);
  sf::Texture canvas;
  sf::Sprite sprite;

  sf::Color currentColor(255, 0, 0, 50); // Color that user's chosen
  int currentTool = 3;                   // instrument that is currently chosen
  float thickness = 30;
  bool isFilled = false;

  bool firstPoint = true;
  sf::Vector2i prevPos;

  std::vector<std::pair<sf::Vertex, sf::Vertex>>
      vecLine; // Vector with all drawn Lines
  std::vector<sf::CircleShape> vecCircle;

  canvas.loadFromImage(image);
  sprite.setTexture(canvas);
  sf::RenderTexture canvasTwo;
  canvasTwo.create(1920, 1080);
  canvasTwo.clear(sf::Color::White);
  sprite.setTexture(canvasTwo.getTexture(), true);
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
          vecLine = drawPencil(mainWindow, currentColor,
                               sf::Mouse::getPosition(mainWindow), 0);
          break;
        }
        case 2: {
          drawBrush(canvasTwo, currentColor,
                    sf::Vector2f(sf::Mouse::getPosition(mainWindow)),
                    thickness);
          break;
        }
        }
      } else if (event.type == sf::Event::MouseButtonPressed) {
        switch (currentTool) {
        case 0: {
          vecLine = drawPencil(mainWindow, currentColor,
                               sf::Mouse::getPosition(mainWindow), 1);
          break;
        }
        case 1: {
          vecLine = drawLine(mainWindow, currentColor,
                             sf::Mouse::getPosition(mainWindow));
          break;
        }
        case 2: {
          drawBrush(canvasTwo, currentColor,
                    sf::Vector2f(sf::Mouse::getPosition(mainWindow)),
                    thickness);
          break;
        }
		case 3: {
			drawRect(canvasTwo, currentColor,
				sf::Vector2f(sf::Mouse::getPosition(mainWindow)),
				thickness, isFilled,true);
			break;
		}
		case 4: {
			drawEllipse(canvasTwo, currentColor,
				sf::Vector2f(sf::Mouse::getPosition(mainWindow)),
				thickness, isFilled, true);
			break;
		}
        }
      } else if (event.type == sf::Event::MouseButtonReleased) {
        switch (currentTool) {
        case 0: {
          break;
        }
		case 3: {
			drawRect(canvasTwo, currentColor,
				sf::Vector2f(sf::Mouse::getPosition(mainWindow)),
				thickness, isFilled, false);
			break;
		}
		case 4: {
			drawEllipse(canvasTwo, currentColor,
				sf::Vector2f(sf::Mouse::getPosition(mainWindow)),
				thickness, isFilled, false);
			break;
		}
        }

      } else if (event.type == sf::Event::Resized) {
        // Window got resized, update the view to the new size
        sf::View view(mainWindow.getView());
        const sf::Vector2f size(mainWindow.getSize().x, mainWindow.getSize().y);
        view.setSize(size); // Set the size
        view.setCenter(
            size / 2.f); // Set the center, moving our drawing to the top left
        mainWindow.setView(view); // Apply the view
      }
    }
	sf::RectangleShape test(sf::Vector2f(400, 200));
	test.setPosition(windowWidth / 2-test.getSize().x/2, windowHeight / 2- test.getSize().y/2);
	test.setFillColor(sf::Color::Transparent);
	test.setOutlineThickness(2.f);
	test.setOutlineColor(sf::Color::Black);
	canvasTwo.draw(test);
	canvasTwo.display();
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
