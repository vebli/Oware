/*Indices:*/
/*    "|----|-----------------------------|----|",*/
/*    "|    | 11 | 10 | 8  | 8  | 7  | 6  |    |",*/
/*    "| 12 |-----------------------------| 13 |",*/
/*    "|    | 0  | 1  | 2  | 3  | 4  | 5  |    |",*/
/*    "|----|-----------------------------|----|"*/

#pragma once
#include <array>
#include <cstdint>
#include <optional>
#include <string>
#include <utility>
#include <vector>
#include <cassert>
#include <iostream>


class GameState {
public:
    GameState();
    GameState(std::array<int, 14>& State);
    void setState(std::array<int, 14>& newState);
    void setSeeds(int pit, int seeds); 
    int getSeeds(int pit); 
    void print(); 
private:
    std::array<int, 14> state;
    const std::vector<std::string> boardTemplate = {
        "|----|-----------------------------|----|",
        "|    | s  | s  | s  | s  | s  | s  |    |",
        "| c  |-----------------------------| c  |",
        "|    | s  | s  | s  | s  | s  | s  |    |",
        "|----|-----------------------------|----|"
    };
};
