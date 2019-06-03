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
#define FPS 4000

sf::RenderWindow mainWindow(sf::VideoMode(windowWidth, windowHeight),
                            "MainWindow");

sf::RenderWindow toolWindow(sf::VideoMode(toolWindowWidth, toolWindowHeight),
                            "Tool window",
                            sf::Style::Titlebar | sf::Style::Close);

sf::Image image, mButtonImage;
sf::Texture canvasHelp, assistTexture, pencilIcon, brushIcon, lineIcon,
    eraserIcon;
sf::Sprite mainSprite, toolSprite;
sf::RenderTexture mainCanvas, toolCanvas;

SliderSFML sliderThickness(20, toolWindowHeight * 18 / 32);
SliderSFML sliderRed(20, toolWindowHeight * 21 / 32);
SliderSFML sliderBlue(20, toolWindowHeight * 24 / 32);
SliderSFML sliderGreen(20, toolWindowHeight * 27 / 32);
SliderSFML sliderAlpha(20, toolWindowHeight * 30 / 32);

std::vector<SliderSFML> vecSlider{sliderRed, sliderBlue, sliderGreen,
                                  sliderAlpha, sliderThickness};

sf::Color currentColor(0, 0, 0, 255); // Color that user's chosen
sf::Color erasingColor(255, 255, 255, 255);
sf::Color toolColor(105, 105, 105);
int currentTool = 1;  // instrument that is currently chosen
float thickness = 20; // line thickness, brush size, or outline thickness
bool isFilled = true; // if false, thickness = outline thickness
bool isErasing = false;
bool isSaved = false; // Checking whether the image is save already
sf::View deltaView;

void mWindowInputHandler(); // functions decalring
void tWindowInputHandler(std::vector<ButtonSFML> &vecButtons);

