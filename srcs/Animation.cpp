#include "../headers/Animation.hpp"
#include <algorithm>
#include <filesystem>
#include <iostream>
#include <SDL2/SDL_image.h>

std::vector<std::string> getSpriteFiles(const std::string& folderPath) {
    std::vector<std::string> files;
    for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
        if (entry.is_regular_file()) {
            files.push_back(entry.path().string());
        }
    }
    std::sort(files.begin(), files.end());
    return files;
}

Animation loadAnimation(SDL_Renderer* renderer, const std::string& folderPath) {
    Animation anim;
    std::vector<std::string> spriteFiles = getSpriteFiles(folderPath);
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
        anim.frames.push_back(texture);
    }

    if (anim.frames.empty()) {
        std::cerr << "Aucune frame chargée pour l'animation dans : " << folderPath << std::endl;
    }

    anim.lastFrameTime = SDL_GetTicks();
    anim.currentFrame = 0;

    return anim;
}

void updateAndRenderAnimation(SDL_Renderer* renderer, Animation& anim, int x, int y, int width, int height, int delayMs, int flipDirection) {
    if (anim.frames.empty()) return;

    SDL_RendererFlip flip = (flipDirection < 0) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - anim.lastFrameTime >= static_cast<Uint32>(delayMs)) {
        anim.currentFrame = (anim.currentFrame + 1) % anim.frames.size();
        anim.lastFrameTime = currentTime;
    }

    SDL_Rect destRect = { x, y, width, height };
    SDL_RenderCopyEx(renderer, anim.frames[anim.currentFrame], nullptr, &destRect, 0, nullptr, flip);
}

void destroyAnimation(Animation& anim) {
    for (auto& tex : anim.frames) {
        SDL_DestroyTexture(tex);
    }
    anim.frames.clear();
}
