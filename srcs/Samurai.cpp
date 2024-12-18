#include "../headers/Samurai.hpp"
#include <iostream>

Samurai::Samurai(int x, int y)
    : Character(x, y),
      m_renderer(nullptr),
      m_direction(1),
      m_delayMs(100),
      m_width(64),
      m_height(64),
      currentSprite("assets/samurai/idle")
{
}

void Samurai::init(SDL_Renderer* renderer) {
    m_renderer = renderer;
    m_currentAnimation = loadAnimation(m_renderer, currentSprite);
}

void Samurai::setSprite(const std::string& spritePath) {
    currentSprite = spritePath;
    destroyAnimation(m_currentAnimation);
    m_currentAnimation = loadAnimation(m_renderer, currentSprite);
    std::cout << "Sprite actif défini sur : " << currentSprite << std::endl;
}

void Samurai::updateAndRender() {
    updateAndRenderAnimation(m_renderer, m_currentAnimation, getX(), getY(), m_width, m_height, m_delayMs, m_direction);
}

void Samurai::setDirection(int dir) {
    m_direction = dir;
}

void Samurai::cleanUp() {
    destroyAnimation(m_currentAnimation);
}
