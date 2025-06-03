#include "Oware.hpp"
#include "GameLogic.hpp"
#include <cstdlib>
#include <iostream>
#include <cassert>

// void assert_invariant(GameState &s){
//     int sum = 0;
//     for(int i = 0; i < 12; i++) { sum += s.getSeeds(i); }
//     assert(s.getScore(player1) + s.getScore(player2) + sum == 48);
// }

void Oware::play_local_multiplayer(){
     GameState gameState({4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4}, {0, 0});

     while(true){
        system("clear");
        print_board(gameState);
        std::cout << "Player 1" << "\'s turn\n"; 
        if(gameState.getScore(player1) >= 25 || !player_turn(gameState, player1)){ break; };

        system("clear");
        print_board(gameState);
        std::cout << "Player 2" << "\'s turn\n"; 
         if(gameState.getScore(player1) >= 25 || !player_turn(gameState, player2)){ break; };
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

void Oware::play_singleplayer(int difficulty){
    //TODO: score win condition
    GameState gameState({4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4}, {0, 0});
    constexpr int com = player2;
    constexpr int player = player1;
    while (true) {

        print_board(gameState);
        std::cout << "Your " << "turn: "; 

        if(gameState.getScore(player) >= 25 || !player_turn(gameState, player)){ break; };
        // system("clear");
        print_board(gameState);
        int best_move = get_best_move(gameState, difficulty, com);
        std::cout << "COM\'s " << "turn: "; 

        if(best_move == -1 || gameState.getScore(com) >= 25){ break; }
        std::cout << best_move << '\n';
        move(gameState, com, best_move);
    }
}
