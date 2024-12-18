#include "../headers/Samurai.hpp"
#include <iostream>
#include <SDL2/SDL.h>

Samurai::Samurai(int x, int y)
    : Character(x, y),
      m_renderer(nullptr),
      m_direction(1),
      m_delayMs(100),
      m_width(128),
      m_height(128),
      currentSprite("idle"),
      m_isJumping(false),
      m_currentLoop(true),
      m_startY(y),
      m_jumpHeight(64), // m_height/2 = 128/2 = 64
      m_walkStartTime(0),
      m_isAttacking(false),
      m_isDying(false),
      m_basePath("assets/samurai")
{
}

void Samurai::init(SDL_Renderer* renderer, const std::string& basePath) {
    m_renderer = renderer;
    m_basePath = basePath;
    setSprite("idle", true);
}

void Samurai::setSprite(const std::string& spriteName, bool loop) {
    currentSprite = spriteName;
    m_currentLoop = loop;
    destroyAnimation(m_currentAnimation);
    std::string fullPath = m_basePath + "/" + spriteName;
    m_currentAnimation = loadAnimation(m_renderer, fullPath);
    std::cout << "Sprite actif défini sur : " << fullPath << " (loop=" << (loop?"true":"false") << ")" << std::endl;
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
                setSprite("idle", true);
                setPosition(getX(), m_startY);
            }
        }
    }

    // Passage de walk à run
    if (isWalking() && !isRunning()) {
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - m_walkStartTime >= RUN_THRESHOLD) {
            setSprite("run", true);
        }
    }

    // Fin de l'attaque
    if (m_isAttacking && !m_currentLoop) {
        size_t lastFrameIndex = (m_currentAnimation.frames.empty()) ? 0 : (m_currentAnimation.frames.size() - 1);
        if (m_currentAnimation.currentFrame == lastFrameIndex) {
            Uint32 currentTime = SDL_GetTicks();
            if (currentTime - m_currentAnimation.lastFrameTime >= (Uint32)m_delayMs) {
                m_isAttacking = false;
                setSprite("idle", true);
            }
        }
    }

    // Fin de dead
    if (m_isDying && !m_currentLoop) {
        // On ne repasse pas à idle après dead.
        // On laisse Game détecter la fin avec isDeadAnimationFinished().
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
        setSprite("jump", false);
    }
}

bool Samurai::isJumping() const {
    return m_isJumping;
}

bool Samurai::isWalking() const {
    return (currentSprite == "walk");
}

bool Samurai::isRunning() const {
    return (currentSprite == "run");
}

void Samurai::startWalk() {
    if (!m_isJumping && !m_isAttacking && !m_isDying) {
        if (!isWalking() && !isRunning()) {
            setSprite("walk", true);
            m_walkStartTime = SDL_GetTicks();
        } else if (isRunning()) {
            setSprite("walk", true);
            m_walkStartTime = SDL_GetTicks();
        }
    }
}

void Samurai::stopWalk() {
    if (!m_isJumping && !m_isAttacking && !m_isDying) {
        setSprite("idle", true);
    }
    m_walkStartTime = 0;
}

void Samurai::startAttack(const std::string& attackName) {
    if (!m_isJumping && !m_isAttacking && !m_isDying) {
        m_isAttacking = true;
        setSprite(attackName, false);
    }
}

bool Samurai::isAttacking() const {
    return m_isAttacking;
}

void Samurai::startDead() {
    if (!m_isAttacking && !m_isJumping && !m_isDying) {
        m_isDying = true;
        setSprite("dead", false);
    }
}

bool Samurai::isDying() const {
    return m_isDying;
}

bool Samurai::isDeadAnimationFinished() const {
    if (!m_isDying) return false;
    if (m_currentAnimation.frames.empty()) return false;

    size_t lastFrameIndex = m_currentAnimation.frames.size() - 1;
    if (m_currentAnimation.currentFrame != lastFrameIndex) return false;

    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - m_currentAnimation.lastFrameTime >= (Uint32)m_delayMs) {
        return true; 
    }

    return false;
}

void Samurai::setBasePath(const std::string& path) {
    m_basePath = path;
}
