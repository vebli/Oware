#pragma once
#include <array>
#include <cstdint>
#include <string>
#include <vector>
#include <cassert>
#include <iostream>

class GameState {
public:
    GameState();
    GameState(std::array<int, 12>& State, int Player1Captures, int Player2Captures);
    void setState(std::array<int, 12>& newState);
    void setSeeds(int seeds, uint8_t pit); 
    int getSeeds(uint8_t pit, uint8_t player); 
    void print();
private:

    std::array<int, 12> state;
    int player1Captures; 
    int player2Captures; 
    std::vector<std::string> boardTemplate;
};
