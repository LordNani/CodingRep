#pragma once
#include <SFML\Graphics.hpp>

class ButtonSFML {

  sf::RectangleShape button;
  sf::Text text;
  sf::Font font;
  sf::Texture test;
  int posX, posY;
  int width, height;
  bool isPressed;
  bool isToggling;
  int rNumber;


public:
  ButtonSFML(int x, int y, float widthX, float heightY, bool isToggle, bool pressed,
             int returnNumber, const std::string&);
  int buttonPressed();
  sf::FloatRect getLocalBounds();
  void draw(sf::RenderWindow& window);
  void setTexture(sf::Texture *back);
};
