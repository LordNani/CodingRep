#include "Tools.h"
#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>
#include <list>
#include <vector>

int main(){
while (window.isOpen())
{

	while (window.pollEvent(event))
	{

		int mouseButtonX = event.mouseButton.x;
		int mouseButtonY = event.mouseButton.y;

		int mouseMoveX = event.mouseMove.x;
		int mouseMoveY = event.mouseMove.y;
		

		setBrushSize(5);

		brush.setRadius(brushSize);
		brush.setPosition(mouseMoveX - brushSize, mouseMoveY - brushSize);
		brush.setFillColor(sf::Color::Transparent);
		brush.setOutlineColor(sf::Color::Green);
		brush.setOutlineThickness(2);

		switch (event.type) {
		case (sf::Event::Closed):
			window.close();
			break;

		case (sf::Event::KeyPressed):
			if (event.key.control && event.key.code == sf::Keyboard::X) {
				cout << "closing";

				window.close();
			}

			if (event.key.code == sf::Keyboard::R) {
				cout << "printed";
				brushColor = setBrushColor(255, 0, 0);
			}
			if (event.key.code == sf::Keyboard::G) {
				brushColor = setBrushColor(0, 255, 0);
			}
			if (event.key.code == sf::Keyboard::B) {
				brushColor = setBrushColor(0, 0, 255);
			}
			if (event.key.code == sf::Keyboard::C) {
				for (int i = 0; i < points.size(); i++) {
					points.clear();
				}
				it = 0;
			}
			break;

		case(sf::Event::MouseButtonPressed):
			points.push_back(point);
			points[it].setRadius(brushSize);
			points[it].setFillColor(brushColor);
			points[it].setPosition(mouseButtonX - brushSize, mouseButtonY - brushSize);
			it++;
			cout << "drawPoint: Pressed X = " << mouseButtonX << " Y = " << mouseButtonY << endl;

			break;

		case(sf::Event::MouseMoved):
			points.push_back(point);
			points[it].setRadius(brushSize);
			points[it].setFillColor(brushColor);
			points[it].setPosition(mouseMoveX - brushSize, mouseMoveY - brushSize);
			it++;
			cout << "drawPoint: Moved X = " << mouseMoveX << " Y = " << mouseMoveY << endl;
			break;
		}
	}window.clear(sf::Color(255, 247, 204));
	window.draw(SkechyT);
	window.draw(close);
	window.draw(brush);
	window.draw(color);
	window.draw(clear); for (int i = 0; i < points.size(); i++) {
		window.draw(points[i]);
	}

	//window.draw(point);

	window.display();
}
}int getBrushSize() {
	return brushSize;
}

void setBrushSize(int num) {
	brushSize = num;

}

sf::Color setBrushColor(int r, int g, int b) {
	return sf::Color(r, g, b);
}

~Visualizer();
};

-2
c++sfml
РЕШЕНИЕ
Хотя вы можете изменить sf::VertexArray на лету(в основном создание приложения для векторного рисования), вы также можете использовать sf::RenderTexture как фактический рисунок холста.

Учитывая, что вы пытались нарисовать много маленьких точек, я предполагаю, что вы стремитесь к последнему.Здесь важно то, что вам не обязательно очищать текстуры рендеринга между вызовами рисования, и поэтому вы можете сохранить все, что было нарисовано ранее.

В сочетании с первоначальной целью — рисованием — это становится очень легко.

Все, что вам нужно сделать, это нарисовать изменения(например, при перемещении курсора), завершить текстуру рендеринга(вызвав display()), а затем представить его, используя любой нарисованный объект(например, sf::Sprite,

	Я быстро набросал следующий пример, который должен довольно хорошо показать концепцию(и вы не столкнетесь с бесконечным циклом, кроме реального основного цикла) :

#include <SFML/Graphics.hpp>
#include <vector>

	int main(int argc, char** argv) {
	sf::RenderWindow window(sf::VideoMode(800, 600), L"SFML Drawing – C to clear, PageUp/PageDown to pick colors", sf::Style::Default);
	// Set a specific frame rate, since we don't want to
	// worry about vsync or the time between drawing iterations
	window.setVerticalSyncEnabled(false);
	window.setFramerateLimit(100);

	// First we'll use a canvas to basically store our image
	sf::RenderTexture canvas;
	canvas.create(800, 600);
	canvas.clear(sf::Color::White);

	// Next we'll need a sprite as a helper to draw our canvas
	sf::Sprite sprite;
	sprite.setTexture(canvas.getTexture(), true);

	// Define some colors to use
	// These are all with very low alpha so we
	// can (over-)draw based on how fast we move the cursor
	const std::vector<sf::Color> colors = {
	sf::Color(255, 0, 0, 8),
	sf::Color(255, 255, 0, 8),
	sf::Color(0, 255, 0, 8),
	sf::Color(0, 255, 255, 8),
	sf::Color(0, 0, 255, 8),
	sf::Color(255, 0, 255, 8)
	};

	// We'll need something to actually draw
	// For simplicity, I'm just drawing a circle shape
	// but you could also draw a line, rectangle, or something more complex
	const float brush_size = 25;
	sf::CircleShape brush(brush_size, 24);
	brush.setOrigin(brush_size, brush_size); // Center on the circle's center

	sf::Vector2f lastPos;
	bool isDrawing = false;
	unsigned int color = 0;

	// Apply some default color
	brush.setFillColor(colors[color]);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				switch (event.key.code) {
				case sf::Keyboard::C:
					// Clear our canvas
					canvas.clear(sf::Color::White);
					canvas.display();
					break;
				case sf::Keyboard::PageUp:
					// Get next color
					color = (color + 1) % colors.size();
					// Apply it
					brush.setFillColor(colors[color]);
					break;
				case sf::Keyboard::PageDown:
					// Get previous color
					color = (color - 1) % colors.size();
					// Apply it
					brush.setFillColor(colors[color]);
					break;
				}
				break;
			case sf::Event::Resized:
			{
				// Window got resized, update the view to the new size
				sf::View view(window.getView());
				const sf::Vector2f size(window.getSize().x, window.getSize().y);
				view.setSize(size); // Set the size
				view.setCenter(size / 2.f); // Set the center, moving our drawing to the top left
				window.setView(view); // Apply the view
				break;
			}
			case sf::Event::MouseButtonPressed:
				// Only care for the left button
				if (event.mouseButton.button == sf::Mouse::Left) {
					isDrawing = true;
					// Store the cursor position relative to the canvas
					lastPos = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });

					// Now let's draw our brush once, so we can
					// draw dots without actually draging the mouse
					brush.setPosition(lastPos);

					// Draw our "brush"canvas.draw(brush);

					// Finalize the texture
					canvas.display();
				}
				break;
			case sf::Event::MouseButtonReleased:
				// Only care for the left button
				if (event.mouseButton.button == sf::Mouse::Left)
					isDrawing = false;
				break;
			case sf::Event::MouseMoved:
				if (isDrawing)
				{
					// Calculate the cursor position relative to the canvas
					const sf::Vector2f newPos(window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y)));

					// I'm only using the new position here
					// but you could also use `lastPos` to draw a
					// line or rectangle instead
					brush.setPosition(newPos);

					// Draw our "brush"canvas.draw(brush);

					// Finalize the texture
					canvas.display();
					break;
				}
			}
		}

		// Clear the window
		window.clear(sf::Color(64, 64, 64));

		// Draw our canvas
		window.draw(sprite);

		// Show the window
		window.display();
	}

	return 0;
}
}