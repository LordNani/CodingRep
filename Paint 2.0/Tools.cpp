#include "Tools.h"
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>

sf::Vertex* drawOnImage(sf::RenderWindow &mainWindow, sf::Image &image,
                        sf::Color color, sf::Vector2i currentPos,
                        sf::Vector2i prevPos, bool newLine) {

  sf::Vertex line[] = { sf::Vertex(sf::Vector2f(prevPos.x, prevPos.y)),
                        sf::Vertex(sf::Vector2f(currentPos.x, currentPos.y))
  };

  return line;
  // sf::RectangleShape line(sf::Vector2f(150, 5));
  // line.rotate(45);
  // mainWindow.draw(line, 2, sf::Lines);
}

/*class DrawnLine {
        std::vector<sf::Vector2i> points;
public:
        DrawnLine();
        void addPoint(sf::Vector2i p) { points.push_back(p); }
        void draw_me(RenderTarget& r) {
                //draw lines between points 0 and 1, 1 and 2, etc...
        }

};*/
