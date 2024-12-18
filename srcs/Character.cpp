#include "../headers/Character.hpp"

Character::Character(int x, int y) : m_x(x), m_y(y) {}

int Character::getX() const {
    return m_x;
}

int Character::getY() const {
    return m_y;
}

void Character::setPosition(int x, int y) {
    m_x = x;
    m_y = y;
}
