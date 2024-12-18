#include "../headers/Game.hpp"

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;
    Game game;

    if (!game.init("Mon Jeu", 800, 600, false)) {
        std::cerr << "Échec de l'initialisation du jeu." << std::endl;
        return 1;
    }

    game.run();
    return 0;
}
