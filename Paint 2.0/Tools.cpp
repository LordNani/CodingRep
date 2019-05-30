#include "Tools.h"
#include "EllipseShape.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#define PI 3.1415926535898

std::vector<std::pair<sf::Vertex, sf::Vertex>> vecLine;
std::vector<sf::CircleShape> vecCircle;
sf::Vertex line[2];
bool firstPoint = true;

std::vector<std::pair<sf::Vertex, sf::Vertex>>
drawPencil(sf::RenderWindow &mainWindow, sf::Color &color,
           sf::Vector2i currentPos, int mode) {

  if (mode == 1) {
    line[0].position = sf::Vector2f(currentPos);
    line[0].color = color;
  } else if (mode == 0) {

    line[1].position = sf::Vector2f(currentPos);
    line[0].color = color;
    line[1].color = color;
    vecLine.push_back(std::make_pair(line[0], line[1]));

    line[0].position = sf::Vector2f(currentPos);
  } else {
    line[1].position = sf::Vector2f(currentPos);
    line[1].color = color;
    vecLine.push_back(std::make_pair(line[0], line[1]));
  }
  return vecLine;
}

sf::CircleShape brush;

void drawBrush(sf::RenderTexture &canvas, sf::Color &color,
               sf::Vector2f currentPos, float thickness) {
  brush.setRadius(thickness);
  brush.setPointCount(100);
  brush.setFillColor(color);
  brush.setOrigin(thickness, thickness);
  brush.setPosition(currentPos);
  canvas.draw(brush);
  canvas.display();
}

std::vector<std::pair<sf::Vertex, sf::Vertex>>
drawLine(sf::RenderWindow &mainWindow, sf::Color &color,
         sf::Vector2i currentPos) {
  if (firstPoint) {
    line[0].position = sf::Vector2f(currentPos);
    line[1].position = sf::Vector2f(currentPos);
    line[0].color = color;
    line[1].color = color;
    firstPoint = false;
  } else {
    line[1].position = sf::Vector2f(currentPos);
    firstPoint = true;
    vecLine.push_back(std::make_pair(line[0], line[1]));
  }
  return vecLine;
}

sf::Vector2f point1;
sf::RectangleShape rect;

void drawRect(sf::RenderTexture &canvas, sf::Color &color,
              sf::Vector2f currentPos, float thickness, bool isFilled,
              bool mode) {
  if (mode)
    point1 = currentPos;
  else {

    if (isFilled) {
      rect.setFillColor(color);
      rect.setPosition(point1);
      rect.setSize(currentPos - point1);
    } else {
      rect.setFillColor(sf::Color::Transparent);
      rect.setOutlineColor(color);
      rect.setOutlineThickness(thickness);
      rect.setPosition(point1 + sf::Vector2f(thickness, thickness));
      rect.setSize(currentPos - point1 - sf::Vector2f(thickness, thickness) -
                   sf::Vector2f(thickness, thickness));
    }

    canvas.draw(rect);
    canvas.display();
  }
}

sf::ConvexShape ellipse;
float radius_x;
float radius_y;
unsigned short const quality = 50;

void drawEllipse(sf::RenderTexture &canvas, sf::Color &color,
                 sf::Vector2f currentPos, float thickness, bool isFilled,
                 bool mode) {
  if (mode)
    point1 = currentPos;
  else {

    ellipse.setPointCount(quality);

    if (isFilled) {
      radius_x = (currentPos.x - point1.x) / 2.f;
      radius_y = (currentPos.y - point1.y) / 2.f;
      ellipse.setFillColor(color);
      ellipse.setPosition(point1 + sf::Vector2f(radius_x, radius_y));
    } else {
      radius_x = (abs(currentPos.x - point1.x) - 2*thickness) / 2.f ;
      radius_y = (abs(currentPos.y - point1.y) - 2*thickness) / 2.f ;
      ellipse.setFillColor(sf::Color::Transparent);
      ellipse.setOutlineColor(color);
      ellipse.setOutlineThickness(thickness);
	  if (point1.x > currentPos.x && point1.y > currentPos.y) {
		  ellipse.setPosition(point1 - sf::Vector2f(radius_x, radius_y) - sf::Vector2f(thickness, thickness));
	  }
	  else if(point1.y > currentPos.y){
		  ellipse.setPosition(point1 + sf::Vector2f(radius_x, -2*radius_y) + sf::Vector2f(thickness, thickness));
	  }
	  else if(point1.x > currentPos.x && point1.y< currentPos.y){
		  ellipse.setPosition(point1 + sf::Vector2f(-1 * radius_x, radius_y) + sf::Vector2f(-1.f * thickness, thickness));
	  }
	  else {
		  ellipse.setPosition(point1 + sf::Vector2f(radius_x, radius_y) + sf::Vector2f(thickness,thickness));
	  }
    }

    for (unsigned int i = 0; i < quality; ++i) {
      float rad = (360 / quality * i) / (360 / PI / 2);
      float x = cos(rad) * radius_x;
      float y = sin(rad) * radius_y;
      ellipse.setPoint(i, sf::Vector2f(x, y));
    };
    canvas.draw(ellipse);
    canvas.display();
  }
}
