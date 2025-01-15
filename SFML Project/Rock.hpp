#ifndef ROCK_HPP
#define ROCK_HPP

#include "SFML/Graphics.hpp"

class Rock {
public:
    Rock(const sf::Texture& texture);
    void setPosition(float x, float y);
    void update();
    void render(sf::RenderWindow& window) const;
    sf::FloatRect getBounds() const;

private:
    sf::Sprite m_sprite;
    float m_speed;
};

#endif // ROCK_HPP
