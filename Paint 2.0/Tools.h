#pragma once
#include <SFML/Graphics.hpp>


void drawPencil(sf::Color &color,
           sf::Vector2i currentPos, int mode, sf::RenderTexture& canvas);
void drawLine(sf::RenderTexture& canvas, sf::Color& color,
	sf::Vector2i currentPos,float thickness);
void drawBrush(sf::RenderTexture& canvas, sf::Color& color,
	sf::Vector2f currentPos, float thickness);
void drawRect(sf::RenderTexture& canvas, sf::Color& color,
	sf::Vector2f currentPos,
	float thickness, bool isFilled, int mode);
void drawEllipse(sf::RenderTexture& canvas, sf::Color& color,
	sf::Vector2f currentPos, float thickness, bool isFilled,
	bool mode);
void setR(int type);
void renderOnScreen(sf::RenderWindow& mWindow, sf::Sprite& sprite);
