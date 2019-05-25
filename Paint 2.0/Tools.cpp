#include "Tools.h"
#include <SFML/Graphics.hpp>



	void ToolManager(sf::RenderWindow& mainWindow, sf::Image& image,
		sf::Color color, int currentTool, sf::Vector2i currentPos,
		sf::Vector2i prevPos) {
		switch (currentTool) {
		case 0: {
			//pencilDraw(mainWindow, image, color, currentPos);
			break;
		}
		case 1: {
			drawLine(mainWindow, color, currentPos);
			break;
		}
		}


	}

	/*sf::Vertex* drawOnImage(sf::RenderWindow& mainWindow, sf::Image& image,
		sf::Color color, sf::Vector2i currentPos,
		sf::Vector2i prevPos, bool newLine) {




		// sf::RectangleShape line(sf::Vector2f(150, 5));
		// line.rotate(45);

	} */

	std::vector<std::pair<sf::Vertex, sf::Vertex>>
		vecLine;

	sf::Vertex line[2];
	bool firstPoint = true;

	std::vector<std::pair<sf::Vertex, sf::Vertex>> drawLine(sf::RenderWindow& mainWindow,
		sf::Color color, sf::Vector2i currentPos) {
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

