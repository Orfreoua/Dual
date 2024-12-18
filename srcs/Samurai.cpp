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
      m_jumpHeight(50),
      m_walkStartTime(0) // initialisé à 0
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
    // Gestion du saut (identique à avant)
    if (m_isJumping && !m_currentLoop && m_currentAnimation.frames.size() > 1) {
        size_t F = m_currentAnimation.frames.size();
        size_t cf = m_currentAnimation.currentFrame;
        size_t midFrame = F / 2;

        int newY;
        if (cf < midFrame) {
            float t = (float)cf / (float)(midFrame);
            newY = m_startY - (int)(m_jumpHeight * t);
        } else {
            float t = (float)(cf - midFrame) / (float)(F - midFrame - 1);
            newY = m_startY - m_jumpHeight + (int)(m_jumpHeight * t);
        }

        setPosition(getX(), newY);
    }

    // Appel du rendu de l'animation
    updateAndRenderAnimation(m_renderer, m_currentAnimation, getX(), getY(), m_width, m_height, m_delayMs, m_direction, m_currentLoop);

    // Fin du saut
    if (m_isJumping && !m_currentLoop) {
        size_t lastFrameIndex = (m_currentAnimation.frames.empty()) ? 0 : (m_currentAnimation.frames.size() - 1);
        if (m_currentAnimation.currentFrame == lastFrameIndex) {
            Uint32 currentTime = SDL_GetTicks();
            if (currentTime - m_currentAnimation.lastFrameTime >= (Uint32)m_delayMs) {
                m_isJumping = false;
                setSprite("assets/samurai/idle", true);
                setPosition(getX(), m_startY);
            }
        }
    }

    // Vérifier si on doit passer de walk à run
    if (isWalking() && !isRunning()) {
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - m_walkStartTime >= RUN_THRESHOLD) {
            // Passe à run
            setSprite("assets/samurai/run", true);
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
        m_startY = getY();
        setSprite("assets/samurai/jump", false);
    }
}

bool Samurai::isJumping() const {
    return m_isJumping;
}

// Méthodes de marche/course
bool Samurai::isWalking() const {
    return (currentSprite.find("walk") != std::string::npos);
}

bool Samurai::isRunning() const {
    return (currentSprite.find("run") != std::string::npos);
}

void Samurai::startWalk() {
    // On ne réinitialise le timer que si on passe vraiment à walk
    // c'est-à-dire si on n'est ni en walk ni en run
    if (!isWalking() && !isRunning()) {
        setSprite("assets/samurai/walk", true);
        m_walkStartTime = SDL_GetTicks();
    } else if (isRunning()) {
        // Si on était en run et qu'on repasse à walk (situation rare),
        // on réinitialise le chrono
        setSprite("assets/samurai/walk", true);
        m_walkStartTime = SDL_GetTicks();
    }
}

void Samurai::stopWalk() {
    // Revenir à idle
    setSprite("assets/samurai/idle", true);
    // Réinitialiser le timer
    m_walkStartTime = 0;
}
