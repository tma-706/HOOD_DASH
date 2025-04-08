#include "COLLIDE.h"
#include <iostream>


bool Collision::checkCollisions(const SDL_Rect& mainCharacter, const std::vector<SDL_Rect>& entities) {
    for (const auto& entityRect : entities) {
        if(mainCharacter.x + int(mainCharacter.w * spriteRat) >= entityRect.x + 150 &&
            mainCharacter.x <= entityRect.x + entityRect.w - 60 &&
            mainCharacter.y + mainCharacter.h * spriteRat >= entityRect.y + 120) {
            std::cout << "Collision detected! Player at (" << mainCharacter.x << ", " << mainCharacter.y
                      << ") collided with entity at (" << entityRect.x << ", " << entityRect.y << ")\n";
            return true;
        }
    }
    return false;
}

void Collision::changeToDeath(Character& character, const std::vector<SDL_Rect>& entities, const std::vector<SDL_Rect>& rockets) {
    if(checkCollisions(character.charGetRect(), entities)) {
        character.isDead = true;
        std::cout << "Character died due to collision!\n";
    }
    SDL_Rect characterRect = character.charGetRect();
     for (const auto& rocketRect : rockets) {
        if (characterRect.x + int(characterRect.w * spriteRat) >= rocketRect.x + 100 &&
            characterRect.x <= rocketRect.x + rocketRect.w - 40 &&
            //characterRect.y + characterRect.h * spriteRat >= rocketRect.y + 100 &&
            characterRect.y <= rocketRect.y + rocketRect.h * appleRat - 160) {
            character.isDead = true;
            std::cout << "Character died due to ROCKET explosion!\n";
            break;
        }
    }
}

void Collision::eatApple(Character& character, appleManager& appleMgr, Score& scoreIncrease) {
    std::vector<SDL_Rect> apples = appleMgr.getOnScrApple();
    for (int i = 0; i < apples.size(); ++i) {
        SDL_Rect characterRect = character.charGetRect();
        if (characterRect.x + int(characterRect.w * spriteRat) >= apples[i].x + 120 &&
            characterRect.x <= apples[i].x + apples[i].w - 60 &&
            characterRect.y + characterRect.h * spriteRat >= apples[i].y + 130 &&
            characterRect.y <= apples[i].y + apples[i].h * appleRat - 50 &&
            !appleMgr.applesOnScreen[i].isCollected()) {
            appleMgr.applesOnScreen[i].setCollected(true);

            if (character.maxJumpCount >= 4) {
                character.maxJumpCount = 4;
                scoreIncrease.score += 20;
            } else {
                character.maxJumpCount++;
                character.newjumpHeight += 1;
            }
            break;
        }
    }
}
