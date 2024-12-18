#ifndef SAMURAI_HPP
#define SAMURAI_HPP

#include "Character.hpp"
#include "Animation.hpp"
#include <string>

class Samurai : public Character {
public:
    Samurai(int x = 0, int y = 0);

    // Initialise le samouraï avec un renderer et un chemin de base (ex: "assets/samurai")
    void init(SDL_Renderer* renderer, const std::string& basePath = "assets/samurai");
    
    // Définit le sprite actif à partir du nom du répertoire (ex: "idle", "walk", "run")
    // Le chemin complet sera m_basePath + "/" + spriteName
    void setSprite(const std::string& spriteName, bool loop = true);
    
    void updateAndRender();
    void setDirection(int dir);
    void cleanUp();

    // Saut
    void startJump();
    bool isJumping() const;

    // Marche et course
    bool isWalking() const;
    bool isRunning() const;
    void startWalk();
    void stopWalk();

    // Attaques
    void startAttack(const std::string& attackName);
    bool isAttacking() const;

    // Mort
    void startDead();
    bool isDying() const;
    bool isDeadAnimationFinished() const;

    // Changer le chemin de base (pour changer de personnage)
    void setBasePath(const std::string& path);

private:
    SDL_Renderer* m_renderer;
    Animation m_currentAnimation;
    int m_direction;  
    int m_delayMs;    
    int m_width, m_height;
    std::string currentSprite; // juste le nom, ex: "idle", "walk", etc.
    bool m_isJumping;
    bool m_currentLoop;

    int m_startY;
    int m_jumpHeight;
    Uint32 m_walkStartTime;
    const Uint32 RUN_THRESHOLD = 500;

    bool m_isAttacking;
    bool m_isDying;
    std::string m_basePath; // chemin de base, ex: "assets/samurai"
};

#endif // SAMURAI_HPP
