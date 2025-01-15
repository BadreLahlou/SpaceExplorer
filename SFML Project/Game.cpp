#include "Game.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>
#include <random>

Game::Game()
    : m_window(sf::VideoMode(800, 600), "SFML Game"), m_player(), gameOver(false), startGame(false), hardMode(false), mainMenu(), playerRecord(0.0f), bestRecord(0.0f), isNewRecord(false) {
    m_window.setFramerateLimit(60);
    m_player.setPosition(400.f, 500.f); // Adjust starting position of the player

    if (!backgroundTexture.loadFromFile("space_background2.png")) {
        std::cerr << "Failed to load space_background.png" << std::endl;
    }

    backgroundSprite1.setTexture(backgroundTexture);
    backgroundSprite2.setTexture(backgroundTexture);

    sf::Vector2u windowSize = m_window.getSize();
    sf::Vector2u textureSize = backgroundTexture.getSize();

    backgroundSprite1.setScale(
        static_cast<float>(windowSize.x) / textureSize.x,
        static_cast<float>(windowSize.y) / textureSize.y
    );
    backgroundSprite2.setScale(
        static_cast<float>(windowSize.x) / textureSize.x,
        static_cast<float>(windowSize.y) / textureSize.y
    );

    backgroundSprite1.setPosition(0, 0);
    backgroundSprite2.setPosition(0, -static_cast<float>(windowSize.y));

    if (!alienTexture.loadFromFile("alien.png")) {
        std::cerr << "Failed to load alien.png" << std::endl;
    }

    if (!rockTexture.loadFromFile("rock.png")) {
        std::cerr << "Failed to load rock.png" << std::endl;
    }

    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load arial.ttf" << std::endl;
    }

    gameOverText.setFont(font);
    gameOverText.setString("Game Over");
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(300, 250);

    // Timer text
    timerText.setFont(font);
    timerText.setCharacterSize(30);
    timerText.setFillColor(sf::Color::White);
    timerText.setPosition(10, 10);

    // New record text
    newRecordText.setFont(font);
    newRecordText.setCharacterSize(30);
    newRecordText.setFillColor(sf::Color::Green);
    newRecordText.setPosition(300, 300);

    // Record text
    recordText.setFont(font);
    recordText.setCharacterSize(30);
    recordText.setFillColor(sf::Color::White);
    recordText.setPosition(300, 200);

    // Game Over menu and buttons
    showGameOverMenu = false;

    restartButton.setSize(sf::Vector2f(200, 50));
    restartButton.setFillColor(sf::Color::Green);
    restartButton.setPosition(300, 350);

    exitButton.setSize(sf::Vector2f(200, 50));
    exitButton.setFillColor(sf::Color::Red);
    exitButton.setPosition(300, 450);

    restartButtonText.setFont(font);
    restartButtonText.setString("Restart");
    restartButtonText.setCharacterSize(30);
    restartButtonText.setFillColor(sf::Color::White);
    restartButtonText.setPosition(350, 360);

    exitButtonText.setFont(font);
    exitButtonText.setString("Exit");
    exitButtonText.setCharacterSize(30);
    exitButtonText.setFillColor(sf::Color::White);
    exitButtonText.setPosition(375, 460);
}

void Game::run() {
    sf::Clock clock;
    while (m_window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        processEvents();
        if (startGame && !gameOver) {
            update(deltaTime);
        } else if (gameOver && gameOverDelayClock.getElapsedTime().asSeconds() > 0) {
            showGameOverMenu = true;
        }
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (startGame && !showGameOverMenu) {
            if (event.type == sf::Event::Closed) {
                m_window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                m_player.handleInput(event.key.code, true);
                if (event.key.code == sf::Keyboard::Space) {
                    Projectile projectile;
                    projectile.setPosition(m_player.getBounds().left + m_player.getBounds().width / 2,
                                           m_player.getBounds().top);
                    m_projectiles.push_back(projectile);
                }
            } else if (event.type == sf::Event::KeyReleased) {
                m_player.handleInput(event.key.code, false);
            }
        } else if (showGameOverMenu) {
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(m_window);
                if (restartButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))) {
                    // Restart the game
                    gameOver = false;
                    startGame = true;
                    showGameOverMenu = false;
                    m_projectiles.clear();
                    m_aliens.clear();
                    m_rocks.clear();
                    gameClock.restart();
                    playerRecord = 0.0f;
                    isNewRecord = false;
                } else if (exitButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))) {
                    m_window.close();
                }
            }
        } else {
            mainMenu.handleEvent(event, m_window, startGame, hardMode);
        }
    }
}

