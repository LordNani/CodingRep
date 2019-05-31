#pragma once
#include <SFML/Graphics.hpp>
#include "SliderSFML.h"

void drawPencil(sf::Color &color, sf::Vector2i currentPos, int mode,
                sf::RenderTexture &canvas);
void drawLine(sf::RenderTexture &canvas, sf::Color &color,
              sf::Vector2i currentPos, float thickness);
void drawBrush(sf::RenderTexture &canvas, sf::Color &color,
               sf::Vector2f currentPos, float thickness);
void drawRect(sf::RenderTexture &canvas, sf::Color &color,
              sf::Vector2f currentPos, float thickness, bool isFilled,
              int mode);
void drawEllipse(sf::RenderTexture &canvas, sf::Color &color,
                 sf::Vector2f currentPos, float thickness, bool isFilled,
                 bool mode);
void setR(int type);
void renderOnScreen(sf::RenderWindow &mWindow, sf::RenderWindow &toolWindow,
                    sf::Sprite &sprite, sf::Sprite &toolSprite,
                    std::vector<SliderSFML> vecSlider);
void slidersInit(std::vector<SliderSFML> vecSlider, const sf::Color& color,
	const float& thickness);
void slidersRender(std::vector<SliderSFML> vecSlider, sf::Color& color,
	float& thickness)
