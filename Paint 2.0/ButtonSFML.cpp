#include "ButtonSFML.h"
#include <iostream>

ButtonSFML::ButtonSFML(int x, int y, float widthX, float heightY, bool isToggle,bool pressed,
                       int returnNumber, const std::string& label) {
  posX = x;
  posY = y;
  width = widthX;
  height = heightY;
  isToggling = isToggle;
  rNumber = returnNumber;
 // text.setString = label;
  isPressed = pressed;

  if (label.compare("NOTEXT") == 0) {
	  text.setString("NOTEXT");
	  
  }

  if (!font.loadFromFile("Fonts\\Roboto-Light.ttf"))
    std::cout << "Error loading font\n";
  //font.loadFromFile("Fonts\\Roboto-Light.ttf");
  text.setFont(font);
  text.setFillColor(sf::Color::White);
  text.setPosition(button.getPosition());
  button.setPosition(posX, posY);
  button.setSize(sf::Vector2f(width, height));
  button.setOutlineThickness(2);
  button.setOutlineColor(sf::Color::Black);
 
}

sf::FloatRect ButtonSFML::getLocalBounds() {

	return button.getLocalBounds();
}

int ButtonSFML::buttonPressed(){
	if (isToggling) {
		isPressed = !isPressed;
	}
	return rNumber;
}
void ButtonSFML::draw(sf::RenderWindow &window) {
	window.draw(button);
	if (text.getString()!=("NOTEXT")) {
		window.draw(text);
	}

}
void ButtonSFML::setTexture(sf::Texture *back) {
	button.setTexture(back, false);
}
