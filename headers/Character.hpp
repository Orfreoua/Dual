#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <string>
#include <SDL2/SDL.h>

class Character {
public:
    Character(int x = 0, int y = 0);

    int getX() const;
    int getY() const;

    void setPosition(int x, int y);

protected:
    int m_x, m_y; // Position du personnage
};

#endif // CHARACTER_HPP
