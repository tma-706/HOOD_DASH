#ifndef COLLISION_H_INCLUDED
#define COLLISION_H_INCLUDED
#include <vector>
#include <SDL.h>
#include "POINT.h"
#include "STATEMACHINE.h"
#include "APPLE.h"
struct Collision {

    bool checkCollisions(const SDL_Rect& mainCharacter, const std::vector<SDL_Rect>& entities);
    void changeToDeath(Character& character, const std::vector<SDL_Rect>& entities, const std::vector<SDL_Rect>& rockets);
    void eatApple(Character& character, appleManager& appleMgr, Score& scoreIncrease);
};


#endif // COLLISION_H_INCLUDED
