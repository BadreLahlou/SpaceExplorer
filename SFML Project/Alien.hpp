#ifndef ALIEN_HPP
#define ALIEN_HPP

#include "SFML/Graphics.hpp"

class Alien {
public:
    Alien();
    void update();
    void render(sf::RenderWindow& window) const;
    void setPosition(float x, float y);
    void setTexture(const sf::Texture& texture);
    void setSpriteScale(float x, float y);
    sf::FloatRect getBounds() const;
    bool isExploding() const;
    void setExploding(bool exploding);
    void setZigzag(bool zigzag);
    void setSpeed(float speed);
    void setAmplitude(float amplitude);

private:
    sf::Sprite m_sprite;
    sf::Texture m_texture;
    bool exploding;
    bool zigzag;
    float speed;
    float amplitude;
};

#endif
