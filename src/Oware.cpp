#include "Oware.hpp"
#include "GameLogic.hpp"
#include <algorithm>
#include <cstdlib>
#include <ios>
#include <iostream>
#include <limits>


void Oware::play_local_multiplayer(){
     GameState gameState({4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4}, {0, 0});
     std::vector<int> legalMoves;

     auto play_turn = [&](const int player){
         system("clear");

        print_board(gameState);

        legalMoves = getLegalMoves(gameState, player);

        if(legalMoves.empty()){ 
            int opponent = player ^ 1;
            int left_over = 0;
            for(int i = 1; i <= 6; i++){
                left_over += gameState.getSeeds(getIndex(opponent, i));
                gameState.setSeeds(getIndex(opponent, i), 0);
            }
            gameState.addToScore(player, left_over);
            return false;
        }

        if(gameState.getScore(player) >= 25){
            return false;
        }
        int chosenMove;

        std::cout << "Player " << player + 1 << "\'s turn\n"; 
        while(true){
            std::cin >> chosenMove;
            if (std::cin.fail()){
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Illegal Move.\n";
            }
            else {
                break;
            }
        }
        
        while (std::find(legalMoves.begin(), legalMoves.end(), chosenMove) == legalMoves.end()){
            std::cout << "Illegal Move\n";
            std::cin >> chosenMove;
        }

        move(gameState, player, chosenMove);
        return true;
     };

     while(true){
         if(!play_turn(player1)){ break; };
         if(!play_turn(player2)){ break; };
     }

    print_board(gameState);

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

