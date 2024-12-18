#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <SDL2/SDL.h>
#include <string>
#include <vector>

struct Animation {
    std::vector<SDL_Texture*> frames;
    size_t currentFrame = 0;
    Uint32 lastFrameTime = 0;
};

Animation loadAnimation(SDL_Renderer* renderer, const std::string& folderPath);
void updateAndRenderAnimation(SDL_Renderer* renderer, Animation& anim, int x, int y, int width, int height, int delayMs, int flipDirection, bool loop = true);
void destroyAnimation(Animation& anim);

#endif // ANIMATION_HPP
