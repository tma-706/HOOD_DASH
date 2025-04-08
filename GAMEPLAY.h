#ifndef GAMEPLAY_H_INCLUDED
#define GAMEPLAY_H_INCLUDED
#include "STATEMACHINE.h"
#include "ENEMY.h"
#include "POINT.h"
#include "COLLIDE.h"
#include "APPLE.h"
#include "MUSIC.h"
#include "ROCKET.h"

enum GameState { MENU, GUIDE, GAMEPLAY, GAMEOVER };

class Game {
public:
    Game();
    ~Game();
    void init();
    void run();
    void handleEvents();
    void update();
    void render();
    void reset();

private:
    bool running;
    GameState state;
    Graphics graphic;
    Character player;
    enemyManager enemy;
    ScrollingBackground background;
    Score score;
    appleManager applee;
    rocketManager rockets;
    Music music;
    SDL_Texture* menuTexture;
    Collision collision;
    SDL_Texture* guideTexture;
    SDL_Texture* gameOverTexture;
};


#endif // GAME_H_INCLUDED
