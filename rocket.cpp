#include "ROCKET.h"
#include <cstdlib>
#include <ctime>

Rocket::Rocket(SDL_Texture* missileTexture, Sprite* explosionSprite, int x, int y, int speed)
    : texture(missileTexture), explosionSprite(explosionSprite), x(x), y(y), speed(speed), exploded(false), explosionStartTime(0) {
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void Rocket::update() {
    if (!exploded) {
        y += speed;
        if (y >= SCREEN_HEIGHT - GROUND_LEVEL - height*2.5) {
            y = SCREEN_HEIGHT - GROUND_LEVEL - height*2.5;
            exploded = true;
            explosionStartTime = SDL_GetTicks();
            explosionSprite->currentFrame = 0;
        }
    } else {
        Uint32 now = SDL_GetTicks();
        if (now - explosionStartTime >= 100) {
            explosionSprite->tick();
            explosionStartTime = now;
        }
    }
}

void Rocket::render(Graphics& graphic) {
    if (exploded) {
        graphic.renderAni(x - mainchar * spriteRat - 70, y - 230, *explosionSprite);
    } else {
        graphic.renderTexture(texture, x, y, appleRat);
    }
}

bool Rocket::hasExploded() const {
    return exploded;
}
SDL_Rect Rocket::getRect() const {
    return {x, y, width * appleRat, height * appleRat};
}

//********************************************************************

rocketManager::rocketManager()
    : spawnInterval(10000), lastSpawnTime(0), warningActive(false), warningStartTime(0), targetX(0), missileTexture(nullptr) {
    srand(time(0));
}

void rocketManager::init(Graphics& graphic) {
    missileTexture = graphic.loadTexture(MISSILE);
    explosionSprite.init(graphic.loadTexture(EXPLODE), EXPLODE_CLIPS, EXPLODE_FRAMES);
    warningSprite.init(graphic.loadTexture(WARN), WARN_CLIPS, WARN_FRAMES);
}

void rocketManager::spawnRocket(int targetX) {
    Uint32 now = SDL_GetTicks();
    if (now - lastSpawnTime >= spawnInterval && !warningActive) {
        this->targetX = targetX;
        warningActive = true;
        warningStartTime = now;
        warningSprite.currentFrame = 0;
    }
    if (warningActive && (now - warningStartTime >= warningDuration)) {
        int width, height;
        SDL_QueryTexture(missileTexture, NULL, NULL, &width, &height);
        Rocket newRocket(missileTexture, &explosionSprite, this->targetX, -height, 20);
        rocketsOnScreen.push_back(newRocket);
        lastSpawnTime = now;
        warningActive = false;
    }
}

void rocketManager::updateRocket(Character& player) {
    spawnRocket(player.getX());
    for (size_t i = 0; i < rocketsOnScreen.size();) {
        rocketsOnScreen[i].update();
        if (rocketsOnScreen[i].hasExploded() && rocketsOnScreen[i].explosionSprite->currentFrame >= EXPLODE_FRAMES - 1) {
            rocketsOnScreen.erase(rocketsOnScreen.begin() + i); // Chỉ xóa sau khi nổ xong
        }
        else {
            ++i;
        }
    }
}

void rocketManager::renderRocket(Graphics& graphic) {
    if (warningActive) {
        int warnX = SCREEN_WIDTH - warningSprite.getWidth() - 300;
        int warnY = 20;
        warningSprite.tick();
        graphic.renderAni(warnX, warnY, warningSprite);
    }

    for (Rocket& rocket : rocketsOnScreen) {
        rocket.render(graphic);
    }
}

void rocketManager::reset() {
    rocketsOnScreen.clear();
    lastSpawnTime = 0;
    warningActive = false;
    targetX = 0;
    warningSprite.currentFrame = 0;
    explosionSprite.currentFrame = 0;
    lastSpawnTime = SDL_GetTicks();
}

std::vector<SDL_Rect> rocketManager::getOnScrRocket() const {
    std::vector<SDL_Rect> onScreenRockets;
    for (const Rocket& rocket : rocketsOnScreen) {
        onScreenRockets.push_back(rocket.getRect());
    }
    return onScreenRockets;
}

rocketManager::~rocketManager() {
    rocketsOnScreen.clear();
}
