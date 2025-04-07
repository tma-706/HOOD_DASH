#ifndef STATEMACHINE_H_INCLUDED
#define STATEMACHINE_H_INCLUDED
#include "GRAPHICS.h"
#include "DEF.h"
#include "SDL.h"
#include <map>

enum State {RUNNING, JUMPING, FALLING};

class Character {
public:
    bool isDead = false;
    void init(Graphics& graphic);
    void handleInput(const Uint8* keyState);
    void update();
    void render(Graphics& graphic);
    void changeState(State newState);
    void reset();
    int getX() const {return x;}
    int getY() const {return y;}
    SDL_Rect charGetRect() const;
    State getState() {return state;}
    ~Character();
    int maxJumpCount=2; //số lần nhảy
    int jumpHeight=-17; //độ cao nhảy
    int newjumpHeight=-17; //độ cao nhảy mới sau khi ăn táo

private:
    int jumpcount = 0;
    std::map <State, Sprite> sprites;
    int x = 50;
    int y = SCREEN_HEIGHT - GROUND_LEVEL - mainchar * spriteRat;
    int gravity = 1;
    int velocityY = 0;
    bool isOnAir = false;
    bool jumpAnimationFinished = false;
    bool fallAnimationFinished = false;
    bool jumpPressed = false;
    State state = RUNNING;
};
#endif // STATEMACHINE_H_INCLUDED
