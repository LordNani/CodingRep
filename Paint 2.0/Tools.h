#pragma once
#pragma once
#include <SFML/Graphics.hpp>

std::vector<std::pair<sf::Vertex, sf::Vertex>>
drawPencil(sf::RenderWindow &mainWindow, sf::Color &color,
           sf::Vector2i currentPos, int mode);

std::vector<std::pair<sf::Vertex, sf::Vertex>>
drawLine(sf::RenderWindow &mainWindow, sf::Color &color,
         sf::Vector2i currentPos);
void drawBrush(sf::RenderTexture& canvas, sf::Color& color,
	sf::Vector2f currentPos, float thickness);
void drawRect(sf::RenderTexture& canvas, sf::Color& color,
	sf::Vector2f currentPos,
	float thickness, bool isFilled, bool mode);
void drawEllipse(sf::RenderTexture& canvas, sf::Color& color,
	sf::Vector2f currentPos, float thickness, bool isFilled,
	bool mode);