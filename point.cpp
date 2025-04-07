#include "POINT.h"
#include <string>

Score::Score(Character& _character)
    : character(_character), score(0), lastUpdateTime(0), scoreTexture(nullptr), fontSmall(nullptr), fontLarge(nullptr) {}

void Score::init(Graphics& graphic) {
    if (TTF_Init() == -1) {
        graphic.logErrorAndExit("TTF_Init", TTF_GetError());
    }
    fontSmall = TTF_OpenFont("assets/ariblk.ttf", 36);
    fontLarge = TTF_OpenFont("assets/ariblk.ttf", 70);
    if (!fontSmall || !fontLarge) {
        graphic.logErrorAndExit("TTF_OpenFont", TTF_GetError());
    }
    color = {255, 255, 255, 255};
}

Score::~Score() {
    if (fontSmall) TTF_CloseFont(fontSmall);
    if (fontLarge) TTF_CloseFont(fontLarge);
    if (scoreTexture) SDL_DestroyTexture(scoreTexture);
    if (jumpCountTexture) SDL_DestroyTexture(jumpCountTexture);
    TTF_Quit();
}

void Score::update() {
    Uint32 currentTime = SDL_GetTicks();
     if (currentTime - lastUpdateTime >= 500) {
        score++;
        lastUpdateTime = currentTime;
    }
}

void Score::reset(Graphics& graphic) {
    score = 0;
    lastUpdateTime = SDL_GetTicks();
    updateTexture(graphic, false);
}

void Score::updateTexture(Graphics& graphic, bool isGameOver) {
    if (scoreTexture) SDL_DestroyTexture(scoreTexture);
    std::string scoreText = std::to_string(score);
    std::string jumpText = "Max jumps: " + std::to_string(character.maxJumpCount);

    TTF_Font* fontToUse = isGameOver ? fontLarge : fontSmall;
    SDL_Surface* surface = TTF_RenderText_Solid(fontToUse, scoreText.c_str(), color);
    SDL_Surface* surfacejump = TTF_RenderText_Solid(fontSmall, jumpText.c_str(), color);
    if (!surface || !surfacejump) {
        graphic.logErrorAndExit("TTF_RenderText_Solid", TTF_GetError());
    }
    scoreTexture = SDL_CreateTextureFromSurface(graphic.renderer, surface);
    jumpCountTexture = SDL_CreateTextureFromSurface(graphic.renderer, surfacejump);
    SDL_FreeSurface(surface);
    SDL_FreeSurface(surfacejump);
    if (!scoreTexture || !surfacejump) {
        graphic.logErrorAndExit("SDL_CreateTextureFromSurface", SDL_GetError());
    }
}

void Score::render(Graphics& graphic, int x1, int y1, int x2, int y2) {
    updateTexture(graphic, false);
    if (scoreTexture) {
        SDL_Rect destRect = {x1, y1, 50, 50};
        SDL_RenderCopy(graphic.renderer, scoreTexture, nullptr, &destRect);
    }
    if (jumpCountTexture) {
        SDL_Rect destRect = {x2, y2, 150, 50};
        SDL_RenderCopy(graphic.renderer, jumpCountTexture, nullptr, &destRect);
    }
}

void Score::renderGameOver(Graphics& graphic, int x, int y) {
    updateTexture(graphic, true);
    if (scoreTexture) {
        SDL_Rect destRect = {x, y, 200, 200};
        SDL_RenderCopy(graphic.renderer, scoreTexture, nullptr, &destRect);
    }
}

