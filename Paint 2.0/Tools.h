#pragma once
#include <SFML/Graphics.hpp>


void drawPencil(sf::Color &color,
           sf::Vector2i currentPos, int mode, sf::RenderTexture& canvas);
void drawLine(sf::RenderTexture& canvas, sf::Color& color,
	sf::Vector2i currentPos);
void drawBrush(sf::RenderTexture& canvas, sf::Color& color,
	sf::Vector2f currentPos, float thickness);
void drawRect(sf::RenderTexture& canvas, sf::Color& color,
	sf::Vector2f currentPos,
	float thickness, bool isFilled, bool mode);
void drawEllipse(sf::RenderTexture& canvas, sf::Color& color,
	sf::Vector2f currentPos, float thickness, bool isFilled,
	bool mode);