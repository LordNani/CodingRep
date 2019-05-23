#include "Tools.h"
#include <SFML/Graphics.hpp>
#include <vector>

int main() {
  int windowHeight,
      windowWidth; // Window size that is specified by user's input to GUI
  windowHeight = 768;
  windowWidth = 1024;
  // create the window
  sf::RenderWindow mainWindow(sf::VideoMode(windowWidth, windowHeight),
                              "MainWindow");
  sf::Image image;
  image.create(windowWidth, windowHeight, sf::Color::White);
  sf::Texture canvas;
  sf::Color currentColor = sf::Color::Black; // Color that user's chosen
  int currentTool = 0; // instrument that is currently chosen
  sf::Sprite sprite;
  bool newLine = true;

  canvas.loadFromImage(image);
  sprite.setTexture(canvas);

  while (mainWindow.isOpen()) {
    canvas.loadFromImage(image);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		sf::Vector2i prevPos;
      if (newLine) {
		  sf::Vector2f vectors[2] = drawOnImage(mainWindow, image, currentColor, sf::Mouse::getPosition(mainWindow),
			sf::Mouse::getPosition(mainWindow), newLine);
        prevPos = sf::Mouse::getPosition(mainWindow);
		newLine = false;
		// start a new line, giving currentLine a new value,  saving it's
		// old value
      } else {
		  drawOnImage(mainWindow, image, currentColor, sf::Mouse::getPosition(mainWindow),
			  prevPos, newLine);
		  prevPos = sf::Mouse::getPosition(mainWindow);
      }
    } else {
      newLine = true;
    }
	
    sf::Event event;
    while (mainWindow.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        mainWindow.close();
      /* else if ((event.type == sf::Event::MouseMoved) &&
                (mousedown == 1)) // MouseMoved and leftClickHeld
       {

         drawOnImage(currentColor, currentTool, canvas, image,
                     sf::Mouse::getPosition(mainWindow));
       } else if (event.type == sf::Event::MouseButtonPressed) {
         mousedown = 1;
         drawOnImage(currentColor, currentTool, canvas, image,
                     sf::Mouse::getPosition(mainWindow));

       } else if (event.type == sf::Event::MouseButtonReleased) {
         mousedown = 0;
         canvas.update(mainWindow);
       } */
    }
	
    mainWindow.clear();
    mainWindow.draw(sprite);
	mainWindow.draw(line, 2, sf::Lines);
    mainWindow.display();
  }

  return 0;
}
