#include "GameLogic.hpp"
#include <cassert>
#include <cstdlib>
#include <iostream>


const std::vector<std::string> boardTemplate = {
    "|----|-----------------------------|----|",
    "|    | s  | s  | s  | s  | s  | s  |    |",
    "| c  |-----------------------------| c  |",
    "|    | s  | s  | s  | s  | s  | s  |    |",
    "|----|-----------------------------|----|"};

inline int getIndex(int player, int pit) {
    int result = -1;
    if (player == player1) {
        result = pit - 1;
    } else if (player == player2) {
        result = pit + 5;
    }
    assert(result >= 0);
    return result;
}


void print_board(const GameState &s) {
    auto board = boardTemplate;
    int state_index = 0;
    int captures_index = 0;
    constexpr int inedx_player2_row = 1;
    constexpr int index_capture_row = 2;
    constexpr int index_player1_row = 3;
    auto replace_with_state = [&](int val, char *ch) {
        std::string str = std::to_string(val);
        for (int l = 0; l < str.length(); l++) {
            *(ch + l) = str[l];
        }
    };

    std::string &player1_row = board[index_player1_row];
    for (int i = 0; i < player1_row.size(); i++) {
        if (player1_row[i] == 's') {
            assert(state_index < 6); //too many s' in template
            replace_with_state(s.getSeeds(state_index), &player1_row[i]);
            state_index++;
        }
    }

    std::string &player2_row = board[inedx_player2_row];
    for (int i = player2_row.size() - 1; i >= 0; i--) {
        if (player2_row[i] == 's') {
            assert(state_index < 12); //too many s' in template
            replace_with_state(s.getSeeds(state_index), &player2_row[i]);
            state_index++;
        }
    }

    std::string &capture_row = board[index_capture_row];
    for (int i = 0; i < capture_row.size(); i++) {
        if (capture_row[i] == 'c') {
            assert(captures_index < 2); // too many c's in template
            replace_with_state(s.getScore(captures_index), &capture_row[i]);
            captures_index++;
        }
    }

    for (auto row : board) {
        for (auto ch : row) {
            std::cout << ch;
        }
        std::cout << "\n";
    }
};

void move(GameState& gameState, const int player, const int pit){
    const int pit_index = getIndex(player, pit);
    const int seeds = gameState.getSeeds(pit_index);
    const int laps = seeds/12;
    const int remainder = seeds % 12;
    int current_pit;
    int new_seed_count;
    int captured = 0;
    bool captured_prev = true;

    gameState.setSeeds(pit_index, laps);
    for(int i = 11; i > 0; i--){
        current_pit = (pit_index + i) % 12;
        new_seed_count = gameState.getSeeds(current_pit) + laps;
        if(i <= remainder){
            new_seed_count++;

            if(captured_prev){
                if(player == player1 ){
                    if(current_pit > 5 && (new_seed_count == 3 || new_seed_count == 2)){
                        gameState.addToScore(player1, new_seed_count);
                        new_seed_count = 0;
                    }
                    else{
                        captured_prev = false;
                    }
                }
                else if (player == player2){
                    if(current_pit <= 5 && (new_seed_count == 3 || new_seed_count == 2)){
                        gameState.addToScore(player2, new_seed_count);
                        new_seed_count = 0;
                    }
                    else{
                        captured_prev = false;
                    }
                }
            }
        } 
        gameState.setSeeds(current_pit, new_seed_count);
    }
}


bool hasEmptyField(GameState s, const int player){
    bool hasEmptyField = true;
    int i = 1;
    while(i <= 6 && hasEmptyField){
        if(s.getSeeds(getIndex(player, i)) != 0){
            hasEmptyField = false;
        }
        i++;
    }
    return hasEmptyField;
}

bool reachesOpponent(const GameState &s, const int player, const int pit){
    if(s.getSeeds(getIndex(player, pit)) >= 7 - pit){
        return true;
    }
    return false;
}

std::vector<int> getForcedMoves(const GameState &s, const int player){
    std::vector<int> forcedMoves;
    const int opponent = player ^ 1;
    if(!hasEmptyField(s, opponent)){
        return forcedMoves;
    }
    for(int i = 1; i <= 6; i++){
        if(reachesOpponent(s, player, i)){
            forcedMoves.push_back(i);
        }
    }
    return forcedMoves;
}

std::vector<int> getLegalMoves(const GameState &s, const int player){
    std::vector<int> legalMoves = getForcedMoves(s, player);
    if(legalMoves.empty() == true){
        for(int i = 1; i <= 6; i++){
            if(s.getSeeds(getIndex(player, i)) != 0){
                legalMoves.push_back(i);
            }
        }
    }
    return legalMoves;
}

