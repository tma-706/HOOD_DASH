#include "ENEMY.h"
#include <ctime>
#include <cstdlib>
//#include <iostream>

Enemy::Enemy(SDL_Texture* _texture, int _x, int _y, int _speed)
    : texture(_texture), e_x(_x), e_y(_y), e_speed(_speed) {
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void Enemy::update() {
    e_x -= e_speed;
}

bool Enemy::isOffScreen() {
    return e_x + width*enemyRat < 0;
}

void Enemy::render(Graphics& graphic) {
    graphic.renderTexture(texture, e_x, e_y, enemyRat);
}

SDL_Rect Enemy::getRect() const {
    return {e_x, e_y, width*enemyRat, height*enemyRat};
}

//********************************************************

enemyManager::enemyManager() : spawnInterval(2500) {
    srand(time(0));
    lastSpawnTime = 0;
    lastIncreaseTime = 0;
}

void enemyManager::init(Graphics& graphic) {
    SDL_Texture* blue_golem = graphic.loadTexture(BLUE_GOLEM);
    SDL_Texture* orange_golem = graphic.loadTexture(ORANGE_GOLEM);
    enemyTextures.push_back(blue_golem);
    enemyTextures.push_back(orange_golem);
}

void enemyManager::spawnEnemy() {
    if (enemiesOnScreen.size() >= maxEnemyNum) return; // Giới hạn số lượng enemy tối đa (sẽ tăng)
    Uint32 now = SDL_GetTicks();

    if (now - lastIncreaseTime >= 45000) {
        if(maxEnemyNum>=5) {
            maxEnemyNum=5;
        }
        else {
        maxEnemyNum += 1;  // Tăng số lượng tối đa enemy sau mỗi 45s
        lastIncreaseTime = now;
        }
    }
    int spawnVariation = rand() % 2;  // 0 hoặc 1, để quyết định spawn nhanh hoặc lâu
    int minSpawn, maxSpawn;

    if (spawnVariation == 0) {
        minSpawn = 300;   // Spawn nhanh
        maxSpawn = 1500;
    } else {
        minSpawn = 2000;  // Spawn lâu hơn
        maxSpawn = 3000;
    }
    if (now - lastSpawnTime >= (Uint32)spawnInterval) {
        lastSpawnTime = now;
        // Random khoảng thời gian giữa các lần spawn
        spawnInterval = minSpawn + rand() % (maxSpawn - minSpawn + 1);
        int typeInd = rand() % enemyTextures.size();
        int width, height;
        SDL_QueryTexture(enemyTextures[typeInd], NULL, NULL, &width, &height);
        int yPos = SCREEN_HEIGHT - GROUND_LEVEL - height*enemyRat;
        int speed = velo;
        enemiesOnScreen.push_back(Enemy(enemyTextures[typeInd], SCREEN_WIDTH, yPos, speed));
    }
}


void enemyManager::updateEnemy() {
    for (int i = 0; i < enemiesOnScreen.size();) {
        enemiesOnScreen[i].update();
        if (enemiesOnScreen[i].isOffScreen()) {
            enemiesOnScreen.erase(enemiesOnScreen.begin() + i);
        } else {
            ++i;
        }
    }
}

void enemyManager::renderEnemy(Graphics& graphic) {
    for (Enemy& enemy_in : enemiesOnScreen) {
        enemy_in.render(graphic);
    }
}

std::vector<SDL_Rect> enemyManager::getOnScrEnemy() const {
    std::vector<SDL_Rect> sz_of_onscr_enemy;
    for (const Enemy& enemy_in : enemiesOnScreen) {
        sz_of_onscr_enemy.push_back(enemy_in.getRect());
    }
    return sz_of_onscr_enemy;
}

enemyManager::~enemyManager() {
    for (auto tex : enemyTextures) {
        SDL_DestroyTexture(tex);
    }
    enemyTextures.clear();
    enemiesOnScreen.clear();
}

void enemyManager::reset() {
    enemiesOnScreen.clear();
    lastSpawnTime = 0;
}
