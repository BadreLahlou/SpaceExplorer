#include "MainMenu.hpp"
#include <iostream>

MainMenu::MainMenu() {
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load arial.ttf" << std::endl;
    }
    title.setFont(font);
    title.setString("Space Explorer");
    title.setCharacterSize(100); // Increased character size
    title.setFillColor(sf::Color::Blue); // Changed color to blue
    title.setPosition(150, 100); // Adjusted position for centering

    easyOption.setFont(font);
    easyOption.setString("EASY");
    easyOption.setCharacterSize(60); // Increased character size
    easyOption.setFillColor(sf::Color::White);
    easyOption.setPosition(350, 250);

    hardOption.setFont(font);
    hardOption.setString("HARD");
    hardOption.setCharacterSize(60); // Increased character size
    hardOption.setFillColor(sf::Color::White);
    hardOption.setPosition(350, 350);

    levelText.setFont(font); // Added level text
    levelText.setString("Level:");
    levelText.setCharacterSize(45);
    levelText.setFillColor(sf::Color::White);
    levelText.setPosition(100, 300);
}

void MainMenu::render(sf::RenderWindow& window) {
    window.draw(title);
    window.draw(easyOption);
    window.draw(hardOption);
    window.draw(levelText); // Render level text
}

void MainMenu::handleEvent(sf::Event event, sf::RenderWindow& window, bool& startGame, bool& hardMode) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        if (easyOption.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))) {
            startGame = true;
            hardMode = false;
        } else if (hardOption.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))) {
            startGame = true;
            hardMode = true;
        }
    }
}
