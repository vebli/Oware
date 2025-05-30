#include "Oware.hpp"
#include "GameLogic.hpp"
#include <algorithm>
#include <iostream>


void Oware::play_local_multiplayer(){
     GameState gameState({4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4}, {0, 0});

    while(true){
        std::vector<int> legalMoves;

        std::cout << "Player 1 to move" << std::endl;
        legalMoves = getLegalMoves(gameState, player1);
        int chosenMove;
        std::cin >> chosenMove;
        
        while (std::find(legalMoves.begin(), legalMoves.end(), chosenMove) == legalMoves.end()){
            std::cout << "Illegal Move\n";
            std::cin >> chosenMove;
        }

        move(gameState, player1, chosenMove);
        print_board(gameState);
        if(checkGameOver(gameState, player1)){ break; };

        std::cout << "Player 2 to move" << std::endl;
        legalMoves = getLegalMoves(gameState, player2);
        std::cin >> chosenMove;

        while (std::find(legalMoves.begin(), legalMoves.end(), chosenMove) == legalMoves.end()){
            std::cout << "Illegal Move\n";
            std::cin >> chosenMove;
        }

        move(gameState, player2, chosenMove);
        print_board(gameState);
        if(checkGameOver(gameState, player2)){ break; };

    }
    if(gameState.getScore(player1) > gameState.getScore(player2)){
        std::cout << "Player 1 Won\n";
    }
    else if (gameState.getScore(player1) < gameState.getScore(player2)){
        std::cout << "Player 2 Won\n";
    }
    else {
        std::cout << "Draw\n";
    }
}

