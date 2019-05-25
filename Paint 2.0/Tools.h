#pragma once
#include <SFML/Graphics.hpp>

	sf::Vertex* drawOnImage(sf::RenderWindow& mainWindow,
		sf::Image& image, sf::Color color, sf::Vector2i currentPos, sf::Vector2i prevPos, bool newLine);

	void ToolManager(sf::RenderWindow& mainWindow, sf::Image& image,
		sf::Color color, int currentTool, sf::Vector2i currentPos,
		sf::Vector2i prevPos);
	std::vector<std::pair<sf::Vertex, sf::Vertex>> drawLine(sf::RenderWindow& mainWindow,
		sf::Color color, sf::Vector2i currentPos);
