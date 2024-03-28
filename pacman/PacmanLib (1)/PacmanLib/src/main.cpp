/// \file
/// main.cpp


#include "GameObjectStruct.hpp"
#include "UI.hpp"
#include <SDL2/SDL.h>
#include <vector>
#include <ctime>

const Uint32 pacmanMovementInterval = 250; // milliseconds between movements
Uint32 lastMovementTime = 0; // Last time Pac-Man moved


std::vector<Direction> GhostMoves(int x, int y, Direction currentDir, const std::vector<std::vector<int>>& map) {
    std::vector<Direction> directions = {UP, DOWN, LEFT, RIGHT}, newDirections;

    // Determine the opposite direction to prevent backtracking
    Direction oppositeDir;
    switch (currentDir) {
        case UP: oppositeDir = DOWN; break;
        case DOWN: oppositeDir = UP; break;
        case LEFT: oppositeDir = RIGHT; break;
        case RIGHT: oppositeDir = LEFT; break;
    }

    // Remove the opposite direction
    for (Direction dir : directions) {
        if (dir != oppositeDir) {
            newDirections.push_back(dir);
        }
    }

    directions = newDirections; // Update directions with the removed opposite direction
    newDirections.clear(); 

    // Manually check and remove directions that lead to a wall
    for (Direction dir : directions) {
        bool isLegal = true;
        switch (dir) {
            case UP: if (map[y - 1][x] == 1) isLegal = false; break;
            case DOWN: if (map[y + 1][x] == 1) isLegal = false; break;
            case LEFT: if (map[y][x - 1] == 1) isLegal = false; break;
            case RIGHT: if (map[y][x + 1] == 1) isLegal = false; break;
        }
        if (isLegal) {
            newDirections.push_back(dir);
        }
    }

    // Handling stuck situation
    if (newDirections.size() == 1) {
        return newDirections;
    } else if (newDirections.empty() && currentDir != NONE) {
        return std::vector<Direction>{oppositeDir}; // Allow reversing direction
    }

    return newDirections;
}

int getRandomIndex(int max) {
    return static_cast<int>(time(NULL)) % max; 
}

void addFruit(std::vector<std::vector<int>>& map, std::vector<GameObjectStruct>& fruits) {
    std::vector<std::pair<int, int>> emptySpaces;

    for (int y = 0; y < map.size(); ++y) {
        for (int x = 0; x < map[0].size(); ++x) {
            if (map[y][x] == 0) { // ]
                emptySpaces.push_back({x, y});
            }
        }
    }

    if (!emptySpaces.empty()) {
        // Choose a random tile
        int index = rand() % emptySpaces.size();
        int x = emptySpaces[index].first;
        int y = emptySpaces[index].second;

        // Choose a random fruit type
        Type fruitTypes[] = {CHERRY, STRAWBERRY, ORANGE, LEMON, APPLE, GRAPES};
        Type fruitType = fruitTypes[rand() % 6];

        // Place the fruit
        GameObjectStruct fruit = {x, y, fruitType, UP}; 
        fruits.push_back(fruit);
    }
}


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

