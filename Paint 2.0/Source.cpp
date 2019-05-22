#include <SFML/Graphics.hpp>

#include <vector>

	void drawOnImage(sf::Color color, int tool, sf::Texture canvas, sf::Image &image, sf::Vector2i vector);

	int main()
	{
		int windowHeight, windowWidth; //Window size that is specified by user's input to GUI
		windowHeight = 600;
		windowWidth = 800;
		// create the window
		sf::RenderWindow mainWindow(sf::VideoMode(windowWidth, windowHeight), "MainWindow");
		sf::Image image;
		image.create(windowWidth, windowHeight, sf::Color::White);
		sf::Texture canvas;
		sf::Color currentColor = sf::Color::Black;  // Color that user's chosen
		int currentTool = 0; // instrument that is currently chosen
		sf::Sprite sprite;
		int mousedown = 0;
		mainWindow.setFramerateLimit(30);
		canvas.loadFromImage(image);
		sprite.setTexture(canvas);

		while (mainWindow.isOpen())
		{
			canvas.loadFromImage(image);
			sf::Event event;
			while (mainWindow.pollEvent(event))
			{
				// "close requested" event: we close the window
				if (event.type == sf::Event::Closed)
					mainWindow.close();
				else if ((event.type == sf::Event::MouseMoved) && (mousedown == 1)) // MouseMoved and leftClickHeld
				{
					
					
					drawOnImage(currentColor, currentTool, canvas, image, sf::Mouse::getPosition(mainWindow));
				}
				else if (event.type == sf::Event::MouseButtonPressed)
				{
					mousedown = 1;
					drawOnImage(currentColor, currentTool, canvas, image, sf::Mouse::getPosition(mainWindow));
					
				}
				else if (event.type == sf::Event::MouseButtonReleased)
				{
					mousedown = 0;
					canvas.update(mainWindow);

				}
			}
			mainWindow.clear();
			mainWindow.draw(sprite);
			mainWindow.display();


		}

		return 0;
	}

	void drawOnImage(sf::Color color, int tool, sf::Texture canvas, sf::Image &image, sf::Vector2i vector) {
		if (tool == 0) {
			image.setPixel(vector.x, vector.y, color);
			
		}
	}
