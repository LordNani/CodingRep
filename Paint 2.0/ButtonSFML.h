#pragma once
#include <SFML\Graphics.hpp>

class ButtonSFML {

  sf::RectangleShape button;
  sf::Text text;
  sf::Font font;
  int posX, posY;
  int width, height;
  bool isPressed;
  bool isToggling;
  int rNumber;


public:
  ButtonSFML(int x, int y, float widthX, float heightY, bool isToggle, bool pressed,
             int returnNumber, const std::string& label);
  int buttonPressed();
  sf::FloatRect getGlobalBounds();
  void draw(sf::RenderWindow& window);
  void setTexture(sf::Texture *back);
  void setTextPosition(sf::Vector2f pos);
  sf::Vector2f getPosition();
  void setTextPosition(std::string words);
  bool getOn();
};
