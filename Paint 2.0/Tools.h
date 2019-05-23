#pragma once
#include <SFML/Graphics.hpp>
 
sf::Vertex * drawOnImage(sf::RenderWindow& mainWindow,
	sf::Image& image, sf::Color color, sf::Vector2i currentPos, sf::Vector2i prevPos, bool newLine);