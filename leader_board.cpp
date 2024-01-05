#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <queue>
#include "other.h"
#include <sstream>
#include <iomanip>

using namespace std;

// g++ -std=c++11 leader_board.cpp -o leader_board -lsfml-graphics -lsfml-window -lsfml-system && ./leader_board

#define nln '\n'

struct Leader {
    string username, result, date;
    double time;
};

struct CompareLeader {
    // Comparison function for the priority queue
    bool operator()(const Leader& lhs, const Leader& rhs) const {
        if (lhs.result == "WIN" && rhs.result == "WIN") {
            // If both results are "WIN", prioritize lower time
            return lhs.time > rhs.time;
        } else if (lhs.result == "WIN" && rhs.result == "LOSE") {
            // If lhs is "WIN" and rhs is "LOSE", lhs is better
            return false;
        } else if (lhs.result == "LOSE" && rhs.result == "WIN") {
            // If lhs is "LOSE" and rhs is "WIN", rhs is better
            return true;
        } else {
            // If both results are "LOSE", prioritize higher time
            return lhs.time < rhs.time;
        }
    }
};

std::string floatToStringWithPrecision(float value) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(3) << value;
    return oss.str();
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Leader Board !!");

    centerWindow(window);

    sf::Font font = loadFont();

    sf::Text text("LEADER BOARD", font, 50);
    text.setFillColor(sf::Color::White);

    sf::Clock clock; // Create a clock object

    // Center the button and text in the window
    float centerX = 0.0f; // Starting from the left edge
    float centerY = (window.getSize().y - text.getGlobalBounds().height) / 2;

    // Back button
    Button_Rectangle back_button;
    initializeButton(back_button, sf::Vector2f(5, 5), sf::Vector2f(120.0f, 50.0f), "BACK", font);

    system("./loadleaders");

    ifstream inFile("leaders.txt");
    priority_queue<Leader, vector<Leader>, CompareLeader> leadersQueue;
    map<string, bool> exist;

    // Read leaderboard data
    Leader tmp;
    while (inFile >> tmp.username >> tmp.result >> tmp.date >> tmp.time) {
        if (!exist[tmp.username] && leadersQueue.size() < 10) {
            leadersQueue.push(tmp);
            exist[tmp.username] = true;
        }
    }
    inFile.close();

    // prepare to draw leaders
    float startX = centerX + 50; // Start position for the first column
    float startY = 110; // Start position below the title
    int rank = 1;
    vector<sf::Text> leaderboardEntries;

    // Draw table headers
    sf::Text headerRank("Rank", font, 20);
    headerRank.setFillColor(sf::Color::White);
    headerRank.setPosition(startX-13, startY);

    sf::Text headerName("Name", font, 20);
    headerName.setFillColor(sf::Color::White);
    headerName.setPosition(startX + 100.0f, startY);

    sf::Text headerResult("Result", font, 20);
    headerResult.setFillColor(sf::Color::White);
    headerResult.setPosition(startX + 220.0f, startY);

    sf::Text headerDate("Date", font, 20);
    headerDate.setFillColor(sf::Color::White);
    headerDate.setPosition(startX + 430.0f, startY);

    sf::Text headerTime("Time", font, 20);
    headerTime.setFillColor(sf::Color::White);
    headerTime.setPosition(startX + 630.0f, startY);

    startY += 30.0f; // Move down for the table content

    while (!leadersQueue.empty()) {
        auto ld = leadersQueue.top();

        // Recreate sf::Text for each iteration
        sf::Text rankText(to_string(rank++), font, 20);
        rankText.setFillColor(sf::Color::White);
        rankText.setPosition(startX, startY);

        sf::Text nameText(ld.username, font, 20);
        nameText.setFillColor(sf::Color::White);
        float centerX_of_header = headerName.getPosition().x + headerName.getGlobalBounds().width/2.0f;
        nameText.setPosition(centerX_of_header - nameText.getGlobalBounds().width/2.0f, startY);

        sf::Text resultText(ld.result, font, 20);
        resultText.setFillColor(sf::Color::White);
        float centerX_of_headerResult = headerResult.getPosition().x + headerResult.getGlobalBounds().width/2.0f;
        resultText.setPosition(centerX_of_headerResult - resultText.getGlobalBounds().width/2.0f, startY);

        sf::Text dateText(ld.date, font, 20);
        dateText.setFillColor(sf::Color::White);
        float centerX_of_headerDate = headerDate.getPosition().x + headerDate.getGlobalBounds().width/2.0f;
        dateText.setPosition(centerX_of_headerDate - dateText.getGlobalBounds().width/2.0f, startY);

        sf::Text timeText(floatToStringWithPrecision(ld.time), font, 20);
        timeText.setFillColor(sf::Color::White);
        float centerX_of_headerTime = headerTime.getPosition().x + headerTime.getGlobalBounds().width/2.0f;
        timeText.setPosition(centerX_of_headerTime - timeText.getGlobalBounds().width/2.0f, startY);

        // Add each column to the vector
        leaderboardEntries.push_back(rankText);
        leaderboardEntries.push_back(nameText);
        leaderboardEntries.push_back(resultText);
        leaderboardEntries.push_back(dateText);
        leaderboardEntries.push_back(timeText);

        leadersQueue.pop();
        startY += 30.0f; // Adjust the vertical spacing
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePosition(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
                if (back_button.shape.getGlobalBounds().contains(mousePosition)) {
                    system("./start");
                    window.close();
                }
            }
        }

        // Draw the text on the button with the oscillating motion
        text.setPosition(centerX + (window.getSize().x - text.getGlobalBounds().width) / 2, 0);

        window.clear();

        // Draw the text
        window.draw(text);

        // Draw the back button
        window.draw(back_button.shape);
        window.draw(back_button.text);

        // Draw the table headers
        window.draw(headerRank);
        window.draw(headerName);
        window.draw(headerResult);
        window.draw(headerDate);
        window.draw(headerTime);

        // Draw the leaderboard entries
        for (const auto& entry : leaderboardEntries) {
            window.draw(entry);
        }

        // Display
        window.display();
    }

    return 0;
}
