#pragma once
#include "GameState.hpp"
#include <vector>

class GameLogic {
public:
    GameLogic();
    void print();
    void move(int pit, int player);
    bool isLegalMove();
    std::vector<int> getLegalMoves();
    std::vector<GameState> findChildren();
    bool isGameOver();
    
private:
    GameState GameState;
};
