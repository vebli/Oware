#include "GameState.hpp"
#include "GameLogic.hpp"
#include <array>
enum {
    player1 = 1,
    player2 = 2
};
int main(){

    /*std::array<int,14> startingState = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};*/
    std::array<int,14> startingState = {0, 0, 0, 0, 0, 0, 5, 4, 4, 2, 1, 0, 12, 13};
    GameState gamestate(startingState);
    GameLogic gamelogic(gamestate); 
    gamelogic.print();
    gamelogic.move(player1, 3);
    gamelogic.print();
    std::vector<int> legalMoves = gamelogic.getLegalMoves(player2);
    for(auto move: legalMoves){
        std::cout << move << ", ";
    }
}

