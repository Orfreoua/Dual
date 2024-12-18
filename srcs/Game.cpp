#include "../headers/Game.hpp"

Game::Game()
    : m_window(nullptr), m_renderer(nullptr), m_isRunning(false), samurai(100, 100) {}

Game::~Game() {
    cleanUp();
}

bool Game::init(const char* title, int width, int height, bool fullscreen) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Erreur SDL: " << SDL_GetError() << std::endl;
        return false;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) {
        std::cerr << "Erreur SDL_Image: " << IMG_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    Uint32 flags = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;

    m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
    if (!m_window) {
        std::cerr << "Erreur SDL_CreateWindow: " << SDL_GetError() << std::endl;
        return false;
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    if (!m_renderer) {
        std::cerr << "Erreur SDL_CreateRenderer: " << SDL_GetError() << std::endl;
        return false;
    }

    samurai.init(m_renderer);

    m_isRunning = true;
    return true;
}

void Game::run() {
    while (m_isRunning) {
        handleEvents();
        update();
        render();
        SDL_Delay(16);
    }
}

void Game::cleanUp() {
    samurai.cleanUp();

    if (m_renderer) SDL_DestroyRenderer(m_renderer);
    if (m_window) SDL_DestroyWindow(m_window);

    IMG_Quit();
    SDL_Quit();
}

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            m_isRunning = false;
        } else if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
            processKeyDown(event.key.keysym.sym);
        } else if (event.type == SDL_KEYUP) {
            processKeyUp(event.key.keysym.sym);
        }
    }
}

void Game::processKeyDown(SDL_Keycode key) {
    std::cout << "Touche pressée : " << SDL_GetKeyName(key) << std::endl;

    if (key == SDLK_ESCAPE) {
        m_isRunning = false;
    } else if (key == SDLK_RIGHT) {
        samurai.setSprite("assets/samurai/walk", true);
        samurai.setDirection(1);
        samurai.setPosition(samurai.getX() + 5, samurai.getY());
    } else if (key == SDLK_LEFT) {
        samurai.setSprite("assets/samurai/walk", true);
        samurai.setDirection(-1);
        samurai.setPosition(samurai.getX() - 5, samurai.getY());
    } else if (key == SDLK_SPACE) {
        // Lancer le saut uniquement si non déjà en saut
        if (!samurai.isJumping()) {
            samurai.startJump();
        }
    }
}

void Game::processKeyUp(SDL_Keycode key) {
    std::cout << "Touche relâchée : " << SDL_GetKeyName(key) << std::endl;

    if (key == SDLK_RIGHT || key == SDLK_LEFT) {
        samurai.setSprite("assets/samurai/idle", true);
    }
    // Ne pas arrêter le saut au relâchement de la touche, c'est géré par l'animation
}

void Game::update() {
    // Logique si besoin
}

void Game::render() {
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);

    samurai.updateAndRender();

    SDL_RenderPresent(m_renderer);
}
