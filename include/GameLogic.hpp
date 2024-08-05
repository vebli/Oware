#pragma once
#include "GameState.hpp"
#include <vector>

class GameLogic {
public:
    GameLogic();
    GameLogic(GameState& State);
    void print();
    void move(uint8_t pit, uint8_t player);
    bool isLegalMove(uint8_t pit, uint8_t player);
    bool checkGameOver();
    std::vector<uint8_t> getLegalMoves(uint8_t player);
    std::vector<GameState> findChildren();
    bool isGameOver();
    
private:
    bool reachesOponent(uint8_t pit, uint8_t player);
    bool hasEmptyField(uint8_t player);
    bool canGiveToOponent(uint8_t player); 
    std::vector<uint8_t> getForcedMoves(uint8_t player);
    GameState gameState;
};
