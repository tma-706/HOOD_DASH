#include "APPLE.h"
#include <ctime>
#include <cstdlib>
#include <iostream>

Apple::Apple(SDL_Texture* _texture, int _x, int _y, int _speed)
    : texture(_texture), a_x(_x), a_y(_y), a_speed(_speed), collected(false) {
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void Apple::update() {
    a_x -= a_speed;
}

bool Apple::isOffScreen() {
    return a_x + width * 3 < 0;
}

void Apple::render(Graphics& graphic) {
    graphic.renderTexture(texture, a_x, a_y, appleRat);
}

SDL_Rect Apple::getRect() const {
    return {a_x, a_y, width * appleRat, height * appleRat};
}

//****************************************************************************

appleManager::appleManager() : spawnInterval(7000) {
    srand(time(0));
    lastSpawnTime = 0;
}

void appleManager::init(Graphics& graphic) {
    appleimg = graphic.loadTexture(apple);
}

void appleManager::spawnApple() {
    Uint32 now = SDL_GetTicks();
    if (now - lastSpawnTime >= (Uint32)spawnInterval) {
        lastSpawnTime = now;
        int width, height;
        SDL_QueryTexture(appleimg, NULL, NULL, &width, &height);
        int speed = velo;
        int yPos = SCREEN_HEIGHT - GROUND_LEVEL - height * appleRat - rand() % 301;
        applesOnScreen.push_back(Apple(appleimg, SCREEN_WIDTH, yPos, speed));
    }
}

void appleManager::updateApple() {
    for (int i = 0; i < applesOnScreen.size();) {
        applesOnScreen[i].update();
        if (applesOnScreen[i].isCollected() || applesOnScreen[i].isOffScreen()) {
            applesOnScreen.erase(applesOnScreen.begin() + i);
        } else {
            ++i;
        }
    }
}

void appleManager::renderApple(Graphics& graphic) {
    for (Apple& apple_in : applesOnScreen) {
        apple_in.render(graphic);
    }
}

std::vector<SDL_Rect> appleManager::getOnScrApple() const {
    std::vector<SDL_Rect> sz_of_onscr_apple;
    for (const Apple& apple_in : applesOnScreen) {
        sz_of_onscr_apple.push_back(apple_in.getRect());
    }
    return sz_of_onscr_apple;
}

appleManager::~appleManager() {
    SDL_DestroyTexture(appleimg);
    applesOnScreen.clear();
}

void appleManager::reset() {
    applesOnScreen.clear();
    lastSpawnTime = 0;
}
