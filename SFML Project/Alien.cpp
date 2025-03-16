#include "Alien.hpp"
#include <cmath>

Alien::Alien()
: exploding(false), zigzag(false), speed(1.0f), amplitude(10.0f) {

}

void Alien::update() {

m_sprite.move(0, speed);


if (zigzag) {
   float xOffset = amplitude * sin(m_sprite.getPosition().y / 40.0f); // Adjust frequency
   m_sprite.move(xOffset, 0);
}


sf::Vector2f position = m_sprite.getPosition();
if (position.x < 0) {
   m_sprite.setPosition(0, position.y);
} else if (position.x + m_sprite.getGlobalBounds().width > 800) {
   m_sprite.setPosition(800 - m_sprite.getGlobalBounds().width, position.y);
}


if (position.y > 600) {
   m_sprite.setPosition(position.x, -m_sprite.getGlobalBounds().height);
}
}

void Alien::render(sf::RenderWindow& window) const {
window.draw(m_sprite);
}

void Alien::setPosition(float x, float y) {
m_sprite.setPosition(x, y);
}

void Alien::setTexture(const sf::Texture& texture) {
m_sprite.setTexture(texture);
}

void Alien::setSpriteScale(float x, float y) {
m_sprite.setScale(x, y);
}

sf::FloatRect Alien::getBounds() const {
return m_sprite.getGlobalBounds();
}

bool Alien::isExploding() const {
return exploding;
}

void Alien::setExploding(bool exploding) {
this->exploding = exploding;
}

void Alien::setZigzag(bool zigzag) {
this->zigzag = zigzag;
}

void Alien::setSpeed(float speed) {
this->speed = speed;
}

void Alien::setAmplitude(float amplitude) {
this->amplitude = amplitude;
}
