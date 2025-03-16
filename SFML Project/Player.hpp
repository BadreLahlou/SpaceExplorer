#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "SFML/Graphics.hpp"

class Player {
public:
    Player();
    void handleInput(sf::Keyboard::Key key, bool isPressed);
    void update(sf::Time deltaTime);
    void render(sf::RenderWindow& window);
    void setPosition(float x, float y);
    sf::FloatRect getBounds() const;

private:
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    float m_speed;
    bool m_movingUp;
    bool m_movingDown;
    bool m_movingLeft;
    bool m_movingRight;
};

#endif 
