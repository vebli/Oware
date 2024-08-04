#include "Oware.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
Oware::Oware(){

}

void Oware::play(){
    while(!GameLogic.isGameOver()){
        std::cout << "Player 1 to move" << std::endl;

        std::vector<int> legalMoves = GameLogic.getLegalMoves();
        int chosenMove;
        std::cin >> chosenMove;
        
        while (std::find(legalMoves.begin(), legalMoves.end(), chosenMove) == legalMoves.end()){
            std::cout << "Illegal Move\n";
            std::cin >> chosenMove;
        }
        GameLogic.move(chosenMove, 1);

        std::cout << "Player 2 to move" << std::endl;

        while (std::find(legalMoves.begin(), legalMoves.end(), chosenMove) == legalMoves.end()){
            std::cout << "Illegal Move\n";
            std::cin >> chosenMove;
        }
        GameLogic.move(chosenMove, 2);

    }
}

