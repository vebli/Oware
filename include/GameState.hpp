#pragma once
#include <array>
#include <string>
#include <vector>
#include <iostream>

class GameState {
public:
    GameState();
    GameState(std::array<int, 12>& State, int Player1Captures, int Player2Captures);
    void setState(std::array<int, 12>& newState);
    void setSeeds(int seeds, int field, int player); 
    int getSeeds(int seeds, int field, int player); 
    void print();
private:

    std::array<int, 12> state;
    int player1Captures; 
    int player2Captures; 
    std::vector<std::string> boardTemplate;
};
