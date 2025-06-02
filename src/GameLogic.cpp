#include "GameLogic.hpp"
#include "GameState.hpp"
#include <array>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <limits>


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
    // assert(result >= 0);
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

bool hasEmptyField(const GameState &s, const int player){
    for(int i = 1; i <= 6; i++){
        if(s.getSeeds(getIndex(player, i)) != 0){
            return false;
        }
    }
    return true;
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

bool play_turn(GameState &s, const int player){
    std::vector<int> legalMoves;

    legalMoves = getLegalMoves(s, player);

    if(legalMoves.empty()){ 
        int opponent = player ^ 1;
        int left_over = 0;
        for(int i = 1; i <= 6; i++){
            left_over += s.getSeeds(getIndex(opponent, i));
            s.setSeeds(getIndex(opponent, i), 0);
        }
        s.addToScore(player, left_over);
        return false;
    }

    if(s.getScore(player) >= 25){
        return false;
    }
    int chosenMove;

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

    move(s, player, chosenMove);
    return true;
};


int minimax(const GameState s, int depth, int player){
    if(depth == 0) { 
        int max_player_score = s.getScore(player);
        int min_player_score = s.getScore(player ^ 1);
        if (max_player_score >= 25 && min_player_score < 25){
            return 1;
        }
        else if (max_player_score < 25 && min_player_score >= 25){
            return -1;
        }
        else{
            return 0;
        }

    }
    if(player) {
        int max = INT_MIN;
        const int opponent = player ^ 1;

        for (auto curr_move : getLegalMoves(s, player)){
            GameState child(s);
            move(child, player, curr_move);
            max = std::max(minimax(child, depth-1, opponent), max);
        }
        return max;
    }
    else {
        int min = INT_MAX;
        const int opponent = player ^ 1;

        for (auto curr_move : getLegalMoves(s, player)){
            GameState child(s);
            move(child, player, curr_move);
            min = std::min(minimax(child, depth-1, opponent), min);
        }
        return min;
    }
}

int get_best_move(const GameState& s, int depth, int player) {
    int bestScore = player ? INT_MIN : INT_MAX;
    int bestMove = -1;
    const int opponent = player ^ 1;

    for (int curr_move : getLegalMoves(s, player)) {
        GameState child(s);
        move(child, player, curr_move);
        int score = minimax(child, depth - 1, opponent);

        if (player && score > bestScore) {
            bestScore = score;
            bestMove = curr_move;
        } else if (!player && score < bestScore) {
            bestScore = score;
            bestMove = curr_move;
        }
    }

    return bestMove;
}
