#pragma once
#pragma once
#include <SFML/Graphics.hpp>

std::vector<std::pair<sf::Vertex, sf::Vertex>>
drawPencil(sf::RenderWindow &mainWindow, sf::Color &color,
           sf::Vector2i currentPos, int mode);

std::vector<std::pair<sf::Vertex, sf::Vertex>>
drawLine(sf::RenderWindow &mainWindow, sf::Color &color,
         sf::Vector2i currentPos);
std::vector<sf::CircleShape> drawBrush(sf::RenderWindow &mainWindow,
                                             sf::Color &color,
                                             sf::Vector2i currentPos,
                                             float thickness);
