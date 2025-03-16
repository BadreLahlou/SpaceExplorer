#include "Projectile.hpp"

Projectile::Projectile() : speed(-6.0f) {
    if (!m_texture.loadFromFile("projectile1.png")) {
       
    }
    m_sprite.setTexture(m_texture);
    m_sprite.setScale(0.1f, 0.1f); 
}

void Projectile::update() {
    m_sprite.move(0, speed);
}

void Projectile::render(sf::RenderWindow& window) const { 
    window.draw(m_sprite);
}

void Projectile::setPosition(float x, float y) {
    m_sprite.setPosition(x, y);
}

sf::FloatRect Projectile::getBounds() const {
    return m_sprite.getGlobalBounds();
}
