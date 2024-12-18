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

        // Si le samouraï est en train de mourir et que l'animation dead est finie,
        // on peut quitter le jeu.
        if (samurai.isDying() && samurai.isDeadAnimationFinished()) {
            m_isRunning = false;
        }

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
            // Si on ferme la fenêtre, on lance dead si pas déjà dying
            if (!samurai.isDying()) {
                samurai.startDead();
            } else {
                // Si déjà dying, on laisse finir
            }
        } else if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
            processKeyDown(event.key.keysym.sym);
        } else if (event.type == SDL_KEYUP) {
            processKeyUp(event.key.keysym.sym);
        }
    }
}

void Game::processKeyDown(SDL_Keycode key) {
    std::cout << "Touche pressée : " << SDL_GetKeyName(key) << std::endl;

    // Si le samouraï est en train de mourir, on ignore tout
    if (samurai.isDying()) return;

    if (key == SDLK_ESCAPE) {
        // Lancer dead si pas déjà en train
        if (!samurai.isDying()) {
            samurai.startDead();
        }
    } else if (key == SDLK_RIGHT) {
        if (!samurai.isJumping() && !samurai.isAttacking() && !samurai.isDying()) {
            samurai.setDirection(1);
            samurai.startWalk();
        } else {
            samurai.setDirection(1);
        }
    } else if (key == SDLK_LEFT) {
        if (!samurai.isJumping() && !samurai.isAttacking() && !samurai.isDying()) {
            samurai.setDirection(-1);
            samurai.startWalk();
        } else {
            samurai.setDirection(-1);
        }
    } else if (key == SDLK_DOWN) {
        // Lance l'animation shield (si on n'est pas en saut, pas en attaque, pas en dying)
        if (!samurai.isJumping() && !samurai.isAttacking() && !samurai.isDying()) {
            samurai.setSprite("assets/samurai/shield", false);
        }
    } else if (key == SDLK_SPACE) {
        if (!samurai.isJumping() && !samurai.isAttacking() && !samurai.isDying()) {
            samurai.startJump();
        }
    } else if (key == SDLK_e) {
        if (!samurai.isJumping() && !samurai.isAttacking() && !samurai.isDying()) {
            samurai.startAttack("assets/samurai/attack_1");
        }
    } else if (key == SDLK_r) {
        if (!samurai.isJumping() && !samurai.isAttacking() && !samurai.isDying()) {
            samurai.startAttack("assets/samurai/attack_2");
        }
    } else if (key == SDLK_t) {
        if (!samurai.isJumping() && !samurai.isAttacking() && !samurai.isDying()) {
            samurai.startAttack("assets/samurai/attack_3");
        }
    }
}

void Game::processKeyUp(SDL_Keycode key) {
    std::cout << "Touche relâchée : " << SDL_GetKeyName(key) << std::endl;

    if (samurai.isDying()) return;

    // Quand on relâche les flèches droite/gauche, si pas en saut, pas en attaque, pas en dying
    if ((key == SDLK_RIGHT || key == SDLK_LEFT) && !samurai.isJumping() && !samurai.isAttacking() && !samurai.isDying()) {
        samurai.stopWalk();
    }

    if (key == SDLK_DOWN && !samurai.isJumping() && !samurai.isAttacking() && !samurai.isDying()) {
        // Revenir à idle après le shield
        samurai.setSprite("assets/samurai/idle", true);
    }
}

void Game::update() {
    // Logique supplémentaire si besoin
}

void Game::render() {
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);

    samurai.updateAndRender();

    SDL_RenderPresent(m_renderer);
}
