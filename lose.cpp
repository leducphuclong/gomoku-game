#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include "other.h"

// g++ -std=c++11 lose.cpp -o lose -lsfml-graphics -lsfml-window -lsfml-system && ./lose

struct Raindrop {
    sf::Vector2f position;
    sf::Vector2f velocity;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Nice try, don't give up too early ok !!");

    centerWindow(window);

    sf::Font font = loadFont();

    sf::Text loseText("LOSE", font, 80); // Larger text
    sf::FloatRect textRect = loseText.getLocalBounds();
    loseText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    loseText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
    loseText.setFillColor(sf::Color::White);

    std::vector<Raindrop> raindrops;

    std::vector<Button_Rectangle> buttons(2);

    // Initialize buttons
    initializeButton(buttons[0], sf::Vector2f(300.0f, 400.0f), sf::Vector2f(120.0f, 50.0f), "Retry", font);
    initializeButton(buttons[1], sf::Vector2f(500.0f, 400.0f), sf::Vector2f(120.0f, 50.0f), "Quit", font);

    // Gravity-like effect
    const float gravity = 1.0f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePosition(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
                for (const auto& button : buttons) {
                    if (button.shape.getGlobalBounds().contains(mousePosition)) {
                        if (button.text.getString() == "Retry") {
                            window.close();
                            system("./x/game");
                        } else if (button.text.getString() == "Quit") {
                            window.close();
                        }
                    }
                }
            }
        }

        // Generate raindrops falling from the top
        Raindrop raindrop;
        raindrop.position = sf::Vector2f(std::rand() % window.getSize().x, 0.0f);
        raindrop.velocity = sf::Vector2f(0.0f, static_cast<float>(std::rand() % 50 + 50));
        raindrops.push_back(raindrop);

        // Update and draw raindrops
        window.clear();

        for (auto& raindrop : raindrops) {
            // Apply gravity-like effect
            raindrop.velocity.y += gravity;

            // Simulate wind effect
            raindrop.velocity.x += static_cast<float>(std::rand() % 5 - 2); // Adjust wind intensity

            raindrop.position.x += raindrop.velocity.x * 0.02;
            raindrop.position.y += raindrop.velocity.y * 0.02;

            sf::CircleShape drop(2.0f);
            drop.setFillColor(sf::Color::White); // Always set to white
            drop.setPosition(raindrop.position);
            window.draw(drop);
        }

        raindrops.erase(std::remove_if(raindrops.begin(), raindrops.end(),
            [&window](const Raindrop& r) { return r.position.y > window.getSize().y; }), raindrops.end());

        // Draw the text
        window.draw(loseText);
        
        // Draw the buttons
        drawButtonsBelowText(buttons, loseText, window);

        // Display the updated frame
        window.display();
    }

    return 0;
}
