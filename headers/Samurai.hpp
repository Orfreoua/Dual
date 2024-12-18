#ifndef SAMURAI_HPP
#define SAMURAI_HPP

#include "Character.hpp"
#include "Animation.hpp"
#include <string>

class Samurai : public Character {
public:
    Samurai(int x = 0, int y = 0);

    void init(SDL_Renderer* renderer);
    void setSprite(const std::string& spritePath, bool loop = true);
    void updateAndRender();
    void setDirection(int dir);
    void cleanUp();

    void startJump();
    bool isJumping() const;

    bool isWalking() const;
    bool isRunning() const;
    void startWalk();
    void stopWalk();

    void startAttack(const std::string& attackPath);
    bool isAttacking() const;

	bool isDeadAnimationFinished() const;
    // Nouveau : état de mort
    void startDead();
    bool isDying() const;

private:
    SDL_Renderer* m_renderer;
    Animation m_currentAnimation;
    int m_direction;  
    int m_delayMs;    
    int m_width, m_height;
    std::string currentSprite;
    bool m_isJumping;
    bool m_currentLoop;

    int m_startY;
    int m_jumpHeight;
    Uint32 m_walkStartTime;
    const Uint32 RUN_THRESHOLD = 500;

    bool m_isAttacking;
    bool m_isDying; // Indique si le samouraï est en train de "mourir" (dead)
};

#endif // SAMURAI_HPP
