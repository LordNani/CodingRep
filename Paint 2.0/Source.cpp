
#include "Tools.h"
#include <SFML\Graphics.hpp>
#include "SFML\Main.hpp"
#include <SFML\Window.hpp>
#include <array>
#include <vector>
#define windowHeight 768
#define windowWidth 1024
#define toolWindowWidth 320
#define toolWindowHeight 600

int main() {
  sf::RenderWindow mainWindow(sf::VideoMode(windowWidth, windowHeight),
                              "MainWindow");
  mainWindow.setFramerateLimit(2000);
  sf::RenderWindow toolWindow(sf::VideoMode(toolWindowWidth, toolWindowHeight),
                              "Tool window");
  sf::Image image;
  sf::Texture canvasHelp;
  sf::Sprite mainSprite, toolSprite;
  sf::RenderTexture mainCanvas, toolCanvas;
  /*
  SliderSFML sliderRed(20, 320 * 8 / 16);
  SliderSFML sliderBlue(20, 320 * 10 / 16);
  SliderSFML sliderGreen(20, 320 * 12 / 16);
  SliderSFML sliderAlpha(20, 320 * 14 / 16);
  SliderSFML sliderThickness(20, 320 * 6 / 16); 

  std::vector<SliderSFML> vecSlider{sliderRed, sliderBlue, sliderGreen,
                                    sliderAlpha, sliderThickness}; */

  sf::Color currentColor(0, 0, 0, 255); // Color that user's chosen
  sf::Color toolColor(105, 105, 105);
  int currentTool = 0;   // instrument that is currently chosen
  float thickness = 40;  // line thickness, brush size, or outline thickness
  bool isFilled = false; // if false, thickness = outline thickness

  sf::Vector2i prevPos;

  image.create(1920, 1080, sf::Color::White);
  canvasHelp.loadFromImage(image);
  toolCanvas.create(toolWindowWidth, toolWindowHeight);
  toolCanvas.clear(toolColor);
  toolSprite.setTexture(toolCanvas.getTexture(), true);
  mainCanvas.create(1920, 1080);
  mainCanvas.clear(sf::Color::White);
  mainCanvas.setSmooth(true);
  mainSprite.setTexture(mainCanvas.getTexture(), true);

  //slidersInit(vecSlider, currentColor, thickness);
  while (mainWindow.isOpen()) {
    // canvasHelp.loadFromImage(image);
    slidersRender(vecSlider, currentColor, thickness);
    sf::Event event;
    while (mainWindow.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        mainWindow.close();

      else if ((event.type == sf::Event::MouseMoved) &&
               sf::Mouse::isButtonPressed(
                   sf::Mouse::Left)) // MouseMoved and leftClickHeld
      {
        switch (currentTool) {
        case 0: {
          drawPencil(currentColor, sf::Mouse::getPosition(mainWindow), 0,
                     mainCanvas);
          break;
        }
        case 2: {
          drawBrush(mainCanvas, currentColor,
                    sf::Vector2f(sf::Mouse::getPosition(mainWindow)),
                    thickness);
          break;
        }
        case 3: {
          drawRect(mainCanvas, currentColor,
                   sf::Vector2f(sf::Mouse::getPosition(mainWindow)), thickness,
                   isFilled, 2);
          break;
        }
        }
      } else if (event.type == sf::Event::MouseButtonPressed) {
        switch (currentTool) {
        case 0: {
          drawPencil(currentColor, sf::Mouse::getPosition(mainWindow), 1,
                     mainCanvas);
          break;
        }
        case 1: {
          drawLine(mainCanvas, currentColor, sf::Mouse::getPosition(mainWindow),
                   thickness);
          break;
        }
        case 2: {
          drawBrush(mainCanvas, currentColor,
                    sf::Vector2f(sf::Mouse::getPosition(mainWindow)),
                    thickness);
          break;
        }
        case 3: {
          drawRect(mainCanvas, currentColor,
                   sf::Vector2f(sf::Mouse::getPosition(mainWindow)), thickness,
                   isFilled, 1);
          break;
        }
        case 4: {
          drawEllipse(mainCanvas, currentColor,
                      sf::Vector2f(sf::Mouse::getPosition(mainWindow)),
                      thickness, isFilled, true);
          break;
        }
        }
      } else if (event.type == sf::Event::MouseButtonReleased) {
        switch (currentTool) {
        case 0: {
          break;
        }
        case 3: {
          drawRect(mainCanvas, currentColor,
                   sf::Vector2f(sf::Mouse::getPosition(mainWindow)), thickness,
                   isFilled, 3);
          break;
        }
        case 4: {
          drawEllipse(mainCanvas, currentColor,
                      sf::Vector2f(sf::Mouse::getPosition(mainWindow)),
                      thickness, isFilled, false);
          break;
        }
        }

      } else if (event.type == sf::Event::Resized) {
        sf::View view(mainWindow.getView());
        const sf::Vector2f size(mainWindow.getSize().x, mainWindow.getSize().y);
        view.setSize(size);         // Set the size
        view.setCenter(size / 2.f); // moving our drawing to the top left
        mainWindow.setView(view);   // Apply the view
      }
    }

    /*  sf::RectangleShape test(
          sf::Vector2f(400, 200)); // start of test rect in the middle
      test.setPosition(windowWidth / 2 - test.getSize().x / 2,
                       windowHeight / 2 - test.getSize().y / 2);
      test.setFillColor(sf::Color::Transparent);
      test.setOutlineThickness(2.f);
      test.setOutlineColor(sf::Color::Black);
      mainCanvas.draw(test);
      mainCanvas.display(); // end of it.*/

    renderOnScreen(mainWindow, toolWindow, mainSprite, toolSprite,
                   vecSlider); // Every frame render main window && toolWindow
  }

  return 0;
}
