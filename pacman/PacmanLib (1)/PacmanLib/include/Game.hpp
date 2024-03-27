// Game.hpp
#include "GameBoard.hpp"
#include "UI.hpp"

class Game {
private:
    UI ui;
    GameBoard board;
    bool isRunning;

public:
    Game(const std::vector<std::vector<int>>& map);
    void init();
    void run();
    void handleEvents();
    void update();
    void render();
};
