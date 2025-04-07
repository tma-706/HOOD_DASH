#ifndef APPLE_H_INCLUDED
#define APPLE_H_INCLUDED
#include "GRAPHICS.h"
#include "STATEMACHINE.h"
#include <vector>

class Apple {
public:
    Apple(SDL_Texture* _texture, int _x, int _y, int _speed);
    void render(Graphics& graphic);
    void update();
    bool isOffScreen();
    SDL_Rect getRect() const;
    bool isCollected() const { return collected; }
    void setCollected(bool value) { collected = value; }
private:
    SDL_Texture* texture;
    int a_x;
    int a_y;
    int a_speed;
    int width;
    int height;
    bool collected=false;
};

class appleManager {
public:
    appleManager();
    void init(Graphics& graphic);
    void spawnApple();
    void renderApple(Graphics& graphic);
    void updateApple();
    //void checkEat(Character& mainCharacter, Score& score);
    void reset();
    ~appleManager();
    std::vector<SDL_Rect> getOnScrApple() const;
    std::vector<Apple> applesOnScreen;

private:

    SDL_Texture* appleimg;
    Uint32 lastSpawnTime;
    int spawnInterval;

};
#endif // APPLE_H_INCLUDED
