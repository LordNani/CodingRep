#include "Tools.h"
#include "SFML/Graphics.hpp"
#include <cmath>
#include "tinyfiledialogs.h"
#define PI 3.1415926535898

std::vector<std::pair<sf::Vertex, sf::Vertex>> vecLine; // vector to store lines
sf::Vertex line[2];                                     // for line
bool firstPoint = true;
sf::RectangleShape tLine;
sf::CircleShape brush;   // brush shape
sf::ConvexShape ellipse; // for ellipse tool
float radius_x;
float radius_y;
float realThickness;
unsigned short const quality = 100; // point Count of convex
sf::Vector2f point1;                // for everything
sf::RectangleShape rect;            // rect tool

int RT = 0;

void drawPencil(sf::Color &color, sf::Vector2i currentPos, int mode,
                sf::RenderTexture &canvas) {

  if (mode == 1) {
    line[0].position = sf::Vector2f(currentPos);
    line[0].color = color;
  } else if (mode == 0) {

    line[1].position = sf::Vector2f(currentPos);
    line[0].color = color;
    line[1].color = color;
    canvas.draw(line, 2, sf::Lines);
    canvas.display();
    line[0].position = sf::Vector2f(currentPos);
  } else {
    line[1].position = sf::Vector2f(currentPos);
    line[1].color = color;
    canvas.draw(line, 2, sf::Lines);
    canvas.display();
  }
}

void drawBrush(sf::RenderTexture &canvas, sf::Color &color,
               sf::Vector2f currentPos, float thickness) {
  brush.setRadius(thickness);
  brush.setPointCount(100);
  brush.setFillColor(color);
  brush.setOrigin(thickness, thickness);
  brush.setPosition(currentPos);
  canvas.draw(brush);
  canvas.display();
}

void drawLine(sf::RenderTexture &canvas, sf::Color &color,
              sf::Vector2i currentPos, float thickness) {
  if (thickness <= 1) {
    if (firstPoint) {
      line[0].position = sf::Vector2f(currentPos);
      line[1].position = sf::Vector2f(currentPos);
      line[0].color = color;
      line[1].color = color;
      firstPoint = false;
    } else {
      line[1].position = sf::Vector2f(currentPos);
      firstPoint = true;
      canvas.draw(line, 2, sf::Lines);
      canvas.display();
    }
  } else {
    if (firstPoint) {
      point1 = sf::Vector2f(currentPos);
      firstPoint = false;
    } else {
      tLine.setPosition(point1);
      tLine.setFillColor(color);
      float dx = point1.x - currentPos.x;
      float dy = point1.y - currentPos.y;
      float length = sqrt(dx * dx + dy * dy);
      float rotation = (atan2(dy, dx)) * 180 / PI;
      tLine.setSize(sf::Vector2f(thickness, length));
      tLine.setOrigin(sf::Vector2f(thickness / 2, 0));
      tLine.setRotation(rotation + 90);

      canvas.draw(tLine);
      canvas.display();
      firstPoint = true;
    }
  }
}

void drawRect(sf::RenderTexture &canvas, sf::Color &color,
              sf::Vector2f currentPos, float thickness, bool isFilled,
              int mode) {
  if (mode == 1) {
    point1 = currentPos;
    setR(1);
  } else if (mode == 2) {
    if (isFilled) {
      rect.setFillColor(color);
      rect.setPosition(point1);
      rect.setSize(currentPos - point1);
    } else {
      rect.setPosition(point1 + sf::Vector2f(-thickness, -thickness));
      rect.setSize(currentPos - point1);
      rect.setFillColor(sf::Color::Transparent);
      rect.setOutlineColor(color);
      rect.setOutlineThickness(thickness);
      rect.setOrigin(sf::Vector2f(-thickness, -thickness));
    }
  } else {

    setR(0);
    canvas.draw(rect);
    canvas.display();
  }
}

void drawEllipse(sf::RenderTexture &canvas, sf::Color &color,
                 sf::Vector2f currentPos, float thickness, bool isFilled,
                 bool mode) {

	if (mode) {
		point1 = currentPos;
		setR(2);
	}
  else {

    ellipse.setPointCount(quality);

    if (isFilled) {
      radius_x = (currentPos.x - point1.x) ;
      radius_y = (currentPos.y - point1.y) ;
      ellipse.setFillColor(color);
      ellipse.setPosition(point1 + sf::Vector2f(radius_x, radius_y));
    } else {
      radius_x = (abs(currentPos.x - point1.x) - thickness) ;
      radius_y = (abs(currentPos.y - point1.y) - thickness) ;
     // ellipse.setOrigin(sf::Vector2f(-thickness, -thickness));
      ellipse.setFillColor(sf::Color::Transparent);
      ellipse.setOutlineColor(color);
      ellipse.setOutlineThickness(thickness);
      ellipse.setPosition(point1 + sf::Vector2f(-thickness, -thickness));

      /*  if (point1.x > currentPos.x && point1.y > currentPos.y) {
                      ellipse.setPosition(point1 - sf::Vector2f(radius_x,
        radius_y) - sf::Vector2f(thickness, thickness)); } else if (point1.y >
        currentPos.y) { ellipse.setPosition(point1 + sf::Vector2f(radius_x, -2 *
        radius_y) + sf::Vector2f(thickness, thickness)); } else if (point1.x >
        currentPos.x && point1.y < currentPos.y) { ellipse.setPosition(point1
        + sf::Vector2f(-1.f * radius_x, radius_y) + sf::Vector2f(-1.f *
        thickness, thickness)); } else { ellipse.setPosition(point1 +
        sf::Vector2f(radius_x, radius_y) + sf::Vector2f(thickness,
        thickness));
        } */
    }

    for (unsigned int i = 0; i < quality; ++i) {
      float rad = (360.f / quality * i) / (360 / PI / 2);
      float x = cos(rad) * radius_x;
      float y = sin(rad) * radius_y;
      ellipse.setPoint(i, sf::Vector2f(x, y));
    };

    radius_x = (currentPos.x - point1.x + 2* thickness) / 2.f;
    radius_y = (currentPos.y - point1.y +  2*thickness) / 2.f;
   
    ellipse.setFillColor(sf::Color::Transparent);
    ellipse.setOutlineColor(color);
    ellipse.setOutlineThickness(thickness);
    ellipse.setPosition(point1 + sf::Vector2f(-thickness, -thickness));
	ellipse.setOrigin(sf::Vector2f(-thickness, -thickness));
    setR(2);

    //canvas.draw(ellipse);
   // canvas.display();
  }
}

