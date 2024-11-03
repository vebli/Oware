#include "Oware.hpp"
Oware::Oware(){
    std::array<int,14> startingState = {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0};
    GameState gameState(startingState);
    gameLogic = GameLogic(gameState);
}

void Oware::play(){
    while(!gameLogic.isGameOver()){
        std::vector<int> legalMoves;

        std::cout << "Player 1 to move" << std::endl;
        legalMoves = gameLogic.getLegalMoves(1);
        int chosenMove;
        std::cin >> chosenMove;
        
        while (std::find(legalMoves.begin(), legalMoves.end(), chosenMove) == legalMoves.end()){
            std::cout << "Illegal Move\n";
            std::cin >> chosenMove;
        }
        gameLogic.move(chosenMove, 1);

        std::cout << "Player 2 to move" << std::endl;
        legalMoves = gameLogic.getLegalMoves(2);
        while (std::find(legalMoves.begin(), legalMoves.end(), chosenMove) == legalMoves.end()){
            std::cout << "Illegal Move\n";
            std::cin >> chosenMove;
        }
        gameLogic.move(chosenMove, 2);

        gameLogic.checkGameOver();

    }
}