/// Program entry point.
int main(int /*argc*/, char ** /*argv*/)
{
    srand(static_cast<unsigned int>(time(NULL)));

    std::vector<std::vector<int>> map = {{
        #include "board.def"
    }};

    // Create a new ui object
    UI ui(map); // <-- use map from your game objects.

    // Start timer for game update, call this function every 100 ms.
    SDL_TimerID timer_id =
        SDL_AddTimer(100, gameUpdate, static_cast<void *>(nullptr));


    //initialize dots
    std::vector<GameObjectStruct> dots; //create dots vector of type GameObjectStruct

    for (size_t i = 0; i < map.size(); ++i) {
        for (size_t j = 0; j < map[i].size(); ++j) {
            // Check if the cell value is 0
            if (map[i][j] == 0) {
                // Create dot if value is 0
                GameObjectStruct dot;
                dot.x = j;
                dot.y = i;
                dot.type = DOT;
                dot.dir = UP;
                dots.push_back(dot);
            }
        }
    }

    //initialize energizers
    std::vector<GameObjectStruct> enegizers; //create enegizer vector of type GameObjectStruct

    GameObjectStruct enegizer1,enegizer2,enegizer3,enegizer4;
    enegizer1.x = 1, enegizer1.y = 1, enegizer1.type = ENERGIZER, enegizer1.dir = UP;
    enegizer2.x = 1, enegizer2.y = 25, enegizer2.type = ENERGIZER, enegizer2.dir = UP;
    enegizer3.x = 26, enegizer3.y = 1, enegizer3.type = ENERGIZER, enegizer3.dir = UP;
    enegizer4.x = 26, enegizer4.y = 25, enegizer4.type = ENERGIZER, enegizer4.dir = UP;

    enegizers.push_back(enegizer1), enegizers.push_back(enegizer2), enegizers.push_back(enegizer3), enegizers.push_back(enegizer4);

    // Initialize fruits
    std::vector<GameObjectStruct> fruits;

    
    //initialize ghosts
    std::vector<GameObjectStruct> ghosts;
    GameObjectStruct blinky, pinky, inky, clyde;
    blinky.x = 12; blinky.y = 13; blinky.type = BLINKY; blinky.dir = UP;
    pinky.x = 13; pinky.y = 13; pinky.type = PINKY; pinky.dir = UP;
    inky.x = 14; inky.y = 13; inky.type = INKY; inky.dir = UP;
    clyde.x = 15; clyde.y = 13; clyde.type = CLYDE; clyde.dir = UP;

    ghosts.push_back(blinky), ghosts.push_back(pinky),ghosts.push_back(inky),ghosts.push_back(clyde);


    int PACMAN_START_X = 13;
    int PACMAN_START_Y = 21;


    //initialize pacman
    GameObjectStruct pacman;
    pacman.x = PACMAN_START_X;
    pacman.y = PACMAN_START_Y;
    pacman.type = PACMAN;
    pacman.dir = UP;

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

        // Render the scene
        std::vector<GameObjectStruct> objects = {pacman};

        objects.insert(objects.end(), dots.begin(), dots.end());
        objects.insert(objects.end(), enegizers.begin(), enegizers.end());
        objects.insert(objects.end(), ghosts.begin(), ghosts.end());

        // ^-- Your code should provide this vector somehow (e.g.
        // game->getStructs())
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

            for (auto& ghost : ghosts) {
            std::vector<Direction> legalMoves = GhostMoves(ghost.x, ghost.y, ghost.dir, map);
            if (!legalMoves.empty()) {
                int index = getRandomIndex(legalMoves.size());
                Direction newDir = legalMoves[index]; // Select a new direction
                ghost.dir = newDir; // Update ghost direction

                // Update ghost position based on the new direction
                switch (newDir) {
                    case UP:
                        if (map[ghost.y - 1][ghost.x] != 1) ghost.y -= 1;
                        break;
                    case DOWN:
                        if (map[ghost.y + 1][ghost.x] != 1) ghost.y += 1;
                        break;
                    case LEFT:
                        if (map[ghost.y][ghost.x - 1] != 1) ghost.x -= 1;
                        else if (map[ghost.y][ghost.x - 1] != 1) ghost.x -= 1;
                        break;
                    case RIGHT:
                        if (map[ghost.y][ghost.x + 1] != 1) ghost.x += 1;
                        else if (map[ghost.y][ghost.x + 1] != 1) ghost.x += 1;
                        break;
                }
            }
        }
        }

        //Check if x and y of pacman are equal to that of the dots.
        for (auto i = dots.begin(); i != dots.end();) {
            auto& dot = *i;
            if (dot.x == pacman.x && dot.y == pacman.y) {
                i = dots.erase(i); // If it is the same, erase dot
                int currentScore=ui.getScore(); // Get the current score
                ui.setScore(currentScore+1); // Add 1 point to the score
            } else {
                ++i; // Move to the next element
            }
        }

        //Check if x and y of pacman are equal to that of the enegizers.
        for (auto i = enegizers.begin(); i != enegizers.end();) {
            auto& enegizer = *i;
            //Starts timer and sets ghosts to type SCARED if the ghost collides with an enegizer.
            if (enegizer.x == pacman.x && enegizer.y == pacman.y) {
                i = enegizers.erase(i); // If it is the same, erase dot
                for (GameObjectStruct& ghost : ghosts) {
                    ghost.type = SCARED;
                }
            } else {
                ++i; // Move to the next element
            }
        }

        //Check if x and y of pacman are equal to that of the ghosts.
        //iterate through all ghosts
        for (GameObjectStruct&  ghost : ghosts) {
            //Check ghost position
            if (ghost.x == pacman.x && ghost.y == pacman.y) {
                if (ghost.type != SCARED) {
                    pacman.x = PACMAN_START_X;
                    pacman.y = PACMAN_START_Y;
                    int currentLives = ui.getLives();
                    ui.setLives(currentLives - 1); 
                }
                
                //reset ghost position and ghost type if ghost is scared
                if (ghost.type == SCARED) { 
                    if (ghost == blinky){ //checks for equal position
                        ghost.x = 12;
                        ghost.y = 13;
                        ghost.type = BLINKY; //resets type
                    }
                    if (ghost == pinky) {
                        ghost.x = 13;
                        ghost.y = 13;
                        ghost.type = PINKY;
                    }
                    if (ghost == inky) {
                        ghost.x = 14;
                        ghost.y = 13;
                        ghost.type = INKY;
                    }
                    if (ghost == clyde){
                        ghost.x = 15;
                        ghost.y = 13;
                        ghost.type = CLYDE;
                    }
                }
            }
        }

        for (auto iterator = fruits.begin(); iterator != fruits.end();) {
            if (iterator->x == pacman.x && iterator->y == pacman.y) {
                // Collision detected, increase score
                int currentScore = ui.getScore();
                ui.setScore(currentScore + 20); 

                // Remove the fruit from the board
                iterator = fruits.erase(iterator);
            } else {
                ++iterator;
            }
        }

        objects.insert(objects.end(), fruits.begin(), fruits.end());
        ui.update(objects);

        if (ui.getScore() % 100 == 0 && ui.getScore() != 0) {
            addFruit(map, fruits);
        }


        while (!SDL_TICKS_PASSED(SDL_GetTicks(), timeout)) {
            // ... do work until timeout has elapsed
        }
    }

    SDL_RemoveTimer(timer_id);

    return 0;
}
