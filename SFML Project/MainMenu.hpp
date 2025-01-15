#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include "SFML/Graphics.hpp"

class MainMenu {
public:
    MainMenu();
    void render(sf::RenderWindow& window);
    void handleEvent(sf::Event event, sf::RenderWindow& window, bool& startGame, bool& hardMode);

private:
    sf::Font font;
    sf::Text title;
    sf::Text easyOption;
    sf::Text hardOption;
    sf::Text levelText; // Added level text
};

#endif // MAINMENU_HPP
