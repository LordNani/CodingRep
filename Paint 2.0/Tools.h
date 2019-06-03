#pragma once
#include "ButtonSFML.h"
#include "SliderSFML.h"
#include <SFML\Graphics.hpp>

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
                 int mode);

void renderOnScreen(sf::RenderWindow &mWindow, sf::RenderWindow &toolWindow,
                    sf::Sprite &sprite, sf::Sprite &toolSprite,
                    std::vector<SliderSFML> &vecSlider,
                    std::vector<ButtonSFML> vecButtons);
void slidersInit(std::vector<SliderSFML> &vecSlider, const sf::Color &color,
                 const float &thickness);
void slidersRender(std::vector<SliderSFML> &vecSlider, sf::Color &color,
                   float &thickness);
void buttonHandler(sf::RenderWindow &mWindow, sf::RenderTexture &mainCanvas,
                   sf::Vector2f pos, std::vector<ButtonSFML> &vecButtons,
                   int &currentTool, bool &isErasing, bool &isSaved,
                   bool &isFilled);
void saveFile(sf::RenderWindow &mainWindow);
void openFile(sf::RenderTexture &mainCanvas);
void init(ButtonSFML &vecButtons);
void select(sf::RenderWindow &mainWindow, sf::Vector2f curPos, bool mode);
void paste(sf::RenderWindow &mainWindow, sf::Vector2f curPos,
           sf::RenderTexture &mainCanvas);
void copy(sf::RenderWindow &mainWindow);
void cut(sf::RenderWindow &mainWindow, sf::RenderTexture &mainCanvas);
