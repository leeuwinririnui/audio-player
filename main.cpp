#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <iostream>

int main(int argc, char** argv) {
     // Initialize SDL 
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "Error: Failed to initialize SDL! - " << SDL_GetError() << std::endl;
        return 1;
    }

    // Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Error: Failed to initialize SDL_mixer! - " << Mix_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    while (true) {
        // Prompt user 
        std::cout << "Please enter path to file (enter 'q' to quit): ";
        std::string file_path;
        std::getline(std::cin, file_path);

        if (file_path == "q") break;

        // Load music from file 
        Mix_Music* music = Mix_LoadMUS(file_path.c_str());
        if (music == nullptr) {
            std::cout << "Error: Failed to load music file! - " << Mix_GetError() << std::endl;
            continue;
        }

        // Play music file (0 = play once)
        if (Mix_PlayMusic(music, 0) < 0) {
            std::cerr << "Error: Failed to play music! - " << Mix_GetError() << std:: endl;
            Mix_FreeMusic(music);
            continue;
        }

        // Control music
        std::string music_control; 
        while (Mix_PlayingMusic()) {
            std::cout << "Enter command (p: pause, r: resume, z:restart, q: stop): ";
            std::cin >> music_control;

            if (music_control == "p") {
                std::cout << "Audio Paused" << std::endl;
                Mix_PauseMusic();
            } else if (music_control == "r") {
                std::cout << "Audio Resumed" << std::endl;
                Mix_ResumeMusic();
            } else if (music_control == "z") {
                std::cout << "Audio Restarted" << std::endl;
                Mix_RewindMusic();
            } else if (music_control == "q") {
                std::cout << "Audio Stopped" << std::endl;
                break;
            }
        }

        // Clean up resources
        std::cin.ignore();
        Mix_HaltMusic();
        Mix_FreeMusic(music);
    }

    Mix_CloseAudio();
    SDL_Quit();
    
    return 0;
}