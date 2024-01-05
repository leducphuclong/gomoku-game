#include <SFML/Graphics.hpp>

using namespace std;

string curr_user_name = "";

sf::Color generateRandomColor() {
    return sf::Color(std::rand() % 256, std::rand() % 256, std::rand() % 256);
}

struct Button_Rectangle {
    sf::Text text;
    sf::RectangleShape shape; // Change to RectangleShape
};


void initializeButton(Button_Rectangle& button, const sf::Vector2f& position, const sf::Vector2f& size, const std::string& buttonText, const sf::Font& font) {
    button.text.setString(buttonText);
    button.text.setFont(font);
    button.text.setCharacterSize(30);
    button.text.setFillColor(sf::Color::White);

    // Set initial position and size for the shape
    button.shape.setSize(size); // Use setSize for RectangleShape
    button.shape.setFillColor(sf::Color(100, 100, 100));
    button.shape.setPosition(position);
    
    // Center the text in the shape
    float textX = position.x + (size.x - button.text.getGlobalBounds().width) / 2;
    float textY = position.y + (size.y - button.text.getGlobalBounds().height) / 2 - 5;
    button.text.setPosition(textX, textY);
}

void centerWindow(sf::RenderWindow& window) {
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    sf::Vector2i screenCenter(desktopMode.width / 2, desktopMode.height / 2);

    window.setPosition(screenCenter - sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2));
}

sf::Font loadFont() {
    sf::Font font;
    if (!font.loadFromFile("/usr/share/matplotlib/mpl-data/fonts/ttf/DejaVuSansMono.ttf")) {
        // You might want to handle the error differently, like displaying a message or logging.
        // For simplicity, returning an empty font here.
        return sf::Font();
    }
    return font;
}

// Function to center buttons below text, draw them, and add borders
void drawButtonsBelowText(std::vector<Button_Rectangle>& buttons, sf::Text& text, sf::RenderWindow& window) {
    float buttonContainerWidth = std::max(buttons[0].shape.getSize().x, buttons[1].shape.getSize().x);
    float totalWidth = buttonContainerWidth * buttons.size();
    float xOffset = (window.getSize().x - totalWidth) / 2.0f;

    // Draw buttons
    for (std::size_t i = 0; i < buttons.size(); ++i) {
        buttons[i].shape.setPosition(xOffset + i * buttonContainerWidth, text.getPosition().y + text.getGlobalBounds().height + 20.0f);
        buttons[i].text.setPosition(buttons[i].shape.getPosition().x + (buttonContainerWidth - buttons[i].text.getGlobalBounds().width) / 2,
                                    buttons[i].shape.getPosition().y + (buttons[i].shape.getSize().y - buttons[i].text.getGlobalBounds().height) / 2 - 5);

        sf::RectangleShape border(buttons[i].shape.getSize());
        border.setPosition(buttons[i].shape.getPosition());
        border.setFillColor(sf::Color::Transparent);
        border.setOutlineColor(sf::Color::White);
        border.setOutlineThickness(2.0f);
        window.draw(border);

        window.draw(buttons[i].shape);
        window.draw(buttons[i].text);
    }
}