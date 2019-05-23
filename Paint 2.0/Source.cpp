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
  image.create(windowWidth, windowHeight, sf::Color::Black);
  sf::Texture canvas;
  sf::Color currentColor = sf::Color::Black; // Color that user's chosen
  int currentTool = 0; // instrument that is currently chosen
  sf::Sprite sprite;
  int mousedown = 0;
  bool newLine = true;
  bool firstPoint = true;
  std::vector< sf::Vertex[2]> vecLine; // Vector with all drawn Lines
  canvas.loadFromImage(image);
  sprite.setTexture(canvas);

  sf::Vertex line[2];
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
		  if (firstPoint) {
			  line[0].position = sf::Vector2f(sf::Mouse::getPosition(mainWindow));
			  line[1].position = sf::Vector2f(sf::Mouse::getPosition(mainWindow));
			  firstPoint = false;
		  }
		  else {
			  line[1].position = sf::Vector2f(sf::Mouse::getPosition(mainWindow));
			  firstPoint = true;
			  vecLine.push_back(line);
		  }
        mousedown = 1;
		
       /* sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(sf::Mouse::getPosition(mainWindow).x,
                                    sf::Mouse::getPosition(mainWindow).y)),
            sf::Vertex(sf::Vector2f(sf::Mouse::getPosition(mainWindow).x,
                                    sf::Mouse::getPosition(mainWindow).y))};
        prevPos = sf::Mouse::getPosition(mainWindow);
        
		 */
      } else if (event.type == sf::Event::MouseButtonReleased) {
        mousedown = 0;
		newLine = true;
        canvas.update(mainWindow);
      }
    }
	
    mainWindow.clear();
    mainWindow.draw(sprite);
	for (std::vector< sf::Vertex[2]>::iterator it = vecLine.begin(); it != vecLine.end(); ++it) {
		mainWindow.draw(*it, 2, sf::Lines);
	}
    
    mainWindow.display();
  }

  return 0;
}
