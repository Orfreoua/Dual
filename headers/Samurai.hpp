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
    
    // Méthodes pour la marche/course
    bool isWalking() const;
    bool isRunning() const;
    void startWalk();
    void stopWalk();

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

    // Ajout pour la marche et la course
    Uint32 m_walkStartTime;           // Quand la marche a débuté
    const Uint32 RUN_THRESHOLD = 1500; // Temps (en ms) avant de passer de walk à run
};

#endif // SAMURAI_HPP
