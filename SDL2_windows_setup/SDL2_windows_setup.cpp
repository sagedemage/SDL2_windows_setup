// SDL2_windows_setup.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/* Standard Libraries */
#include <iostream>
#include <string>
#include <windows.h>

/* Third Party Liberies */
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int FPS = 60;

const int music_volume = 12;
const int chunksize = MIX_MAX_VOLUME;
const char* music_path = "assets/sample_music.mp3";

const int width = 25;
const int height = 25;
const int speed = 2;

void player_boundaries(SDL_Rect& dstrect);

int main(int argc, char* args[])
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::string err_msg = "SDL could not initialize. SDL_Error: " + (std::string)SDL_GetError() + "\n";
        OutputDebugStringA(err_msg.c_str());
        return EXIT_FAILURE;
    }

    SDL_Window* window = SDL_CreateWindow("SDL2 Windows Setup", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL) {
        std::string err_msg = "Window could not be created. SDL_Error: " + (std::string)SDL_GetError() + "\n";
        OutputDebugStringA(err_msg.c_str());
        return EXIT_FAILURE;
    }

    SDL_Renderer* rend = SDL_CreateRenderer(window, -1, 0);

    // Initialize loading audio files
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, chunksize) < 0) {
        std::string err_msg = "SDL_mixer could not initialize. SDL_Error: " + (std::string)Mix_GetError() + "\n";
        OutputDebugStringA(err_msg.c_str());
        return EXIT_FAILURE;
    }

    // Initialize loading PNG files 
    if (IMG_Init(IMG_INIT_PNG) < 0) {
        std::string err_msg = "SDL_image could not initialize. SDL_Error: " + (std::string)IMG_GetError() + "\n";
        OutputDebugStringA(err_msg.c_str());
        return EXIT_FAILURE;
    }

    Mix_Music* music = Mix_LoadMUS(music_path);
    Mix_VolumeMusic(music_volume);

    if (Mix_PlayMusic(music, -1) < 0) {
        std::string err_msg = "Could not play music. SDL_Error: " + (std::string)Mix_GetError() + "\n";
        OutputDebugStringA(err_msg.c_str());
        return EXIT_FAILURE;
    }

    SDL_Surface* playerSurface = IMG_Load("assets/player.png");

    if (playerSurface == NULL) {
        std::string err_msg = "Could load surface of player bmp file. SDL_Error: " + (std::string)SDL_GetError() + "\n";
        OutputDebugStringA(err_msg.c_str());
        return EXIT_FAILURE;
    }

    SDL_Texture* playerTexture = SDL_CreateTextureFromSurface(rend, playerSurface);

    if (playerTexture == NULL) {
        std::string err_msg = "Could load texture of player surface. SDL_Error: " + (std::string)SDL_GetError() + "\n";
        OutputDebugStringA(err_msg.c_str());
        return EXIT_FAILURE;
    }

    SDL_Rect srcrect = {0, 0, width, height};
    SDL_Rect dstrect = {10, SCREEN_HEIGHT / 2, width, height};

    SDL_Event e;
    bool quit = false;

    Uint8 red = 0, green = 0, blue = 255, alpha = 255;
    SDL_SetRenderDrawColor(rend, red, green, blue, alpha);

    while (quit == false) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        /* Hold Keybindings */
        // Get the snapshot of the current state of the keyboard
        const Uint8* state = SDL_GetKeyboardState(NULL);

        if (state[SDL_SCANCODE_LEFT] == 1) { // move player left
            dstrect.x -= speed;
        }
        else if (state[SDL_SCANCODE_RIGHT] == 1) { // move player right
            dstrect.x += speed;
        }
        else if (state[SDL_SCANCODE_UP] == 1) { // move player up
            dstrect.y -= speed;
        }
        else if (state[SDL_SCANCODE_DOWN] == 1) { // move player down
            dstrect.y += speed;
        }

        player_boundaries(dstrect);

        SDL_RenderClear(rend);
        SDL_RenderCopy(rend, playerTexture, &srcrect, &dstrect);
        SDL_RenderPresent(rend);
        SDL_Delay(1000/FPS);
    }

    // Deallocate surface
    SDL_FreeSurface(playerSurface);
    playerSurface = NULL;
    SDL_DestroyTexture(playerTexture);
    playerTexture = NULL;

    // Destroy window
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(window);
    rend = NULL;
    window = NULL;

    // Destroy SDL instances
    IMG_Quit();
    Mix_Quit();
    SDL_Quit();

    return 0;
}

void player_boundaries(SDL_Rect &dstrect) {
    /* Player boundaries */
        // left boundary
    if (dstrect.x < 0) {
        dstrect.x = 0;
    }
    // right boundary
    if (dstrect.x + dstrect.w > SCREEN_WIDTH) {
        dstrect.x = SCREEN_WIDTH - dstrect.w;
    }
    // bottom boundary
    if (dstrect.y + dstrect.h > SCREEN_HEIGHT) {
        dstrect.y = SCREEN_HEIGHT - dstrect.h;
    }
    // top boundary
    if (dstrect.y < 0) {
        dstrect.y = 0;
    }
}
