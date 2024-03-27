// GameBoard.hpp
#include <vector>
#include "UI.hpp"
#include "GameObjectStruct.hpp"

class GameBoard {
public:
    std::vector<std::vector<int>> map;

    GameBoard(const std::vector<std::vector<int>>& map);
    void drawBoard(UI& ui) const; 
};
