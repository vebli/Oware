#pragma once
#include "GameState.hpp"
#include <vector>
#include <cassert>

class GameLogic {
public:
    GameLogic(GameState State);

    int getSeeds(int player, int pit);
    void setSeeds(int player, int pit, int amount);

    void print();
    void move(int pit, int player);

    bool isLegalMove(int player, int pit);
    bool checkGameOver(int player);
    std::vector<int> getLegalMoves(int player);
    std::vector<GameState> findChildren();
    bool isGameOver();
    
private:
    int getIndex(int player, int pit);
    bool capture(int start, int stop);
    bool reachesOponent(int player, int pit);
    bool hasEmptyField(int player);
    bool canGiveToOponent(int player); 
    std::vector<int> getForcedMoves(int player);
    GameState gameState;
};
