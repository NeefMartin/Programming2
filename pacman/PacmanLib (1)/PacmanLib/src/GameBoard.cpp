// GameBoard.cpp
#include "GameBoard.hpp"
#include "UI.hpp"

GameBoard::GameBoard(const std::vector<std::vector<int>>& map) : map(map) {}

void GameBoard::drawBoard(UI& ui) const {
    ui.drawBackground(map);
}
