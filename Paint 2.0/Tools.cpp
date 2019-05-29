#include "Tools.h"
#include <SFML/Graphics.hpp>

/*sf::Vertex* drawOnImage(sf::RenderWindow& mainWindow, sf::Image& image,
		sf::Color color, sf::Vector2i currentPos,
		sf::Vector2i prevPos, bool newLine) {




		// sf::RectangleShape line(sf::Vector2f(150, 5));
		// line.rotate(45);

} */

std::vector<std::pair<sf::Vertex, sf::Vertex>> vecLine;
std::vector<sf::CircleShape> vecCircle;
sf::Vertex line[2];
bool firstPoint = true;

std::vector<std::pair<sf::Vertex, sf::Vertex>>
drawPencil(sf::RenderWindow& mainWindow, sf::Color& color,
	sf::Vector2i currentPos, int mode) {
	
		if (mode == 1) {	
			line[0].position = sf::Vector2f(currentPos);
			line[0].color = color;
		}
		else if (mode == 0) {

			line[1].position = sf::Vector2f(currentPos);
			line[0].color = color;
			line[1].color = color;
			vecLine.push_back(std::make_pair(line[0], line[1]));
			
			line[0].position = sf::Vector2f(currentPos);
		}
		else {
				line[1].position = sf::Vector2f(currentPos);
				line[1].color = color;
				vecLine.push_back(std::make_pair(line[0], line[1]));
				
			}
		return vecLine;
	
}

std::vector<sf::CircleShape> drawBrush(sf::RenderWindow& mainWindow, sf::Color& color,
	sf::Vector2i currentPos,float thickness ) {
	sf::CircleShape brush(thickness, 100);
	brush.setFillColor(color);
	brush.setOrigin(thickness, thickness);
	brush.setPosition(sf::Vector2f(currentPos));
	vecCircle.push_back(brush);
	return vecCircle;
}

std::vector<std::pair<sf::Vertex, sf::Vertex>>
drawLine(sf::RenderWindow& mainWindow, sf::Color& color,
	sf::Vector2i currentPos) {
	if (firstPoint) {
		line[0].position = sf::Vector2f(currentPos);
		line[1].position = sf::Vector2f(currentPos);
		line[0].color = color;
		line[1].color = color;
		firstPoint = false;
	}
	else {
		line[1].position = sf::Vector2f(currentPos);
		firstPoint = true;
		vecLine.push_back(std::make_pair(line[0], line[1]));
	}
	return vecLine;
}
