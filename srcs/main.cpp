#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>

namespace fs = std::filesystem;

// Fonction pour charger tous les fichiers d'un dossier
std::vector<std::string> getSpriteFiles(const std::string& folderPath) {
    std::vector<std::string> files;
    if (!fs::exists(folderPath)) {
        std::cerr << "Le dossier " << folderPath << " n'existe pas ou est introuvable !" << std::endl;
        return files;
    }
    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (entry.is_regular_file()) {
            files.push_back(entry.path().string());
        }
    }
    // Trier les fichiers par ordre alphabétique
    std::sort(files.begin(), files.end());
    return files;
}

// Fonction pour afficher les sprites d'un dossier avec une animation
void playSpriteAnimation(SDL_Renderer* renderer, const std::string& folderPath, int x, int y, int width, int height, int delayMs) {
    // Charger les fichiers des sprites
    std::vector<std::string> spriteFiles = getSpriteFiles(folderPath);
    if (spriteFiles.empty()) {
        std::cerr << "Aucun fichier sprite valide trouvé dans le dossier : " << folderPath << std::endl;
        return;
    }

    // Charger les textures des sprites
    std::vector<SDL_Texture*> textures;
    for (const std::string& filePath : spriteFiles) {
        SDL_Surface* surface = IMG_Load(filePath.c_str());
        if (!surface) {
            std::cerr << "Erreur IMG_Load: " << IMG_GetError() << " pour le fichier " << filePath << std::endl;
            continue;
        }
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        if (!texture) {
            std::cerr << "Erreur SDL_CreateTextureFromSurface: " << SDL_GetError() << " pour le fichier " << filePath << std::endl;
            continue;
        }
        textures.push_back(texture);
    }

    if (textures.empty()) {
        std::cerr << "Aucune texture valide trouvée." << std::endl;
        return;
    }

    // Jouer l'animation
    bool running = true;
    SDL_Event event;
    size_t currentFrame = 0;
    Uint32 lastFrameTime = SDL_GetTicks();

    while (running) {
        // Gestion des événements
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Dessiner le sprite actuel
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - lastFrameTime >= static_cast<Uint32>(delayMs)) {
            currentFrame = (currentFrame + 1) % textures.size();
            lastFrameTime = currentTime;
        }

        SDL_RenderClear(renderer);

        SDL_Rect destRect = {x, y, width, height};
        SDL_RenderCopy(renderer, textures[currentFrame], nullptr, &destRect);

        SDL_RenderPresent(renderer);
    }

    // Nettoyer les textures
    for (SDL_Texture* texture : textures) {
        SDL_DestroyTexture(texture);
    }
}

int main(int argc, char **argv) {
    (void)argc;
    (void)argv;

    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Erreur SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Initialisation de SDL_Image
    if (IMG_Init(IMG_INIT_PNG) == 0) {
        std::cerr << "Erreur SDL_Image: " << IMG_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Créer une fenêtre
    SDL_Window* window = SDL_CreateWindow("Animation de Sprite",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          800, 600, SDL_WINDOW_SHOWN);

    if (!window) {
        std::cerr << "Erreur SDL_CreateWindow: " << SDL_GetError() << std::endl;
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // Créer un renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Erreur SDL_CreateRenderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // Jouer l'animation des sprites avec une vérification du dossier
    playSpriteAnimation(renderer, "assets/attack_1", 100, 100, 200, 150, 200);

    // Nettoyage
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
