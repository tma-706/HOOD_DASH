#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED
#include "DEF.h"
#include <vector>
#include <SDL.h>
#include <SDL_image.h>

struct ScrollingBackground {
    SDL_Texture* texture;
    int scrollingOffset=0;
    int width, height;

    void setTexture(SDL_Texture* _texture) {
        texture=_texture;
        SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    }

    void scroll(int distance) {
        scrollingOffset-=distance;
        if(scrollingOffset<0) scrollingOffset=width;
    }

    ~ScrollingBackground() {
        if (texture) {
            SDL_DestroyTexture(texture);
        }
    }
};
struct Sprite {
    SDL_Texture* texture;
    std::vector <SDL_Rect> clips;
    int currentFrame = 0;
    void init(SDL_Texture* _texture, const int _clips[][4], int frames) {
        texture = _texture;
        SDL_Rect clip;
        for(int i = 0; i < frames; i++) {
            clip.x = _clips[i][0];
            clip.y = _clips[i][1];
            clip.w = _clips[i][2];
            clip.h = _clips[i][3];
            clips.push_back(clip);
        }
    }
    void tick() {
        currentFrame = (currentFrame+1)%clips.size();
    }
    const SDL_Rect* getCurrentclip() const {
        return &(clips[currentFrame]); //đỡ tốn dữ liệu trả về biến sao chép
    }
    int getWidth() const {
        return clips[currentFrame].w;
    }

    int getHeight() const {
        return clips[currentFrame].h;
    }

    ~Sprite() {
        if (texture) {
            SDL_DestroyTexture(texture);
        }
    }

};
struct Graphics {
    SDL_Renderer *renderer;
    SDL_Window *window;


    void logErrorAndExit(const char* msg, const char* error) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
        SDL_Quit();
        exit(1);
    }

    void init() {
        if(SDL_Init(SDL_INIT_EVERYTHING)!=0) logErrorAndExit("SDL_Init", SDL_GetError());
        window = SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(window == nullptr) logErrorAndExit("CreateWindow", SDL_GetError());

        if(!IMG_Init(IMG_INIT_PNG | IMG_INIT_PNG)) logErrorAndExit("SDL_image error:", SDL_GetError());
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if(renderer == nullptr) logErrorAndExit("SDL_CreateRenderer", SDL_GetError());

        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    }

    void presentScene() {
        SDL_RenderPresent(renderer);
    }

    void prepareScene(SDL_Texture* background) {
        SDL_RenderClear(renderer);
        if(background != nullptr) {
            SDL_Rect dstRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT}; //trong trường hợp cần kiểm tra lại tỉ lệ màn hình
            SDL_RenderCopy(renderer, background, NULL, &dstRect);
        }
    }

    SDL_Texture* loadTexture(const char* filename) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);
        SDL_Texture* texture = IMG_LoadTexture(renderer, filename);
        if(texture == NULL) {
           SDL_Log("Failed to load texture: %s, error: %s", filename, IMG_GetError());
            return nullptr;
        }
        return texture;
    }

    void renderTexture(SDL_Texture* texture, int x, int y, int rat) {
        SDL_Rect dest;
        dest.x = x;
        dest.y = y;
        int w, h;
        SDL_QueryTexture(texture, NULL, NULL, &w, &h);
        dest.w = w*rat;
        dest.h = h*rat;
        SDL_RenderCopy(renderer, texture, NULL, &dest);
    }

    void renderAni(int x, int y, const Sprite &sprite) {
        const SDL_Rect* clip;
        clip = sprite.getCurrentclip();
        int w = (clip->w) * spriteRat;
        int h = (clip->h) * spriteRat;
        SDL_Rect printDest = {x, y, w, h};
        //SDL_Log("Rendering sprite at x: %d, y: %d, w: %d, h: %d", x, y, w, h);

        if (SDL_RenderCopy(renderer, sprite.texture, clip, &printDest) != 0) {
        //SDL_Log("SDL_RenderCopy failed: %s", SDL_GetError());
        }
    }

    void renderScreen(const ScrollingBackground& background) {
        renderTexture(background.texture, background.scrollingOffset, 0,1);
        renderTexture(background.texture, background.scrollingOffset - background.width, 0,1);
    }

    void quit() {
        if (renderer) {
            SDL_DestroyRenderer(renderer);
            renderer = nullptr;
        }
        if (window) {
            SDL_DestroyWindow(window);
            window = nullptr;
        }
        IMG_Quit();
        SDL_Quit();
    }

};


#endif // GRAPHICS_H_INCLUDED
