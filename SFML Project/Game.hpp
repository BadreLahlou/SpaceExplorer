#ifndef GAME_HPP
#define GAME_HPP

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "Player.hpp"
#include "Alien.hpp"
#include "Projectile.hpp"
#include "Rock.hpp"
#include "MainMenu.hpp"

class Game {
public:
Game();
void run();

private:
void processEvents();
void update(sf::Time deltaTime);
void render();
void spawnAliens();
void spawnRocks();
void checkCollisions();
void displayGameOverScreen();

sf::RenderWindow m_window;
Player m_player;
sf::Texture alienTexture;
sf::Texture rockTexture;
sf::Texture backgroundTexture;
sf::Sprite backgroundSprite1;
sf::Sprite backgroundSprite2;
std::vector<Alien> m_aliens;
std::vector<Rock> m_rocks;
std::vector<Projectile> m_projectiles;
sf::Clock alienSpawnClock;
sf::Clock rockSpawnClock;
sf::Clock gameClock;
sf::Font font;
sf::Text gameOverText;
sf::Text timerText;
sf::Text newRecordText;
sf::RectangleShape restartButton;
sf::RectangleShape exitButton;
sf::Text restartButtonText;
sf::Text exitButtonText;
bool gameOver;
bool startGame;
bool hardMode;
bool showGameOverMenu;
float playerRecord;
sf::Clock gameOverDelayClock;
MainMenu mainMenu;

sf::Text recordText;
float bestRecord;
bool isNewRecord;
};

#endif 
