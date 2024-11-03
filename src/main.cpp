#include "GameState.hpp"
#include "GameLogic.hpp"
#include <array>
int main(){

    std::array<int,14> startingState = {0, 1, 13, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    GameState gamestate(startingState);
    GameLogic gamelogic(gamestate); 
    /*gamelogic.setSeeds(2, 6, 100);*/
    /*gamelogic.setSeeds(1, 2, 100);*/
    /*std::cout << gamelogic.getSeeds(1, 1) << "\n";*/
    /*std::cout << gamelogic.getSeeds(2, 1) << "\n";*/
    /*std::cout << gamelogic.getSeeds(1, 6) << "\n";*/
    /*std::cout << gamelogic.getSeeds(2, 6) << "\n";*/
    gamelogic.print();
    gamelogic.move(2);
    gamelogic.print();

}

