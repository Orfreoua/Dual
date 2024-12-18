#include "../headers/Samurai.hpp"
#include <iostream>

Samurai::Samurai(int x, int y)
    : Character(x, y),
      m_renderer(nullptr),
      m_direction(1),
      m_delayMs(100),
      m_width(128),
      m_height(128),
      currentSprite("assets/samurai/idle"),
      m_isJumping(false),
      m_currentLoop(true),
      m_startY(y),
      m_jumpHeight(m_height / 2),
      m_walkStartTime(0),
      m_isAttacking(false),
      m_isDying(false)
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
    // Gestion du saut
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

    // Passage de walk à run
    if (isWalking() && !isRunning()) {
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - m_walkStartTime >= RUN_THRESHOLD) {
            setSprite("assets/samurai/run", true);
        }
    }

    // Fin de l'attaque
    if (m_isAttacking && !m_currentLoop) {
        size_t lastFrameIndex = (m_currentAnimation.frames.empty()) ? 0 : (m_currentAnimation.frames.size() - 1);
        if (m_currentAnimation.currentFrame == lastFrameIndex) {
            Uint32 currentTime = SDL_GetTicks();
            if (currentTime - m_currentAnimation.lastFrameTime >= (Uint32)m_delayMs) {
                m_isAttacking = false;
                setSprite("assets/samurai/idle", true);
            }
        }
    }

    // Fin de l'animation dead
    if (m_isDying && !m_currentLoop) {
        size_t lastFrameIndex = (m_currentAnimation.frames.empty()) ? 0 : (m_currentAnimation.frames.size() - 1);
        if (m_currentAnimation.currentFrame == lastFrameIndex) {
            Uint32 currentTime = SDL_GetTicks();
            if (currentTime - m_currentAnimation.lastFrameTime >= (Uint32)m_delayMs) {
                // L'animation dead est terminée
                // On ne repasse pas à idle, on reste m_isDying = true.
                // On peut laisser Game détecter que c'est fini pour fermer le jeu.
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
    if (!m_isJumping && !m_isAttacking && !m_isDying) {
        m_isJumping = true;
        m_startY = getY();
        setSprite("assets/samurai/jump", false);
    }
}

bool Samurai::isJumping() const {
    return m_isJumping;
}

bool Samurai::isWalking() const {
    return (currentSprite.find("walk") != std::string::npos);
}

bool Samurai::isRunning() const {
    return (currentSprite.find("run") != std::string::npos);
}

void Samurai::startWalk() {
    if (!m_isJumping && !m_isAttacking && !m_isDying) {
        if (!isWalking() && !isRunning()) {
            setSprite("assets/samurai/walk", true);
            m_walkStartTime = SDL_GetTicks();
        } else if (isRunning()) {
            setSprite("assets/samurai/walk", true);
            m_walkStartTime = SDL_GetTicks();
        }
    }
}

void Samurai::stopWalk() {
    if (!m_isJumping && !m_isAttacking && !m_isDying) {
        setSprite("assets/samurai/idle", true);
    }
    m_walkStartTime = 0;
}

void Samurai::startAttack(const std::string& attackPath) {
    if (!m_isJumping && !m_isAttacking && !m_isDying) {
        m_isAttacking = true;
        setSprite(attackPath, false);
    }
}

bool Samurai::isAttacking() const {
    return m_isAttacking;
}

void Samurai::startDead() {
    if (!m_isAttacking && !m_isJumping && !m_isDying) {
        m_isDying = true;
        setSprite("assets/samurai/dead", false);
    }
}

bool Samurai::isDying() const {
    return m_isDying;
}

bool Samurai::isDeadAnimationFinished() const {
    // L'animation dead est terminée si m_isDying = true,
    // currentFrame = dernière frame et le temps d'affichage de cette frame est écoulé
    if (!m_isDying) return false;
    if (m_currentAnimation.frames.empty()) return false;

    size_t lastFrameIndex = m_currentAnimation.frames.size() - 1;
    if (m_currentAnimation.currentFrame != lastFrameIndex) return false;

    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - m_currentAnimation.lastFrameTime >= (Uint32)m_delayMs) {
        return true; // la dernière frame a été affichée assez longtemps
    }

    return false;
}
