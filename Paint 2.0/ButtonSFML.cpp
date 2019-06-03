#include "ButtonSFML.h"
#include <iostream>

ButtonSFML::ButtonSFML(int x, int y, float widthX, float heightY, bool isToggle,
                       bool pressed, int returnNumber,
                       const std::string &label) {
  posX = x;
  posY = y;
  width = widthX;
  height = heightY;
  isToggling = isToggle;
  rNumber = returnNumber;
  text.setString(label);
  isPressed = pressed;

  if (!font.loadFromFile("Fonts\\Roboto-Bold.ttf"))
    std::cout << "Error loading font\n";
  // font.loadFromFile("Fonts\\Roboto-Light.ttf");
  text.setFont(font);
  text.setCharacterSize(25);
  text.setFillColor(sf::Color::Black);

  button.setPosition(posX, posY);
  button.setSize(sf::Vector2f(width, height));
  button.setOutlineThickness(2);
  button.setOutlineColor(sf::Color::Black);
}

void ButtonSFML::setTextPosition(sf::Vector2f pos) { text.setPosition(pos); }

sf::Vector2f ButtonSFML::getPosition() { return button.getPosition(); }
void ButtonSFML::setTextPosition(std::string words) { text.setString(words); }

sf::FloatRect ButtonSFML::getGlobalBounds() { return button.getGlobalBounds(); }

bool ButtonSFML::getOn() { return isPressed; }

int ButtonSFML::buttonPressed() {
  if (isToggling) {
    isPressed = !isPressed;
  }
  return rNumber;
}

void ButtonSFML::draw(sf::RenderWindow &window) {
  window.draw(button);
  if (text.getString() != ("NOTEXT")) {
    window.draw(text);
  }
}

void ButtonSFML::setTexture(sf::Texture *back) {
  button.setTexture(back, false);
}

void ButtonSFML::setText(std::string newText) { text.setString(newText); }
