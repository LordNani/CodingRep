#include "Tools.h"
#include <SFML/Graphics.hpp>

/*sf::Vertex* drawOnImage(sf::RenderWindow& mainWindow, sf::Image& image,
		sf::Color color, sf::Vector2i currentPos,
		sf::Vector2i prevPos, bool newLine) {




		// sf::RectangleShape line(sf::Vector2f(150, 5));
		// line.rotate(45);

} */

std::vector<std::pair<sf::Vertex, sf::Vertex>> vecLine;

sf::Vertex line[2];
bool firstPoint = true;

std::vector<std::pair<sf::Vertex, sf::Vertex>>
drawPencil(sf::RenderWindow& mainWindow, sf::Color color,
	sf::Vector2i currentPos, unsigned int thickness, int mode) {
	if (thickness == 0) {

		if (mode == 1) {
			line[0].position = sf::Vector2f(sf::Mouse::getPosition(mainWindow));
			line[1].position = sf::Vector2f(sf::Mouse::getPosition(mainWindow));
			line[0].color = color;
			line[1].color = color;

		}
		else {
			if (firstPoint) {
				line[0].position = sf::Vector2f(sf::Mouse::getPosition(mainWindow));
				line[1].position = sf::Vector2f(sf::Mouse::getPosition(mainWindow));
				line[0].color = color;
				line[1].color = color;
				firstPoint = false;
			}
			else {
				line[1].position = sf::Vector2f(sf::Mouse::getPosition(mainWindow));
				firstPoint = true;
				vecLine.push_back(std::make_pair(line[0], line[1]));
			}
		}
		return vecLine;
	}
	else {
	}
}

std::vector<std::pair<sf::Vertex, sf::Vertex>>
drawLine(sf::RenderWindow& mainWindow, sf::Color color,
	sf::Vector2i currentPos) {
	if (firstPoint) {
		line[0].position = sf::Vector2f(sf::Mouse::getPosition(mainWindow));
		line[1].position = sf::Vector2f(sf::Mouse::getPosition(mainWindow));
		line[0].color = color;
		line[1].color = color;
		firstPoint = false;
	}
	else {
		line[1].position = sf::Vector2f(sf::Mouse::getPosition(mainWindow));
		firstPoint = true;
		vecLine.push_back(std::make_pair(line[0], line[1]));
	}
	return vecLine;
}