void renderOnScreen(sf::RenderWindow &mWindow, sf::RenderWindow &toolWindow,
                    sf::Sprite &mainSprite, sf::Sprite &toolSprite,
                    std::vector<SliderSFML> &vecSlider,
                    std::vector<ButtonSFML> vecButtons) {

  mWindow.clear();
  mWindow.draw(mainSprite);
  if (RT == 1) {
    mWindow.draw(rect);
  } else if (RT == 2) {
    mWindow.draw(ellipse);
  }
  mWindow.display();

  toolWindow.clear();
  toolWindow.draw(toolSprite);
  for (auto &i : vecSlider) {
    i.draw(toolWindow);
  }
  for (auto &i : vecButtons) {
    i.draw(toolWindow);
  }

  toolWindow.display();
}

void setR(int type) { RT = type; }

void slidersInit(std::vector<SliderSFML> &vecSlider, const sf::Color &color,
                 const float &thickness) {
  for (auto &i : vecSlider) {
    i.create(0, 255);
  }
  vecSlider.at(4).create(0, 100);
  vecSlider.at(0).setSliderValue(color.r);
  vecSlider.at(1).setSliderValue(color.g);
  vecSlider.at(2).setSliderValue(color.b);
  vecSlider.at(3).setSliderValue(color.a);
  vecSlider.at(4).setSliderValue(thickness);

  vecSlider.at(0).setAxisColor(sf::Color::Red);
  vecSlider.at(1).setAxisColor(sf::Color::Green);
  vecSlider.at(2).setAxisColor(sf::Color::Blue);
  vecSlider.at(3).setAxisColor(sf::Color::White);
}
void slidersRender(std::vector<SliderSFML> &vecSlider, sf::Color &color,
                   float &thickness) {
  thickness = vecSlider.at(4).getSliderValue();
  color.r = vecSlider.at(0).getSliderValue();
  color.g = vecSlider.at(1).getSliderValue();
  color.b = vecSlider.at(2).getSliderValue();
  color.a = vecSlider.at(3).getSliderValue();
}

int lastResult;

void buttonHandler(sf::RenderWindow& mWindow, sf::RenderTexture& mainCanvas, sf::Vector2f pos, std::vector<ButtonSFML> &vecButtons,
                   int &currentTool, bool &isErasing, bool& isSaved,bool &isFilled) {

  for (auto &i : vecButtons) {
    if (i.getGlobalBounds().contains(pos)) {
      lastResult = i.buttonPressed();
    }
  }

  if (lastResult == 5) {//for eraser
    isErasing = true;
    currentTool = 2;
  } else if(lastResult == 6){//for save button
	  saveFile(mWindow);
	  isSaved = true;
  }
  else if (lastResult == 7) { //openFile
	  openFile(mainCanvas);
  }
  else if (lastResult == 8) { //Filled/NotFilled
	  isFilled = vecButtons.at(8).getOn();
	  if (isFilled) {
		//  vecButtons.at(8).setTexture
	  }
  }
  else {
	  currentTool = lastResult;
  }
}

void saveFile(sf::RenderWindow& mainWindow) {
	char const* filterPatterns[2] = { "*.png", "*.jpg" };
	char const* saveFile = tinyfd_saveFileDialog("Save File", "\\default.png", 2,
		filterPatterns, NULL);

	sf::Vector2u windowSize = mainWindow.getSize();
	sf::Texture texture;
	texture.create(windowSize.x, windowSize.y);
	texture.update(mainWindow);
	sf::Image screenshot = texture.copyToImage();
	screenshot.saveToFile(saveFile);
}


sf::Texture buttonOn;
sf::Image helpingTouch;
void openFile( sf::RenderTexture &mainCanvas) {
	char const* filterPatterns[2] = { "*.png", "*.jpg" };
	char const* fileAdress = tinyfd_openFileDialog("Open file", "\\default.png", 2, filterPatterns, NULL, 0);
	sf::Texture texture;
	texture.loadFromFile(fileAdress);
	sf::Sprite sprite;
	sprite.setTexture(texture);
	mainCanvas.draw(sprite);
	mainCanvas.display();
}
