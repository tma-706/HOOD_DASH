#include "GAMEPLAY.h"

Game::Game() : running(true), state(MENU), score(player) {}

Game::~Game(){
    if (menuTexture) SDL_DestroyTexture(menuTexture);
    if (guideTexture) SDL_DestroyTexture(guideTexture);
    if (gameOverTexture) SDL_DestroyTexture(gameOverTexture);
    music.stopMusic();
    graphic.quit();
}

void Game::init() {
    graphic.init();

    SDL_Texture* bgTexture = graphic.loadTexture(BACKGROUND_IMG);
    background.setTexture(bgTexture);

    menuTexture = graphic.loadTexture("assets/menu.png");
    guideTexture = graphic.loadTexture("assets/guide.png");
    gameOverTexture = graphic.loadTexture("assets/gameover.png");

    player.init(graphic);
    enemy.init(graphic);
    score.init(graphic);
    applee.init(graphic);
    music.init(BGMUSIC, graphic);
    music.playMusic();
}

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
        else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_SPACE:
                    if (state == MENU || state == GUIDE) {
                        state = GAMEPLAY;
                        reset();
                    }
                    if(state == GAMEOVER) {
                        state = GAMEPLAY;
                        reset();
                    }
                    break;
                case SDLK_q:
                    if (state == MENU) state = GUIDE;
                    break;
                case SDLK_a:
                    if (state == GAMEOVER) state = MENU;
                    break;
                case SDLK_ESCAPE:
                    running = false;
                    break;
            }
        }
    }
    const Uint8* keystate = SDL_GetKeyboardState(NULL);
        player.handleInput(keystate);
}

void Game::update() {
    if (state != GAMEPLAY) return;

    background.scroll(velo);
    player.update();
    enemy.spawnEnemy();
    enemy.updateEnemy();
    score.update();
    applee.spawnApple();
    applee.updateApple();
    collision.eatApple(player,applee,score);
    collision.changeToDeath(player, enemy.getOnScrEnemy());
    if (player.isDead) {
        state = GAMEOVER;
    }
}

void Game::render() {
    //SDL_Log("Rendering state: %d", state);
    graphic.prepareScene(nullptr);

    if (state == MENU) {
        //SDL_Log("Rendering MENU");
        graphic.renderTexture(menuTexture, 0, 0,1);
    }
    else if (state == GUIDE) {
        //SDL_Log("Rendering GUIDE");
        graphic.renderTexture(guideTexture, 0, 0,1);
    }
    else if (state == GAMEPLAY) {
        //SDL_Log("Rendering GAMEPLAY");
        SDL_RenderClear(graphic.renderer);
        graphic.renderScreen(background);
        enemy.renderEnemy(graphic);
        player.render(graphic);
        score.render(graphic, 30, 10, 30, 60);
        applee.renderApple(graphic);
    }
    else if (state == GAMEOVER) {
        graphic.renderTexture(gameOverTexture, 0, 0,1);
        score.renderGameOver(graphic, 230, 200);
    }

    graphic.presentScene();
}

void Game::reset() {
    player.reset();
    enemy.reset();
    score.reset(graphic);
    background.scrollingOffset = 0;
    state = GAMEPLAY;
    player.isDead=false;
    applee.reset();
    music.stopMusic();
    music.playMusic();
}

void Game::run() {
    while (running) {
        handleEvents();
        update();
        render();
        SDL_Delay(25);
    }
}
