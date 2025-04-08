#ifndef ROCKET_H_INCLUDED
#define ROCKET_H_INCLUDED
#include "GRAPHICS.h"
#include <vector>
#include "STATEMACHINE.h"

class Rocket {
public:
    Rocket(SDL_Texture* missileTexture, Sprite* explosionSprite, int x, int y, int speed);
    void update();
    void render(Graphics& graphic);
    bool hasExploded() const;
    SDL_Rect getRect() const;
    bool isOffScreen() const;
    Sprite* explosionSprite; // Con trỏ tới sprite animation nổ (chung từ rocketManager)

private:
    SDL_Texture* texture;
    int x, y;
    int speed;
    int width, height;
    bool exploded;
    Uint32 explosionStartTime; // Thời gian bắt đầu animation nổ
};

class rocketManager {
public:
    rocketManager();
    ~rocketManager();
    void init(Graphics& graphic);
    void spawnRocket(int targetX);
    void updateRocket(Character& player);
    void renderRocket(Graphics& graphic);
    void reset();
    bool isWarningActive() const {return warningActive;}
    SDL_Rect getWarningRect() const;
    std::vector<SDL_Rect> getOnScrRocket() const;

private:
    std::vector<Rocket> rocketsOnScreen;
    SDL_Texture* missileTexture;
    Sprite explosionSprite;
    Sprite warningSprite;        // Sprite animation cho cảnh báo
    Uint32 lastSpawnTime;
    Uint32 spawnInterval;        // 10 giây
    bool warningActive;
    Uint32 warningStartTime;
    const int warningDuration = 1000; // 1 giây cảnh báo
    int targetX;                 // Tọa độ x mục tiêu ban đầu
};

#endif // ROCKET_H_INCLUDED
