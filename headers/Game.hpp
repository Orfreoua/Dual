#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "Character.hpp"
#include "Samurai.hpp"

class Game {
public:
    Game();
    ~Game();

    bool init(const char* title, int width, int height, bool fullscreen);
    void run();
    void cleanUp();

private:
    void handleEvents();
    void processKeyDown(SDL_Keycode key);
    void processKeyUp(SDL_Keycode key);
    void update();
    void render();

    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    bool m_isRunning;

    Samurai samurai; // Samurai géré en membre de Game
};

#endif // GAME_HPP
