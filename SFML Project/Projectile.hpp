#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "SFML/Graphics.hpp"

class Projectile {
public:
    Projectile();
    void update();
    void render(sf::RenderWindow& window) const; // Marked as const
    void setPosition(float x, float y);
    sf::FloatRect getBounds() const;

private:
    sf::Sprite m_sprite;
    sf::Texture m_texture;
    float speed;
};

#endif // PROJECTILE_HPP
