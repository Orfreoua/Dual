#include "../headers/Samurai.hpp"
#include <iostream>

Samurai::Samurai(int x, int y)
    : Character(x, y),
      m_renderer(nullptr),
      m_direction(1),
      m_delayMs(100),
      m_width(64),
      m_height(64),
      currentSprite("assets/samurai/idle"),
      m_isJumping(false),
      m_currentLoop(true),
      m_startY(y),
      m_jumpHeight(50) // Hauteur du saut, ajustez selon vos besoins
{
}

void Samurai::init(SDL_Renderer* renderer) {
    m_renderer = renderer;
    m_currentAnimation = loadAnimation(m_renderer, currentSprite);
    m_currentLoop = true;
}

void Samurai::setSprite(const std::string& spritePath, bool loop) {
    currentSprite = spritePath;
    m_currentLoop = loop;
    destroyAnimation(m_currentAnimation);
    m_currentAnimation = loadAnimation(m_renderer, currentSprite);
    std::cout << "Sprite actif défini sur : " << currentSprite << " (loop=" << (loop?"true":"false") << ")" << std::endl;
}

void Samurai::updateAndRender() {
    // Mettre à jour la position si on est en saut et que l'animation n'est pas bouclée
    if (m_isJumping && !m_currentLoop && m_currentAnimation.frames.size() > 1) {
        size_t F = m_currentAnimation.frames.size();
        size_t cf = m_currentAnimation.currentFrame;
        size_t midFrame = F / 2;

        // Calcul de la nouvelle position en fonction de la frame
        // Première moitié : monter
        // Deuxième moitié : redescendre
        int newY;
        if (cf < midFrame) {
            // Progression de 0 à m_jumpHeight sur la première moitié
            float t = (float)cf / (float)(midFrame);
            newY = m_startY - (int)(m_jumpHeight * t);
        } else {
            // Redescente sur la deuxième moitié
            float t = (float)(cf - midFrame) / (float)(F - midFrame - 1);
            // t passe de 0 à 1 dans la deuxième moitié
            // On redescend de m_jumpHeight à 0
            newY = m_startY - m_jumpHeight + (int)(m_jumpHeight * t);
        }

        setPosition(getX(), newY);
    }

    updateAndRenderAnimation(m_renderer, m_currentAnimation, getX(), getY(), m_width, m_height, m_delayMs, m_direction, m_currentLoop);

    // Si on est en train de sauter et que c'est une animation non bouclée
    if (m_isJumping && !m_currentLoop) {
        size_t lastFrameIndex = (m_currentAnimation.frames.empty()) ? 0 : (m_currentAnimation.frames.size() - 1);
        if (m_currentAnimation.currentFrame == lastFrameIndex) {
            Uint32 currentTime = SDL_GetTicks();
            if (currentTime - m_currentAnimation.lastFrameTime >= (Uint32)m_delayMs) {
                // L'animation est terminée, on repasse en idle
                m_isJumping = false;
                setSprite("assets/samurai/idle", true);
                // Restaure la position initiale
                setPosition(getX(), m_startY);
            }
        }
    }
}

void Samurai::setDirection(int dir) {
    m_direction = dir;
}

void Samurai::cleanUp() {
    destroyAnimation(m_currentAnimation);
}

void Samurai::startJump() {
    if (!m_isJumping) {
        m_isJumping = true;
        m_startY = getY(); // On enregistre la position au sol avant le saut
        setSprite("assets/samurai/jump", false); // jump non bouclé
        // Ne pas changer la position ici, on le fera dans updateAndRender()
    }
}

bool Samurai::isJumping() const {
    return m_isJumping;
}
