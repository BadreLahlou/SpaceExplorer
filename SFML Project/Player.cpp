#include "Player.hpp"
#include <iostream>

Player::Player()
    : m_speed(200.f), m_movingUp(false), m_movingDown(false), m_movingLeft(false), m_movingRight(false) {
    if (!m_texture.loadFromFile("spaceship.png")) {
        std::cerr << "Failed to load spaceship.png" << std::endl;
    }

    m_sprite.setTexture(m_texture);
    m_sprite.setScale(0.2f, 0.2f); 
    m_sprite.setPosition(400.f, 500.f); 
}

void Player::handleInput(sf::Keyboard::Key key, bool isPressed) {
    if (key == sf::Keyboard::W || key == sf::Keyboard::Up) {
        m_movingUp = isPressed;
    } else if (key == sf::Keyboard::S || key == sf::Keyboard::Down) {
        m_movingDown = isPressed;
    } else if (key == sf::Keyboard::A || key == sf::Keyboard::Left) {
        m_movingLeft = isPressed;
    } else if (key == sf::Keyboard::D || key == sf::Keyboard::Right) {
        m_movingRight = isPressed;
    }
}

void Player::update(sf::Time deltaTime) {
    sf::Vector2f movement(0.1f, 0.1f);
    if (m_movingUp) {
        movement.y -= m_speed;
    }
    if (m_movingDown) {
        movement.y += m_speed;
    }
    if (m_movingLeft) {
        movement.x -= m_speed;
    }
    if (m_movingRight) {
        movement.x += m_speed;
    }

    m_sprite.move(movement * deltaTime.asSeconds());

    
    sf::Vector2f position = m_sprite.getPosition();
    if (position.x < 0) {
        m_sprite.setPosition(0, position.y);
    } else if (position.x + m_sprite.getGlobalBounds().width > 800) {
        m_sprite.setPosition(800 - m_sprite.getGlobalBounds().width, position.y);
    }
    if (position.y < 0) {
        m_sprite.setPosition(position.x, 0);
    } else if (position.y + m_sprite.getGlobalBounds().height > 600) {
        m_sprite.setPosition(position.x, 600 - m_sprite.getGlobalBounds().height);
    }
}

void Player::render(sf::RenderWindow& window) {
    window.draw(m_sprite);
}

void Player::setPosition(float x, float y) {
    m_sprite.setPosition(x, y);
}

sf::FloatRect Player::getBounds() const {
    return m_sprite.getGlobalBounds();
}
