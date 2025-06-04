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
     GameState s({4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4}, {0, 0});

     while(true){
        system("clear");
        print_board(s);
        std::cout << "Player 1" << "\'s turn\n"; 
        if(!player_turn(s, player1)){ break; };

        system("clear");
        print_board(s);
        std::cout << "Player 2" << "\'s turn\n"; 
         if(!player_turn(s, player2)){ break; };
     }

    print_board(s);

    if(s.getScore(player1) > s.getScore(player2)){
        std::cout << "Player 1 Won\n";
    }
    else if (s.getScore(player1) < s.getScore(player2)){
        std::cout << "Player 2 Won\n";
    }
    else {
        std::cout << "Draw\n";
    }
}

void Oware::play_singleplayer(int difficulty){
    //TODO: score win condition
    GameState s({4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4}, {0, 0});
    constexpr int com = player2;
    constexpr int player = player1;
    while (true) {

        print_board(s);
        std::cout << "Your " << "turn: "; 

        if(player_turn(s, player) == -1){ break; };
        // system("clear");
        print_board(s);
        int best_move = get_best_move(s, difficulty, com);
        std::cout << "COM\'s " << "turn: "; 

        if(ai_turn(s, difficulty, com) == -1){ break; }
        std::cout << best_move << '\n';
    }
}
