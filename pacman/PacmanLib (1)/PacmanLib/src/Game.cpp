// Game.cpp
#include "Game.hpp"
#include <SDL2/SDL.h>

Game::Game(const std::vector<std::vector<int>>& map) : ui(map), board(map), isRunning(false) {}

void Game::init() {
    // Initialize SDL, create window, and other setup tasks
    SDL_Init(SDL_INIT_EVERYTHING);
}

void Game::run() {
    isRunning = true;
    while (isRunning) {
        handleEvents();
        update();
        render();
    }
}

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
        else if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                // Escape key is pressed
                isRunning = false;
            }
        }
        // Handle other events -> keyboard input
    }
}

void Game::update() {
    // Update game state, including Pacman and ghosts
}

void Game::render() {
    ui.clear();
    board.drawBoard(ui); // Draw the game board
    ui.present();
}
