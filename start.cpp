#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <iostream>
#include <cmath>
#include "other.h"

// g++ -std=c++11 start.cpp -o start -lsfml-graphics -lsfml-window -lsfml-system && ./start

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Welcome to Caro Game || Developed by Thien and Long || Good luck buddy !!");

    centerWindow(window);

    sf::Font font = loadFont();

    sf::Text text("Start", font, 40), leaders_text("Leader Board", font, 23);
    sf::Text Caro_text("CARO GAME", font, 100);
    Caro_text.setFillColor(sf::Color::White);
    text.setFillColor(sf::Color::White);
    leaders_text.setFillColor(sf::Color::White);

    sf::Clock clock; // Create a clock object

    // Center the button and text in the window
    float centerX = 0.0f; // Starting from the left edge
    float centerY = (window.getSize().y - text.getGlobalBounds().height) / 2.0f;

    // Create a button covering the entire width and height of the text
    sf::RectangleShape button(sf::Vector2f(window.getSize().x, text.getGlobalBounds().height*10/6.0));
    button.setPosition(centerX, centerY);
    button.setFillColor(sf::Color(100, 100, 100)); // Gray color for the button

    // Create a button covering the entire width and height of the leader text
    sf::RectangleShape leaders_button(sf::Vector2f(window.getSize().x, leaders_text.getGlobalBounds().height*10.0/6.0));
    leaders_button.setPosition(centerX, centerY + 100);
    leaders_button.setFillColor(sf::Color(100, 100, 100)); // Gray color for the button


    

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                // Check if the mouse click is inside the button
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                if (button.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
                    window.close();
                    // system("g++ -std=c++11 main.cpp  material.cpp game.cpp -o game -L/usr/local/lib -lglfw -lGL -lGLEW && ./game");
                    system("./sign_in");
                } else if (leaders_button.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
                       window.close();
                    // system("g++ -std=c++11 main.cpp  material.cpp game.cpp -o game -L/usr/local/lib -lglfw -lGL -lGLEW && ./game");
                    system("./leader_board");
                }
            }
            
        }

        // Oscillating motion for a simple 3D effect
        float amplitude = 100.0f; // Adjust the amplitude for desired effect
        float frequency = 2.0f;  // Adjust the frequency for desired speed
        float offsetX = amplitude * std::sin(frequency * clock.getElapsedTime().asSeconds());

        // Draw the text on the button with the oscillating motion
        text.setPosition((window.getSize().x - text.getGlobalBounds().width) / 2 + offsetX, centerY);
        leaders_text.setPosition((window.getSize().x - leaders_text.getGlobalBounds().width) / 2 + offsetX, centerY + 3.1*text.getGlobalBounds().height);
        Caro_text.setPosition((window.getSize().x - Caro_text.getGlobalBounds().width)/2.0, centerY - 5*text.getGlobalBounds().height);

        window.clear();

        // Draw the button
        window.draw(button);
        window.draw(leaders_button);
        window.draw(Caro_text);

        // Draw the text
        window.draw(text);
        window.draw(leaders_text);

        window.display();
    }
    
    return 0;
}


