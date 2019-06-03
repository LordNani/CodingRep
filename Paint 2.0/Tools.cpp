#include "Tools.h"
#include "SFML/Graphics.hpp"
#include "tinyfiledialogs.h"
#include <cmath>
#define PI 3.1415926535898

sf::Vertex line[2]; // for line
bool firstPoint = true;
sf::RectangleShape tLine;
sf::CircleShape brush;   // brush shape
sf::ConvexShape ellipse; // for ellipse tool
float radius_x;
float radius_y;
float realThickness;
unsigned short const quality = 35; // point Count of convex
sf::Vector2f point1;               // for everything
sf::RectangleShape rect;           // rect tool
sf::Texture buttonOn, assistTexture2, bufferTexture, bufferTexture2,bufferedTexture3;
sf::Image helpingTouch, mButtonImage2,
    bufferImage;                        // helping touch is for buttonBackground
sf::Sprite bufferSprite, bufferSprite2, bufferSprite3; // for anything, used here for
                                        // copypasting, and saving/opening files
sf::IntRect bufferRect;

int RT = 0; // RenderType for real time [0 for nothing, 1 for Rect, and 2 for
            // Ellipse]

void init(ButtonSFML &fillButton) {
  mButtonImage2.create(48, 48, sf::Color(211, 211, 211, 255));
  assistTexture2.loadFromImage(mButtonImage2);
  helpingTouch.create(72, 48, sf::Color::Green);
  buttonOn.loadFromImage(helpingTouch);
  fillButton.setTexture(&buttonOn);

  ellipse.setPointCount(quality);
  brush.setPointCount(quality);
}

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
    RT = 1;
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

    RT = 0;
    canvas.draw(rect);
    canvas.display();
  }
}
void drawEllipse(sf::RenderTexture &canvas, sf::Color &color,
                 sf::Vector2f currentPos, float thickness, bool isFilled,
                 int mode) {

  if (mode == 1) {
    point1 = currentPos;
    RT = 2;
  } else if (mode == 2) {

    if (isFilled) {
      radius_x = (currentPos.x - point1.x) / 2.f;
      radius_y = (currentPos.y - point1.y) / 2.f;
      ellipse.setFillColor(color);
      ellipse.setPosition(point1 + sf::Vector2f(radius_x, radius_y));
    } else {
      radius_x = (abs(currentPos.x - point1.x) - thickness);
      radius_y = (abs(currentPos.y - point1.y) - thickness);
      // ellipse.setOrigin(sf::Vector2f(-thickness, -thickness));
      ellipse.setFillColor(sf::Color::Transparent);
      ellipse.setOutlineColor(color);
      ellipse.setOrigin(sf::Vector2f(-thickness, -thickness));
      ellipse.setOutlineThickness(thickness);
      ellipse.setPosition(point1 + sf::Vector2f(-thickness, -thickness));
    }

    for (float i = 0; i < quality; ++i) {
      float rad = (360.f / quality * i) / (360 / PI / 2);
      float x = cos(rad) * radius_x;
      float y = sin(rad) * radius_y;
      ellipse.setPoint(i, sf::Vector2f(x, y));
    }
  } else {
    RT = 0;
    canvas.draw(ellipse);
    canvas.display();
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

void buttonHandler(sf::RenderWindow &mWindow, sf::RenderTexture &mainCanvas,
                   sf::Vector2f pos, std::vector<ButtonSFML> &vecButtons,
                   int &currentTool, bool &isErasing, bool &isSaved,
                   bool &isFilled) {
  for (auto &i : vecButtons) {
    if (i.getGlobalBounds().contains(pos)) {
      lastResult = i.buttonPressed();
    }
  }

  if (lastResult == 5) { // for eraser
    isErasing = true;
    currentTool = 2;
  } else if (lastResult == 6) { // for save button
    saveFile(mWindow);
    isSaved = true;
  } else if (lastResult == 7) { // openFile
    openFile(mainCanvas);
  } else if (lastResult == 8) { // Filled/NotFilled
    isFilled = vecButtons.at(8).getOn();
    if (isFilled)
      vecButtons.at(8).setText("Filled");
    else
      vecButtons.at(8).setText("Not filled");
    if (isFilled) {
      vecButtons.at(8).setTexture(&buttonOn);
    } else {
      vecButtons.at(8).setTexture(&assistTexture2);
    }
  } else {
    isErasing = false;
    currentTool = lastResult;
  }
}

void saveFile(sf::RenderWindow &mainWindow) {
  char const *filterPatterns[2] = {"*.png", "*.jpg"};
  char const *saveFile = tinyfd_saveFileDialog("Save File", "\\default.png", 2,
                                               filterPatterns, NULL);
  if (saveFile == NULL || saveFile == "cancel") {

  } else {
    sf::Vector2u windowSize = mainWindow.getSize();
    bufferTexture.create(windowSize.x, windowSize.y);
    bufferTexture.update(mainWindow);
    bufferImage = bufferTexture.copyToImage();
    bufferImage.saveToFile(saveFile);
  }
}

void openFile(sf::RenderTexture &mainCanvas) {
  char const *filterPatterns[2] = {"*.png", "*.jpg"};
  char const *fileAdress = tinyfd_openFileDialog("Open file", "\\default.png",
                                                 2, filterPatterns, NULL, 0);
  if (fileAdress == NULL || fileAdress == "cancel") {

  } else {
	bufferedTexture3.loadFromFile(fileAdress);
    bufferSprite3.setTexture(bufferedTexture3);
    mainCanvas.clear(sf::Color::White);
    mainCanvas.draw(bufferSprite3);
    mainCanvas.display();
  }
}

void select(sf::RenderWindow &mainWindow, sf::Vector2f curPos, bool mode) {
  if (mode) {
    point1 = curPos;

  } else {

    if (curPos.x > point1.x)
      if (curPos.y > point1.y) {
        bufferRect.left = point1.x;
        bufferRect.top = point1.y;
      } else {
        bufferRect.left = point1.x;
        bufferRect.top = curPos.y;
      }
    else {
      if (curPos.y > point1.y) {
        bufferRect.left = curPos.x;
        bufferRect.top = point1.y;
      } else {
        bufferRect.left = curPos.x;
        bufferRect.top = curPos.y;
      }
    }
    bufferRect.width = abs(curPos.x - point1.x);
    bufferRect.height = abs(curPos.y - point1.y);
  }
}

void copy(sf::RenderWindow &mainWindow) {
  sf::Vector2u windowSize = mainWindow.getSize();
  bufferTexture.create(windowSize.x, windowSize.y);
  bufferTexture.update(mainWindow);

  bufferSprite.setTexture(bufferTexture);
  bufferSprite.setTextureRect(bufferRect);
}

void cut(sf::RenderWindow &mainWindow, sf::RenderTexture &mainCanvas) {
  sf::Vector2u windowSize = mainWindow.getSize();
  bufferTexture.create(windowSize.x, windowSize.y);
  bufferTexture.update(mainWindow);

  bufferSprite.setTexture(bufferTexture);
  bufferSprite.setTextureRect(bufferRect);

  bufferImage.create(bufferRect.width, bufferRect.height, sf::Color::White);
  bufferTexture2.loadFromImage(bufferImage);
  bufferSprite2.setTexture(bufferTexture2);
  bufferSprite2.setPosition(bufferRect.left, bufferRect.top);
  mainCanvas.draw(bufferSprite2);
  mainCanvas.display();
}

void paste(sf::RenderWindow &mainWindow, sf::Vector2f curPos,
           sf::RenderTexture &mainCanvas) {

  bufferSprite.setPosition(
      curPos - sf::Vector2f(bufferSprite.getTextureRect().width / 2,
                            bufferSprite.getTextureRect().height / 2));
  mainCanvas.draw(bufferSprite);
  mainCanvas.display();
}
