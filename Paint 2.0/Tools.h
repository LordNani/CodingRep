#pragma once
#include <SFML/Graphics.hpp>
 
sf::Vector2f * drawOnImage(sf::RenderWindow& mainWindow,
	sf::Image& image, sf::Color color, sf::Vector2i currentPos, sf::Vector2i prevPos, bool newLine);