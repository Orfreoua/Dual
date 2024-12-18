#ifndef SAMURAI_HPP
#define SAMURAI_HPP

#include "Character.hpp"
#include "Animation.hpp"
#include <string>

class Samurai : public Character {
public:
    Samurai(int x = 0, int y = 0);

    void init(SDL_Renderer* renderer);
    void setSprite(const std::string& spritePath);
    void updateAndRender();
    void setDirection(int dir);
    void cleanUp();

private:
    SDL_Renderer* m_renderer;
    Animation m_currentAnimation;
    int m_direction;  
    int m_delayMs;    
    int m_width, m_height;
    std::string currentSprite;
};

#endif // SAMURAI_HPP

/*	std::string	attack_1	= "assets/samurai/attack_1";
	std::string	attack_2	= "assets/samurai/attack_2";
	std::string	attack_3	= "assets/samurai/attack_3";
	std::string	dead		= "assets/samurai/dead";
	std::string	hurt		= "assets/samurai/hurt";
	std::string	idle		= "assets/samurai/idle";
	std::string	jump		= "assets/samurai/jump";
	std::string	run			= "assets/samurai/run";
	std::string	shield		= "assets/samurai/shield";
	std::string	walk		= "assets/samurai/walk";*/
