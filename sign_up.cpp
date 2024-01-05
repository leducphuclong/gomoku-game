// g++ -std=c++11 sign_up.cpp -o sign_up -lsfml-graphics -lsfml-window -lsfml-system && ./sign_up

#include <SFML/Graphics.hpp>
#include <iostream>
#include "other.h"
#include <fstream>

struct TextBox {
    sf::Text label;
    sf::RectangleShape box;
    sf::Text input;
};

using namespace std;

bool isUsernameActive = true; // Flag to track which input field is active

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Sign Up");
    sf::RectangleShape cursor; // Cursor for indicating the typing position

    centerWindow(window);

    sf::Font font;
    if (!font.loadFromFile("/usr/share/matplotlib/mpl-data/fonts/ttf/DejaVuSansMono.ttf")) {
        return -1; // Failed to load font
    }

    sf::Text signUpText("Sign Up", font, 40);
    signUpText.setFillColor(sf::Color::White);
    signUpText.setPosition((window.getSize().x - signUpText.getGlobalBounds().width) / 2.0, signUpText.getGlobalBounds().height * 3);

    TextBox usernameBox;
    usernameBox.label.setString("New Username?");
    usernameBox.label.setFont(font);
    usernameBox.label.setCharacterSize(20);
    usernameBox.label.setFillColor(sf::Color::White);

    usernameBox.box.setSize(sf::Vector2f(300, 30));
    usernameBox.box.setFillColor(sf::Color(100, 100, 100)); // Gray color for the box

    usernameBox.input.setFont(font);
    usernameBox.input.setCharacterSize(20);
    usernameBox.input.setFillColor(sf::Color::Black);

    TextBox passwordBox;
    passwordBox.label.setString("New Password?");
    passwordBox.label.setFont(font);
    passwordBox.label.setCharacterSize(20);
    passwordBox.label.setFillColor(sf::Color::White);

    passwordBox.box.setSize(sf::Vector2f(300, 30));
    passwordBox.box.setFillColor(sf::Color(100, 100, 100)); // Gray color for the box

    passwordBox.input.setFont(font);
    passwordBox.input.setCharacterSize(20);
    passwordBox.input.setFillColor(sf::Color::Black);
    passwordBox.input.setString(""); // Hide password characters

    // Position the boxes and text inputs
    float boxSpacing = 10.0f;
    float startX = (window.getSize().x - usernameBox.box.getSize().x) / 2.0f;
    float startY = window.getSize().y / 2.0f - 50;

    usernameBox.label.setPosition(window.getSize().x / 2.0 - usernameBox.label.getGlobalBounds().width / 2.0, startY);
    usernameBox.box.setPosition(startX, startY + usernameBox.label.getGlobalBounds().height + boxSpacing);
    usernameBox.input.setPosition(usernameBox.box.getPosition().x + 5, usernameBox.box.getPosition().y + 5);

    passwordBox.label.setPosition(window.getSize().x / 2.0 - passwordBox.label.getGlobalBounds().width / 2.0, usernameBox.box.getPosition().y + usernameBox.box.getSize().y + boxSpacing);
    passwordBox.box.setPosition(startX, passwordBox.label.getPosition().y + passwordBox.label.getGlobalBounds().height + boxSpacing);
    passwordBox.input.setPosition(passwordBox.box.getPosition().x + 5, passwordBox.box.getPosition().y + 5);

    // Initialize the cursor
    float cursorWidth = 2.0f;
    cursor.setSize(sf::Vector2f(cursorWidth, usernameBox.input.getCharacterSize()));
    cursor.setFillColor(sf::Color::Black);
    cursor.setPosition(usernameBox.input.getPosition().x + usernameBox.input.getGlobalBounds().width + 5, usernameBox.input.getPosition().y);

    // Create a Text for Sign In option
    sf::Text signInText("Sign In", font, 20);
    signInText.setFillColor(sf::Color::White);
    signInText.setPosition((window.getSize().x - signInText.getGlobalBounds().width) / 2.0, passwordBox.box.getPosition().y + passwordBox.box.getSize().y + 2 * boxSpacing);

    // Underline the "Sign In" text
    sf::Vertex signInLine[] = {
        sf::Vertex(sf::Vector2f(signInText.getPosition().x, signInText.getPosition().y + signInText.getCharacterSize() + 5)),
        sf::Vertex(sf::Vector2f(signInText.getPosition().x + signInText.getGlobalBounds().width, signInText.getPosition().y + signInText.getCharacterSize() + 5))
    };

    // Creat a The Text Instruction
    sf::Text instructionText("Press Enter after you fill up the boxes, If you already have an account - Click Sign In.", font, 14);
    instructionText.setPosition((window.getSize().x - instructionText.getGlobalBounds().width) / 2.0, window.getSize().y - 5 * instructionText.getGlobalBounds().height);

    // Back button
    Button_Rectangle back_button;
    initializeButton(back_button, sf::Vector2f(5, 5), sf::Vector2f(120.0f, 50.0f), "BACK", font);

    // Message to existed username
    sf::Text messageText("", font, 15);
    messageText.setFillColor(sf::Color::Red);

    string tmp = "";
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::TextEntered) {
                // Handle text input events for each box
                if (event.text.unicode == 13) {
                    if (passwordBox.input.getString().isEmpty()) {
                        isUsernameActive = !isUsernameActive;
                    } else {
                        ifstream userFile("users.txt");
                        bool usernameExists = false;
                        string line;
                        while (getline(userFile, line)) {
                            ofstream seeFile("see.txt");
                            seeFile << "line: " << line << endl;
                            if (line == usernameBox.input.getString().toAnsiString()) {
                                usernameExists = true;
                                // break;
                            }
                            getline(userFile, line);
                        }
                        userFile.close();
                        if (usernameExists) {
                            messageText.setString("This username already exists. Please choose another one.");                            
                            messageText.setPosition((window.getSize().x - messageText.getGlobalBounds().width) / 2.0, usernameBox.input.getPosition().y - 5*messageText.getGlobalBounds().height);
                        } else {
                            ofstream userFile("users.txt", ios::app);
                            userFile << usernameBox.input.getString().toAnsiString() << endl;
                            userFile << tmp << endl;
                            window.close();
                            curr_user_name = usernameBox.input.getString().toAnsiString();
                            system("./sign_in");
                        }
                        
                    }
                } else if (isUsernameActive) {
                    if (event.text.unicode >= 32 && event.text.unicode < 128) {
                        usernameBox.input.setString(usernameBox.input.getString() + static_cast<char>(event.text.unicode));
                    } else if (event.text.unicode == 8 && !usernameBox.input.getString().isEmpty()) {
                        // Backspace key is pressed and the input string is not empty
                        usernameBox.input.setString(usernameBox.input.getString().substring(0, usernameBox.input.getString().getSize() - 1));
                    }
                } else { // Password box is active
                    if (event.text.unicode >= 32 && event.text.unicode < 128) {
                        tmp += static_cast<char>(event.text.unicode);
                    } else if (event.text.unicode == 8 && !tmp.empty()) {
                        tmp.pop_back();
                    }
                    passwordBox.input.setString(std::string(tmp.length(), '*'));  // Display asterisks
                }
            } else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePosition(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
                if (back_button.shape.getGlobalBounds().contains(mousePosition)) {
                    window.close();
                    system("./start");
                } else if (signInText.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
                    window.close();
                    // Go to Sign Up Window
                    system("./sign_in");
                }
            }

            // Handle switching between input fields (e.g., using Tab key)
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Tab) {
                    isUsernameActive = !isUsernameActive;
                }
            }
        }

        if (isUsernameActive) {
            cursor.setPosition(usernameBox.input.getPosition().x + usernameBox.input.getGlobalBounds().width + 5, usernameBox.input.getPosition().y);
        } else {
            cursor.setPosition(passwordBox.input.getPosition().x + passwordBox.input.getGlobalBounds().width + 5, passwordBox.input.getPosition().y);
        }

        window.clear();

        // Draw username box and text
        window.draw(usernameBox.box);
        window.draw(usernameBox.label);
        window.draw(usernameBox.input);

        // Draw password box and text
        window.draw(passwordBox.box);
        window.draw(passwordBox.label);
        window.draw(passwordBox.input);

        // Draw underline for Sign In text
        window.draw(signInLine, 2, sf::Lines);

        // Draw the back button
        window.draw(back_button.shape);
        window.draw(back_button.text);

        // Draw Sign In text
        window.draw(signInText);

        window.draw(signUpText);

        window.draw(cursor);

        window.draw(instructionText);

        window.draw(messageText);

        window.display();
    }

    return 0;
}
