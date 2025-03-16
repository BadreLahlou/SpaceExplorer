#include "Rock.hpp"

Rock::Rock(const sf::Texture& texture)
    : m_speed(5.0f) 
{
    m_sprite.setTexture(texture);
}

void Rock::setPosition(float x, float y) {
    m_sprite.setPosition(x, y);
}

void Rock::update() {
    m_sprite.move(0, m_speed);
}

void Rock::render(sf::RenderWindow& window) const {
    window.draw(m_sprite);
}

sf::FloatRect Rock::getBounds() const {
    return m_sprite.getGlobalBounds();
}
