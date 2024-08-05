#pragma once
#include "GameLogic.hpp"
#include <array>
#include <cstdint>
#include <iostream>
#include <vector>
#include <algorithm>

class Oware {
public:
    Oware();
    void play();
private:
    GameLogic gameLogic;
};
