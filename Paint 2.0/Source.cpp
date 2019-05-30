#include "Tools.h"
#include <SFML/Graphics.hpp>
#include <array>
#include <vector>

int main() {
  
  int windowHeight = 768; // Window size that is specified by user's input to GUI
  int windowWidth = 1024;
  sf::RenderWindow mainWindow(sf::VideoMode(windowWidth, windowHeight),
                              "MainWindow");
  mainWindow.setFramerateLimit(2000);

  sf::Image image;
  image.create(1920, 1080, sf::Color::White);
  sf::Texture canvas;
  sf::Sprite sprite;

  sf::Color currentColor(255, 0, 0, 50); // Color that user's chosen
  int currentTool = 1;                   // instrument that is currently chosen
  float thickness = 30;  // line thickness, brush size, or outline thickness
  bool isFilled = true; // if false, thickness = outline thickness

  sf::Vector2i prevPos;

  canvas.loadFromImage(image);
  sprite.setTexture(canvas);
  sf::RenderTexture canvasTwo;
  canvasTwo.create(1920, 1080);
  canvasTwo.clear(sf::Color::White);
  canvasTwo.setSmooth(true);
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
          drawPencil( currentColor,
                               sf::Mouse::getPosition(mainWindow), 0, canvasTwo);
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
				sf::Vector2f(sf::Mouse::getPosition(mainWindow)), thickness,
				isFilled, 2);
			break;
		}

        }
      } else if (event.type == sf::Event::MouseButtonPressed) {
        switch (currentTool) {
        case 0: {
          drawPencil( currentColor,
                               sf::Mouse::getPosition(mainWindow), 1,canvasTwo);
          break;
        }
        case 1: {
          drawLine(canvasTwo, currentColor,
                             sf::Mouse::getPosition(mainWindow),thickness);
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
                   sf::Vector2f(sf::Mouse::getPosition(mainWindow)), thickness,
                   isFilled, 1);
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
                   sf::Vector2f(sf::Mouse::getPosition(mainWindow)), thickness,
                   isFilled, 3);
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
        sf::View view(mainWindow.getView());
        const sf::Vector2f size(mainWindow.getSize().x, mainWindow.getSize().y);
        view.setSize(size);         // Set the size
        view.setCenter(size / 2.f); // moving our drawing to the top left
        mainWindow.setView(view);   // Apply the view
      }
    }

    sf::RectangleShape test(
        sf::Vector2f(400, 200)); // start of test rect in the middle
    test.setPosition(windowWidth / 2 - test.getSize().x / 2,
                     windowHeight / 2 - test.getSize().y / 2);
    test.setFillColor(sf::Color::Transparent);
    test.setOutlineThickness(2.f);
    test.setOutlineColor(sf::Color::Black);
    canvasTwo.draw(test);
    canvasTwo.display(); // end of it.

	renderOnScreen(mainWindow, sprite);
  }

  return 0;
}