int main() {

  mainWindow.setFramerateLimit(FPS);
  toolWindow.setPosition(mainWindow.getPosition() +
                         sf::Vector2i(mainWindow.getSize().x, 0));

  const std::string notext = "NOTEXT";

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
                           120.f, 48.f, false, false, 4,
                           std::string("Ellipse"));
  buttonEllipse.setTextPosition(buttonEllipse.getPosition() +
                                sf::Vector2f(20, 8));
  buttonEllipse.setTexture(&assistTexture);
  ButtonSFML buttonSave(toolWindowWidth / 20, toolWindowHeight * 12 / 32, 64.f,
                        48.f, false, false, 6, std::string("Save"));
  buttonSave.setTextPosition(buttonSave.getPosition() + sf::Vector2f(4, 10));
  buttonSave.setTexture(&assistTexture);
  ButtonSFML buttonOpen(toolWindowWidth * 8 / 20, toolWindowHeight * 12 / 32,
                        64.f, 48.f, false, false, 7, std::string("Open"));
  buttonOpen.setTextPosition(buttonOpen.getPosition() + sf::Vector2f(3, 10));
  buttonOpen.setTexture(&assistTexture);
  ButtonSFML buttonFilled(toolWindowWidth / 20, toolWindowHeight * 8 / 32,
                          120.f, 48.f, true, true, 8, std::string("Filled"));
  buttonFilled.setTextPosition(buttonFilled.getPosition() + sf::Vector2f(4, 8));
  ButtonSFML buttonSelect(toolWindowWidth * 10 / 20, toolWindowHeight * 8 / 32,
                          120.f, 48.f, false, false, 9,
                          std::string("Selection"));
  buttonSelect.setTextPosition(buttonSelect.getPosition() + sf::Vector2f(4, 8));
  buttonSelect.setTexture(&assistTexture);

  std::vector<ButtonSFML> vecButtons{
      buttonPencil, buttonLine, buttonBrush, buttonRect,   buttonEllipse,
      buttonEraser, buttonSave, buttonOpen,  buttonFilled, buttonSelect};

  image.create(1920, 1080, sf::Color::White);
  canvasHelp.loadFromImage(image);
  toolCanvas.create(toolWindowWidth, toolWindowHeight);
  toolCanvas.clear(toolColor);
  toolSprite.setTexture(toolCanvas.getTexture(), true);
  mainCanvas.create(1920, 1080);
  mainCanvas.clear(sf::Color::White);
  mainCanvas.setSmooth(true);
  mainSprite.setTexture(mainCanvas.getTexture(), true);

  slidersInit(vecSlider, currentColor,
              thickness); // set sliders to currentColor and thickness
  init(vecButtons.at(8)); // for IsFilledButton initialization
  mainWindow.setKeyRepeatEnabled(true);

  while (mainWindow.isOpen()) {
    slidersRender(vecSlider, currentColor,
                  thickness);        // Rendering the sliders in the tool Window
    mWindowInputHandler();           // any action done on mainWindow
    tWindowInputHandler(vecButtons); // any action done on toolWindow
    renderOnScreen(mainWindow, toolWindow, mainSprite, toolSprite, vecSlider,
                   vecButtons); // Every frame render main window && toolWindow
  }
  return 0;
}
void tWindowInputHandler(std::vector<ButtonSFML> &vecButtons) {
  sf::Event event2;
  if (toolWindow.pollEvent(event2)) {
    if (event2.type == sf::Event::Closed) {
      toolWindow.close();
    } else if (event2.type == sf::Event::MouseButtonPressed) {
      buttonHandler(mainWindow, mainCanvas,
                    sf::Vector2f(sf::Mouse::getPosition(toolWindow)),
                    vecButtons, currentTool, isErasing, isSaved, isFilled);
      mainWindow.requestFocus();
    }
  }
}
void mWindowInputHandler() {
  sf::Event event;
  while (mainWindow.pollEvent(event)) {
    mainWindow.requestFocus();
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
      } else {
        mainWindow.close();
      }

    } else if ((event.type ==
                sf::Event::MouseMoved) && // MouseMoved and leftClickHeld
               sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      isSaved = false;
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
                    sf::Vector2f(sf::Mouse::getPosition(mainWindow)), thickness,
                    isFilled, 2);
        break;
      }
      }
    } else if (event.type == sf::Event::MouseButtonPressed) {
      isSaved = false;
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
                    sf::Vector2f(sf::Mouse::getPosition(mainWindow)), thickness,
                    isFilled, 1);
        break;
      }
      case 9: {
        select(mainWindow, sf::Vector2f(sf::Mouse::getPosition(mainWindow)),
               true);
        break;
      }
      }
    } else if (event.type == sf::Event::MouseButtonReleased) {
      isSaved = false;
      switch (currentTool) {
      case 3: {
        drawRect(mainCanvas, currentColor,
                 sf::Vector2f(sf::Mouse::getPosition(mainWindow)), thickness,
                 isFilled, 3);
        break;
      }
      case 4: {
        drawEllipse(mainCanvas, currentColor,
                    sf::Vector2f(sf::Mouse::getPosition(mainWindow)), thickness,
                    isFilled, 3);
        break;
      }
      case 9: {
        select(mainWindow, sf::Vector2f(sf::Mouse::getPosition(mainWindow)),
               false);
        break;
      }
      }
    } else if (event.type == sf::Event::KeyPressed &&
               event.key.code == sf::Keyboard::C) {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
        copy(mainWindow);
        std::cout << "copy" << std::endl;
      }
    } else if (event.type == sf::Event::KeyPressed &&
               event.key.code == sf::Keyboard::X) {

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
        isSaved = false;
        cut(mainWindow, mainCanvas);
        std::cout << "cut" << std::endl;
      }
    } else if (event.type == sf::Event::KeyPressed &&
               event.key.code == sf::Keyboard::V) {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
        isSaved = false;
        paste(mainWindow, sf::Vector2f(sf::Mouse::getPosition(mainWindow)),
              mainCanvas);
      }
    } else if (event.type == sf::Event::KeyPressed) {
      // get the current mouse position in the window
      // convert it to world coordinates
		deltaView = mainWindow.getView();  //getting the old view in the delta view
      if (event.key.code == sf::Keyboard::Equal) {
        sf::Vector2f worldPos =
            mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow));
        deltaView.zoom(0.75);
        deltaView.setCenter(worldPos);
      } else if (event.key.code == sf::Keyboard::Hyphen) {
        sf::Vector2f worldPos =
            mainWindow.mapPixelToCoords(sf::Mouse::getPosition(mainWindow));
        deltaView = mainWindow.getView();
        deltaView.zoom(1.25);
        deltaView.setCenter(worldPos);
      } else if (event.key.code == sf::Keyboard::Right)
        deltaView.move(10, 0);
      else if (event.key.code == sf::Keyboard::Left)
        deltaView.move(-10, 0);
      else if (event.key.code == sf::Keyboard::Up)
        deltaView.move(0, -10);
      else if (event.key.code == sf::Keyboard::Down)
        deltaView.move(0, 10);
      else if (event.key.code == sf::Keyboard::R) {
        deltaView = mainWindow.getDefaultView();
        mainWindow.setView(deltaView);
      }

      mainWindow.setView(deltaView);  //setting the changed view
    } else if (event.type == sf::Event::Resized) {
      sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
      mainWindow.setView(sf::View(visibleArea));
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::T) &&
               !toolWindow.isOpen()) {
      toolWindow.create(sf::VideoMode(toolWindowWidth, toolWindowHeight),
                        "Tool window", sf::Style::Titlebar | sf::Style::Close);
      toolWindow.setPosition(mainWindow.getPosition() +
                             sf::Vector2i(mainWindow.getSize().x, 0));
      slidersInit(vecSlider, currentColor, thickness);
    }
  }
}
