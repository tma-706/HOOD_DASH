#include "STATEMACHINE.h"
//#include <iostream>

void Character::init(Graphics& graphic) {
    sprites[RUNNING].init(graphic.loadTexture(MAIN_RUN), MAIN_RUN_CLIPS, MAIN_RUN_FRAMES);
    sprites[JUMPING].init(graphic.loadTexture(MAIN_JUMP), MAIN_JUMP_CLIPS, MAIN_JUMP_FRAMES);
    sprites[FALLING].init(graphic.loadTexture(MAIN_FALL), MAIN_FALL_CLIPS, MAIN_FALL_FRAMES);
}

void Character::handleInput(const Uint8* keyState) {
    if (keyState[SDL_SCANCODE_SPACE]) {
        if (!jumpPressed && jumpcount < maxJumpCount) {
            jumpPressed = true; // Đánh dấu phím SPACE đã được bấm
            changeState(JUMPING);
            isOnAir = true;
            velocityY = jumpHeight;
            jumpcount++;
            //std::cout << "Jump count: " << jumpcount << std::endl;
        }
    }
    else {
        jumpPressed = false; // Khi nhả phím, reset biến này
    }
    if(keyState[SDL_SCANCODE_LEFT]) {
        if(!isOnAir) {
            x -= 3;
            if(x <= 0) {
                x = 0;
            }
        }
    }
    if(keyState[SDL_SCANCODE_RIGHT]) {
        if(!isOnAir) {
            x += 3;
            if(x > SCREEN_WIDTH - mainchar * spriteRat) {
              x = SCREEN_WIDTH - mainchar * spriteRat;
            }
        }
    }
}

void Character::render(Graphics& graphic) {
    if(state == RUNNING) {
        sprites[RUNNING].tick();
        graphic.renderAni(x, y, sprites[RUNNING]);
    }
    if(state == JUMPING) {
        if(!jumpAnimationFinished) {
            sprites[JUMPING].tick();
            graphic.renderAni(x, y, sprites[JUMPING]);
            if(sprites[JUMPING].currentFrame == MAIN_JUMP_FRAMES - 1) {
                jumpAnimationFinished = true;
            }
        }
        else {
            graphic.renderAni(x, y, sprites[JUMPING]);
        }

    }
    if(state == FALLING) {
        if(!fallAnimationFinished) {
            sprites[FALLING].tick();
            graphic.renderAni(x, y, sprites[FALLING]);
            if(sprites[FALLING].currentFrame == MAIN_FALL_FRAMES - 1) {
                fallAnimationFinished = true;
            }
        }
        else {
            graphic.renderAni(x, y, sprites[FALLING]);
        }
    }
}

void Character::update() {
    if (isDead) {
        return;
    }
    if(isOnAir) {
        velocityY += gravity;  // Áp dụng trọng lực
        y += velocityY ;

        if(velocityY > 0 && state == JUMPING) {
            changeState(FALLING);
        }

        if(y >= SCREEN_HEIGHT - GROUND_LEVEL - mainchar * spriteRat) {
            y = SCREEN_HEIGHT - GROUND_LEVEL - mainchar * spriteRat;
            jumpHeight=newjumpHeight;
            isOnAir = false;
            changeState(RUNNING);
            jumpcount=0;
            jumpAnimationFinished = false;
            fallAnimationFinished = false;
        }
    }
}

void Character::changeState(State newState) {
    if(state == newState) return;
    state = newState;
    sprites[state].currentFrame = 0;
}

SDL_Rect Character::charGetRect() const {
    return {getX(), getY(), 31*spriteRat, 31*spriteRat};
}

Character::~Character() {
    for (auto& spritePair : sprites) {
        if (spritePair.second.texture) {
            SDL_DestroyTexture(spritePair.second.texture);
        }
    }
    sprites.clear();
}

void Character::reset() {
    maxJumpCount=2;
    jumpHeight=-17;
    newjumpHeight=-17;
}
