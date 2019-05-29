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

  sf::Color currentColor = sf::Color::Black; // Color that user's chosen
  int currentTool = 2; // instrument that is currently chosen
  float thickness = 30;

  bool firstPoint = true;
  sf::Vector2i prevPos;

  std::vector<std::pair<sf::Vertex, sf::Vertex>>
      vecLine; // Vector with all drawn Lines
  std::vector<sf::CircleShape> vecCircle;
  sf::CircleShape brush;
  canvas.loadFromImage(image);
  sprite.setTexture(canvas);
  sf::RenderTexture canvasTwo;
  canvasTwo.create(1920,1080);
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
          prevPos = sf::Mouse::getPosition(mainWindow);
          break;
        }
		case 2: {
			vecCircle = drawBrush(mainWindow, currentColor, sf::Mouse::getPosition(mainWindow), 30);
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
			  sf::Vector2f newPos(mainWindow.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y)));
			  brush.setRadius(thickness);
			  brush.setPointCount(100);
			  brush.setFillColor(currentColor);
			  brush.setOrigin(thickness, thickness);
			  brush.setPosition(sf::Vector2f(sf::Mouse::getPosition(mainWindow)));
			  canvasTwo.draw(brush);
			  canvasTwo.display();
			  
			  
		  }
		  }
      } else if (event.type == sf::Event::MouseButtonReleased) {
        switch (currentTool) {
        case 0: {
          vecLine = drawPencil(mainWindow, currentColor,
                               sf::Mouse::getPosition(mainWindow), 2);
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

    mainWindow.clear();
    mainWindow.draw(sprite);
	/*for (auto const &i : vecLine) {
      sf::Vertex res[2];
      res[0] = i.first;
      res[1] = i.second;
      mainWindow.draw(res, 2, sf::Lines);
    } 
	for (auto const& i : vecCircle) {
		mainWindow.draw(i);
	}*/
    mainWindow.display(); 
  }

  return 0;
}
