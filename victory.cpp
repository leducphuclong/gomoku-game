#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include "other.h"

// g++ -o victory victory.cpp -lsfml-graphics -lsfml-window -lsfml-system && ./victory  

struct Particle {
    sf::Vector2f position;
    sf::Vector2f velocity;
    float lifetime;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Good Job !");

    centerWindow(window);

    sf::Font font = loadFont();

    sf::Text text("Victory", font, 80); // Larger text
    text.setFillColor(generateRandomColor());

    std::vector<Particle> fireworks;

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Change color every 1 second
    float colorChangeFrequency = 1.0f;
    float colorChangeTimer = colorChangeFrequency;

    // Background rectangle
    sf::RectangleShape background(sf::Vector2f(window.getSize().x, window.getSize().y));
    background.setFillColor(sf::Color::White);

    std::vector<Button_Rectangle> buttons(2);
    // Initialize buttons
    initializeButton(buttons[0], sf::Vector2f(300.0f, 400.0f), sf::Vector2f(120.0f, 50.0f), "Again", font);
    initializeButton(buttons[1], sf::Vector2f(500.0f, 400.0f), sf::Vector2f(120.0f, 50.0f), "Quit", font);
    
    // Back button
    Button_Rectangle back_button;
    initializeButton(back_button, sf::Vector2f(5, 5), sf::Vector2f(120.0f, 50.0f), "BACK", font);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePosition(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
                for (const auto& button : buttons) {
                    if (button.shape.getGlobalBounds().contains(mousePosition)) {
                        if (button.text.getString() == "Again") {
                            window.close();
                            system("./x/game");
                        } else if (button.text.getString() == "Quit") {
                            window.close();
                            
                        }
                    }
                }
            } else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePosition(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
                if (back_button.shape.getGlobalBounds().contains(mousePosition)) {
                    system("./start");
                    window.close();
                }    
            }
        }

        // Generate a new firework
        Particle firework;
        firework.position = sf::Vector2f(window.getSize().x / 2, window.getSize().y);
        float angle = static_cast<float>(std::rand() % 360);
        float speed = static_cast<float>(std::rand() % 200 + 100);
        firework.velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
        firework.lifetime = 1.5f; // Adjust the lifetime for desired effect
        fireworks.push_back(firework);

        // Update and draw fireworks
        window.clear();

        // Draw the background
        window.draw(background);

        // FireWork
        for (auto& firework : fireworks) {
            firework.position += firework.velocity * 0.02f; // Adjust the time step for desired speed
            firework.velocity.y -= 50.0f; // Move fireworks upward (subtract for upward motion)

            sf::CircleShape particle(5.0f);
            particle.setFillColor(text.getFillColor()); // Use the text color for particles
            particle.setPosition(firework.position);
            window.draw(particle);

            firework.lifetime -= 0.02f; // Adjust the time decrement for desired speed
        }

        fireworks.erase(std::remove_if(fireworks.begin(), fireworks.end(),
            [](const Particle& p) { return p.lifetime <= 0.0f; }), fireworks.end());

        // Update the text color every 1 second
        colorChangeTimer -= 0.02f;
        if (colorChangeTimer <= 0.0f) {
            text.setFillColor(generateRandomColor());
            colorChangeTimer = colorChangeFrequency;
        }

        // Center the text in the window
        text.setPosition((window.getSize().x - text.getGlobalBounds().width) / 2,
                          (window.getSize().y - text.getGlobalBounds().height) / 2);

        // Draw the text
        window.draw(text);

        // Draw the buttons
        drawButtonsBelowText(buttons, text, window);


        window.display();
    }

    return 0;
}
