
#include "ButtonSFML.h"
#include "Tools.h"
#include <SFML\Config.hpp>
#include <SFML\Graphics.hpp>
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
                              "Tool window",
                              sf::Style::Titlebar | sf::Style::Close);
  toolWindow.setPosition(mainWindow.getPosition() +
                         sf::Vector2i(mainWindow.getSize().x, 0));
  sf::Image image;
  sf::Texture canvasHelp;
  sf::Sprite mainSprite, toolSprite;
  sf::RenderTexture mainCanvas, toolCanvas;

  SliderSFML sliderThickness(20, toolWindowHeight * 7 / 16);
  SliderSFML sliderRed(20, toolWindowHeight * 9 / 16);
  SliderSFML sliderBlue(20, toolWindowHeight * 11 / 16);
  SliderSFML sliderGreen(20, toolWindowHeight * 13 / 16);
  SliderSFML sliderAlpha(20, toolWindowHeight * 15 / 16);
  std::vector<SliderSFML> vecSlider{sliderRed, sliderBlue, sliderGreen,
                                    sliderAlpha, sliderThickness};
  std::string test = "NOTEXT";
  sf::Texture pencilIcon;
  sf::Texture* help = &pencilIcon;

 
  pencilIcon.loadFromFile("pencil.png");
  ButtonSFML buttonPencil(toolWindowWidth / 4, toolWindowHeight * 1 / 16, 64.f,
                          64.f, true, true, 0, test);
  buttonPencil.setTexture(help);
  
  std::vector<ButtonSFML> vecButtons{ buttonPencil };

  sf::Color currentColor(0, 0, 0, 255); // Color that user's chosen
  sf::Color toolColor(105, 105, 105);
  int currentTool = 3;   // instrument that is currently chosen
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

  sf::Sprite texture;
  sf::RectangleShape shape();

  slidersInit(vecSlider, currentColor,
              thickness); // set sliders to currentColor and thickness
  while (mainWindow.isOpen()) {
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
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::T) &&
                 !toolWindow.isOpen()) {
        std::cout << "T is pressed";
        toolWindow.create(sf::VideoMode(toolWindowWidth, toolWindowHeight),
                          "Tool window",
                          sf::Style::Titlebar | sf::Style::Close);
        toolWindow.setPosition(mainWindow.getPosition() +
                               sf::Vector2i(mainWindow.getSize().x, 0));
        slidersInit(vecSlider, currentColor, thickness);
      }
    }

    sf::Event event2;
    if (toolWindow.pollEvent(event2)) {
      if (event2.type == sf::Event::Closed) {
        toolWindow.close();
      } else if (event.type == sf::Event::MouseButtonPressed) {
        buttonHandler(sf::Vector2f(sf::Mouse::getPosition()), vecButtons,
                      currentTool);
      }
    }

    renderOnScreen(mainWindow, toolWindow, mainSprite, toolSprite, vecSlider,
                   vecButtons); // Every frame render main window && toolWindow
  }

  return 0;
}


