#include "MUSIC.h"
#include "DEF.h"

Music::Music() : bgMusic(nullptr) {}

Music::~Music() {
    if(bgMusic) {
        Mix_FreeMusic(bgMusic);
    }
    Mix_Quit();
}

void Music::init(const char* filename, Graphics& graphic) {
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        graphic.logErrorAndExit("Mix_OpenAudio", Mix_GetError());
    }
    bgMusic = Mix_LoadMUS(filename);
    if (!bgMusic) {
        Graphics().logErrorAndExit("Mix_LoadMUS", Mix_GetError());
    }
}

void Music::playMusic() {
    if(bgMusic && !Mix_PlayingMusic()) {
        Mix_PlayMusic(bgMusic, -1);
    }
}

void Music::stopMusic() {
    if(Mix_PlayingMusic()) {
        Mix_HaltMusic();
    }
}
