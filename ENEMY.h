#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED
#include <vector>
#include "SDL.h"
#include "GRAPHICS.h"

class Enemy {
public:
    Enemy(SDL_Texture* _texture, int _x, int _y, int _speed);
    void update();
    void render(Graphics& graphic);
    bool isOffScreen();
    SDL_Rect getRect() const;
private:
    SDL_Texture* texture;
    int e_x;
    int e_y;
    int e_speed;
    int width;
    int height;
};

class enemyManager {
public:
    enemyManager();
    void init(Graphics& graphic);
    void spawnEnemy();
    void updateEnemy();
    void renderEnemy(Graphics& graphic);
    std::vector<SDL_Rect> getOnScrEnemy() const;
    void reset();
    ~enemyManager();
    int maxEnemyNum = 5;
private:
    std::vector<SDL_Texture*> enemyTextures;
    std::vector<Enemy> enemiesOnScreen;
    Uint32 lastSpawnTime;
    Uint32 lastIncreaseTime;
    int spawnInterval;
};

#endif // ENEMY_H_INCLUDED
