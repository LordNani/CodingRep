#pragma once
#pragma once
#include <SFML/Graphics.hpp>


std::vector<std::pair<sf::Vertex, sf::Vertex>> drawPencil(sf::RenderWindow& mainWindow,
	sf::Color color, sf::Vector2i currentPos, unsigned int thickness, int mode, sf::Vector2i prevPos);
std::vector<std::pair<sf::Vertex, sf::Vertex>> drawLine(sf::RenderWindow& mainWindow,
	sf::Color color, sf::Vector2i currentPos);
