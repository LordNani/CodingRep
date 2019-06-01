#include "ButtonSFML.h"
#include "Tools.h"
#include "tinyfiledialogs.h"
#include <SFML\Config.hpp>
#include <SFML\Graphics.hpp>
#include <array>
#include <vector>
#define windowHeight 768
#define windowWidth 1024
#define toolWindowWidth 320
#define toolWindowHeight 600

void saveFile(sf::RenderWindow &mainWindow);

int main() {
  sf::RenderWindow mainWindow(sf::VideoMode(windowWidth, windowHeight),
                              "MainWindow");
  mainWindow.setFramerateLimit(8000);
  sf::RenderWindow toolWindow(sf::VideoMode(toolWindowWidth, toolWindowHeight),
                              "Tool window",
                              sf::Style::Titlebar | sf::Style::Close);
  toolWindow.setPosition(mainWindow.getPosition() +
                         sf::Vector2i(mainWindow.getSize().x, 0));
  sf::Image image, mButtonImage;
  sf::Texture canvasHelp, assistTexture, pencilIcon, brushIcon, lineIcon,
      eraserIcon;
  sf::Sprite mainSprite, toolSprite;
  sf::RenderTexture mainCanvas, toolCanvas;
  const std::string notext = "NOTEXT";

  SliderSFML sliderThickness(20, toolWindowHeight * 18 / 32);
  SliderSFML sliderRed(20, toolWindowHeight * 21 / 32);
  SliderSFML sliderBlue(20, toolWindowHeight * 24 / 32);
  SliderSFML sliderGreen(20, toolWindowHeight * 27 / 32);
  SliderSFML sliderAlpha(20, toolWindowHeight * 30 / 32);
  std::vector<SliderSFML> vecSlider{sliderRed, sliderBlue, sliderGreen,
                                    sliderAlpha, sliderThickness};
  // Preparing icons for buttonsSFML
  pencilIcon.loadFromFile("icons\\pencil.png");
  pencilIcon.setSmooth(true);
  brushIcon.loadFromFile("icons\\brush.png");
  brushIcon.setSmooth(true);
  lineIcon.loadFromFile("icons\\line.png");
  lineIcon.setSmooth(true);
  eraserIcon.loadFromFile("icons\\eraser.png");
  eraserIcon.setSmooth(true);
  mButtonImage.create(48, 48, sf::Color(211, 211, 211, 255));
  assistTexture.loadFromImage(mButtonImage);

  // INITIALIZING ALL BUTTONS
  ButtonSFML buttonPencil(toolWindowWidth / 20, toolWindowHeight / 32, 48.f,
                          48.f, false, false, 0, notext);
  buttonPencil.setTexture(&pencilIcon);

  ButtonSFML buttonLine(toolWindowWidth * 6 / 20, toolWindowHeight / 32, 48.f,
                        48.f, false, false, 1, notext);
  buttonLine.setTexture(&lineIcon);

  ButtonSFML buttonBrush(toolWindowWidth * 11 / 20, toolWindowHeight / 32, 48.f,
                         48.f, false, false, 2, notext);
  buttonBrush.setTexture(&brushIcon);
  ButtonSFML buttonEraser(toolWindowWidth * 16 / 20, toolWindowHeight / 32,
                          48.f, 48.f, false, false, 5, notext);
  buttonEraser.setTexture(&eraserIcon);

  ButtonSFML buttonRect(toolWindowWidth * 23 / 40, toolWindowHeight * 4 / 32,
                        120.f, 48.f, false, false, 3, std::string("Rectangle"));
  buttonRect.setTexture(&assistTexture);
  buttonRect.setTextPosition(buttonRect.getPosition() + sf::Vector2f(4, 7));
  ButtonSFML buttonEllipse(toolWindowWidth / 20, toolWindowHeight * 4 / 32,
                           120.f, 48.f, false, false, 4, std::string("Ellipse"));
  buttonEllipse.setTextPosition(buttonEllipse.getPosition() +
                                sf::Vector2f(20, 8));
  buttonEllipse.setTexture(&assistTexture);
  ButtonSFML buttonSave(toolWindowWidth / 20, toolWindowHeight * 12 / 32, 64.f,
                        48.f, false, false, 6, std::string("Save"));
  buttonSave.setTextPosition(buttonSave.getPosition() + sf::Vector2f(4, 10));
  buttonSave.setTexture(&assistTexture);
  ButtonSFML buttonOpen(toolWindowWidth *8/ 20, toolWindowHeight * 12 / 32, 64.f,
	  48.f, false, false, 7, std::string("Open"));
  buttonOpen.setTextPosition(buttonOpen.getPosition() + sf::Vector2f(3, 10));
  buttonOpen.setTexture(&assistTexture);
  ButtonSFML buttonFilled(toolWindowWidth / 20, toolWindowHeight * 8 / 32, 72.f,
	  48.f, true, false, 8, std::string("Filled"));
  buttonFilled.setTextPosition(buttonFilled.getPosition() + sf::Vector2f(4, 8));
  buttonFilled.setTexture(&assistTexture);

  std::vector<ButtonSFML> vecButtons{buttonPencil, buttonLine,    buttonBrush,
                                     buttonRect,   buttonEllipse, buttonEraser,
                                     buttonSave,buttonOpen,buttonFilled };

  sf::Color currentColor(0, 0, 0, 255); // Color that user's chosen
  sf::Color erasingColor(255, 255, 255, 255);
  sf::Color toolColor(105, 105, 105);
  int currentTool = 0;   // instrument that is currently chosen
  float thickness = 10;  // line thickness, brush size, or outline thickness
  bool isFilled = true; // if false, thickness = outline thickness
  bool isErasing = false;

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
  bool isSaved = false; // Checking whether the image is save already
  slidersInit(vecSlider, currentColor,
              thickness); // set sliders to currentColor and thickness

  while (mainWindow.isOpen()) {
    slidersRender(vecSlider, currentColor, thickness);
    sf::Event event;
    while (mainWindow.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        if (!isSaved) {
          int var =
              tinyfd_messageBox("ACHTUNG!", "Would you like to save this file?",
                                "yesno", "warning", 1);
          if (var == 0)
            mainWindow.close();
          else {
            saveFile(mainWindow);
			mainWindow.close();
          }
		}
		else {
			mainWindow.close();
		}

      } else if ((event.type ==
                  sf::Event::MouseMoved) && // MouseMoved and leftClickHeld
                 sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        switch (currentTool) {
        case 0: {
          drawPencil(currentColor, sf::Mouse::getPosition(mainWindow), 0,
                     mainCanvas);
          break;
        }
        case 2: {
          if (isErasing)
            drawBrush(mainCanvas, erasingColor,
                      sf::Vector2f(sf::Mouse::getPosition(mainWindow)),
                      thickness);
          else
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
        case 4: {
          drawEllipse(mainCanvas, currentColor,
                      sf::Vector2f(sf::Mouse::getPosition(mainWindow)),
                      thickness, isFilled, false);
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
          if (isErasing)
            drawBrush(mainCanvas, erasingColor,
                      sf::Vector2f(sf::Mouse::getPosition(mainWindow)),
                      thickness);
          else
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
      } else if (event2.type == sf::Event::MouseButtonPressed) {
        buttonHandler(mainWindow, mainCanvas,
                      sf::Vector2f(sf::Mouse::getPosition(toolWindow)),
                      vecButtons, currentTool, isErasing, isSaved,isFilled);
        mainWindow.requestFocus();
      }
    }

    renderOnScreen(mainWindow, toolWindow, mainSprite, toolSprite, vecSlider,
                   vecButtons); // Every frame render main window && toolWindow
  }

  return 0;
}
