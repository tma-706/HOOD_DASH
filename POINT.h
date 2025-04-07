#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED
#include "SDL.h"
#include "SDL_ttf.h"
#include "GRAPHICS.h"
#include "STATEMACHINE.h"

class Score {
public:
    Score(Character& _character);
    ~Score();
    void init(Graphics& graphic);
    void update();
    void reset(Graphics& graphic);
    void renderGameOver(Graphics& graphic, int x, int y);
    void render(Graphics& graphic, int x1, int y1, int x2, int y2);
    int score;
private:
    Character& character;
    Uint32 lastUpdateTime;
    TTF_Font* fontSmall;
    TTF_Font* fontLarge;
    SDL_Color color;
    SDL_Texture* scoreTexture;
    SDL_Texture* jumpCountTexture;
    void updateTexture(Graphics& graphic, bool isGameOver);
};

#endif // SCORE_H_INCLUDED
