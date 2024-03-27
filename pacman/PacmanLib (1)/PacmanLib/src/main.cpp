/// \file
/// main.cpp


#include "GameObjectStruct.hpp"
#include "UI.hpp"
#include <SDL2/SDL.h>
#include <vector>

const Uint32 pacmanMovementInterval = 150; // milliseconds between movements
Uint32 lastMovementTime = 0; // Last time Pac-Man moved


/// Callback function to update the game state.
///
/// This function is called by an SDL timer at regular intervals.
/// Note that this callback may happen on a different thread than the main thread.
/// You therefore have to be careful in avoiding data races. For example, you
/// should use mutexes to access shared data.
/// Read the documentation of SDL_AddTimer for more information and for tips
/// regarding multithreading issues.
Uint32 gameUpdate(Uint32 interval, void * /*param*/)
{
    // Do game loop update here
    return interval;
}

Direction getRandomDirection(const std::vector<std::vector<int>>& map, GameObjectStruct& ghost) {
    std::vector<Direction> possibleDirections;
    if (map[ghost.y][ghost.x - 1] != 1) possibleDirections.push_back(LEFT);
    if (map[ghost.y][ghost.x + 1] != 1) possibleDirections.push_back(RIGHT);
    if (map[ghost.y - 1][ghost.x] != 1) possibleDirections.push_back(UP);
    if (map[ghost.y + 1][ghost.x] != 1) possibleDirections.push_back(DOWN);

    if (possibleDirections.empty()) return ghost.dir; 

    int randomIndex = rand() % possibleDirections.size();
    return possibleDirections[randomIndex];
}


/// Program entry point.
int main(int /*argc*/, char ** /*argv*/)
{
    std::vector<std::vector<int>> map = {{
        #include "board.def"
    }};

    // Create a new ui object
    UI ui(map); // <-- use map from your game objects.

    // Start timer for game update, call this function every 100 ms.
    SDL_TimerID timer_id =
        SDL_AddTimer(100, gameUpdate, static_cast<void *>(nullptr));

    // Example object, this can be removed later
    GameObjectStruct pacman;
    pacman.x = 1;
    pacman.y = 1;
    pacman.type = PACMAN;
    pacman.dir = UP;

    GameObjectStruct blinky, pinky, inky, clyde;
    blinky.x = 12; blinky.y = 13; blinky.type = BLINKY; blinky.dir = UP;
    pinky.x = 13; pinky.y = 13; pinky.type = PINKY; pinky.dir = UP;
    inky.x = 14; inky.y = 13; inky.type = INKY; inky.dir = UP;
    clyde.x = 15; clyde.y = 13; clyde.type = CLYDE; clyde.dir = UP;


    // Call game init code here


    bool quit = false;
    while (!quit) {
        // set timeout to limit frame rate
        Uint32 timeout = SDL_GetTicks() + 20;

        // Handle the input
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            // Quit button.
            if (e.type == SDL_QUIT) {
                quit = true;
            }

            // All keydown events
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                case SDLK_LEFT: // YOUR CODE HERE
                    if (map[pacman.y][pacman.x - 1] != 1) pacman.dir = LEFT;
                    break;
                case SDLK_RIGHT: // YOUR CODE HERE
                    if (map[pacman.y][pacman.x + 1] != 1) pacman.dir = RIGHT;
                    break;
                case SDLK_UP: // YOUR CODE HERE
                    if (map[pacman.y - 1][pacman.x] != 1) pacman.dir = UP;
                    break;
                case SDLK_DOWN: // YOUR CODE HERE
                    if (map[pacman.y + 1][pacman.x] != 1) pacman.dir = DOWN;
                    break;
                case SDLK_ESCAPE:
                    quit = true;
                    break;
                }
            }
        }

        // Timing control for Pac-Man's movement
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - lastMovementTime >= pacmanMovementInterval) {
            // Update Pac-Man's position
            switch (pacman.dir) {
                case LEFT:
                    if (pacman.x == 0) pacman.x = map[0].size() - 1;
                    else if (map[pacman.y][pacman.x - 1] != 1) pacman.x -= 1;
                    break;
                case RIGHT:
                    if (pacman.x == map[0].size() - 1) pacman.x = 0;
                    else if (map[pacman.y][pacman.x + 1] != 1) pacman.x += 1;
                    break;
                case UP:
                    if (map[pacman.y - 1][pacman.x] != 1) pacman.y -= 1;
                    break;
                case DOWN:
                    if (map[pacman.y + 1][pacman.x] != 1) pacman.y += 1;
                    break;
            }
            lastMovementTime = currentTime;
        }
        

        // Set the score
        ui.setScore(0); // <-- Pass correct value to the setter

        // Set the amount of lives
        ui.setLives(3); // <-- Pass correct value to the setter

        // Render the scene
        std::vector<GameObjectStruct> objects = {pacman, blinky, pinky, inky, clyde};
        // ^-- Your code should provide this vector somehow (e.g.
        // game->getStructs())


        ui.update(objects);

        while (!SDL_TICKS_PASSED(SDL_GetTicks(), timeout)) {
            // ... do work until timeout has elapsed
        }
    }

    SDL_RemoveTimer(timer_id);

    return 0;
}