void Game::update(sf::Time deltaTime) {
    if (startGame && !gameOver) {
        // Update player
        m_player.update(deltaTime);

        // Update projectiles
        for (auto& projectile : m_projectiles) {
            projectile.update();
        }

        // Remove projectiles that are off-screen
        m_projectiles.erase(
            std::remove_if(m_projectiles.begin(), m_projectiles.end(), [](const Projectile& projectile) {
                return projectile.getBounds().top + projectile.getBounds().height < 0;
            }),
            m_projectiles.end()
        );

        // Update aliens
        for (auto& alien : m_aliens) {
            alien.update();
        }

        // Update rocks
        for (auto& rock : m_rocks) {
            rock.update();
        }

        // Check collisions
        checkCollisions();

        // Scroll background
        float scrollSpeed = 0.0f;
        sf::Vector2u windowSize = m_window.getSize();

        backgroundSprite1.move(0, scrollSpeed * deltaTime.asSeconds());
        backgroundSprite2.move(0, scrollSpeed * deltaTime.asSeconds());

        if (backgroundSprite1.getPosition().y >= static_cast<float>(windowSize.y)) {
            backgroundSprite1.setPosition(0, backgroundSprite2.getPosition().y - static_cast<float>(windowSize.y));
        }

        if (backgroundSprite2.getPosition().y >= static_cast<float>(windowSize.y)) {
            backgroundSprite2.setPosition(0, backgroundSprite1.getPosition().y - static_cast<float>(windowSize.y));
        }

        // Spawn aliens periodically
        if (alienSpawnClock.getElapsedTime().asSeconds() > 2) {
            spawnAliens();
            alienSpawnClock.restart();
        }

        // Spawn rocks periodically in hard mode
        if (hardMode && rockSpawnClock.getElapsedTime().asSeconds() > 3) {
            spawnRocks();
            rockSpawnClock.restart();
        }

        // Update timer
        sf::Time elapsedTime = gameClock.getElapsedTime();
        timerText.setString("Time: " + std::to_string(static_cast<int>(elapsedTime.asSeconds())) + "s");
        playerRecord = elapsedTime.asSeconds();
    }
}

void Game::render() {
    m_window.clear();

    if (!startGame) {
        // Draw the main menu without clearing the window each frame
        mainMenu.render(m_window);
    } else {
        m_window.draw(backgroundSprite1);
        m_window.draw(backgroundSprite2);
        m_player.render(m_window);

        for (const auto& projectile : m_projectiles) {
            projectile.render(m_window);
        }

        for (const auto& alien : m_aliens) {
            alien.render(m_window);
        }

        for (const auto& rock : m_rocks) {
            rock.render(m_window);
        }

        if (gameOver) {
            // Draw a black rectangle over the entire window
            sf::RectangleShape blackOverlay(sf::Vector2f(m_window.getSize()));
            blackOverlay.setFillColor(sf::Color(0, 0, 0, 255)); // Solid black
            m_window.draw(blackOverlay);

            displayGameOverScreen();
        }
    }

    m_window.display();
}



void Game::spawnAliens() {
    for (int i = 0; i < 8; ++i) {
        Alien alien;
        alien.setTexture(alienTexture);
        float x = static_cast<float>(rand() % 700); // Random x position
        float y = static_cast<float>(-rand() % 600); // Random y position above the screen
        alien.setPosition(x, y); // Spawn above the screen
        alien.setSpriteScale(0.04f, 0.04f); // Scale the aliens down to 30%

        // Adjust speed based on game mode
        if (hardMode) {
            alien.setSpeed(2.0f); // Set higher speed for hard mode
        } else {
            alien.setSpeed(1.0f); // Set lower speed for easy mode
        }

        // Randomly set zigzag movement
        bool shouldZigzag = rand() % 1 == 0; // 50% chance of zigzag
        alien.setZigzag(shouldZigzag);
        m_aliens.push_back(alien);
    }
}

void Game::spawnRocks() {
    for (int i = 0; i < 4; ++i) {
        Rock rock(rockTexture);
        float x = static_cast<float>(rand() % 700); // Random x position
        float y = static_cast<float>(-rand() % 600); // Random y position above the screen
        rock.setPosition(x, y); // Spawn above the screen
        m_rocks.push_back(rock);
        
    }
}

void Game::checkCollisions() {
    for (auto it = m_aliens.begin(); it != m_aliens.end();) {
        bool alienDestroyed = false;
        if (m_player.getBounds().intersects(it->getBounds())) {
            gameOver = true;
            gameOverDelayClock.restart();
            break;
        }

        for (auto projIt = m_projectiles.begin(); projIt != m_projectiles.end();) {
            if (projIt->getBounds().intersects(it->getBounds())) {
                it = m_aliens.erase(it);
                projIt = m_projectiles.erase(projIt);
                alienDestroyed = true;
                break;
            } else {
                ++projIt;
            }
        }

        if (!alienDestroyed) {
            ++it;
        }
    }

    for (const auto& rock : m_rocks) {
        if (m_player.getBounds().intersects(rock.getBounds())) {
            gameOver = true;
            gameOverDelayClock.restart();
            break;
        }
    }
}

void Game::displayGameOverScreen() {
    m_window.draw(gameOverText);

    // Update and display record text
    recordText.setString("Your Record: " + std::to_string(static_cast<int>(playerRecord)) + "s");
    m_window.draw(recordText);

    // If new record, update text appearance
    if (isNewRecord) {
        newRecordText.setString("YOU GOT A NEW RECORD: " + std::to_string(static_cast<int>(playerRecord)) + "s");
        newRecordText.setCharacterSize(40);
        newRecordText.setFillColor(sf::Color::Red);
        m_window.draw(newRecordText);
    }

    // Draw restart and exit buttons
    m_window.draw(restartButton);
    m_window.draw(exitButton);
    m_window.draw(restartButtonText);
    m_window.draw(exitButtonText);
}
