#ifndef MUSIC_H_INCLUDED
#define MUSIC_H_INCLUDED
#include "GRAPHICS.h"
#include <SDL_mixer.h>

class Music {
public:
    Music();
    ~Music();
    void init(const char* filename, Graphics& graphic);
    void playMusic();
    void stopMusic();
private:
    Mix_Music* bgMusic;
};

#endif // MUSIC_H_INCLUDED
