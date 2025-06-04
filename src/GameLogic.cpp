#include "GameLogic.hpp"
#include "GameState.hpp"
#include <cassert>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <limits>
#include <future>


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
    std::vector<int> special_cases; 
    const int opponent = player ^ 1;
    if(!hasEmptyField(s, opponent)){
        return forcedMoves;
    }
    for(int i = 1; i <= 6; i++){
        if(reachesOpponent(s, player, i)){
            if(s.getSeeds(getIndex(player, i)) % 12 == 12 - i){
            /*
            Moves that capture all the seeds given to the opponent leaving him starved anyway.
            Only allowed if no other moves are playable 
            */
                special_cases.push_back(i);
            }
            else { forcedMoves.push_back(i); }
        }
    }
    if(forcedMoves.empty()){
        return special_cases;
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


//POST: Gets user input and plays turn, returns true if move was played and false if no legal moves can be played
int player_turn(GameState &s, const int player){
    std::vector<int> legalMoves;
    int chosen_move = -1;

    if(s.getScore(player^1) >= 25){
        return chosen_move;
    }

    legalMoves = getLegalMoves(s, player);
    if(legalMoves.empty()){ 
        int opponent = player ^ 1;
        int left_over = 0;
        for(int i = 1; i <= 6; i++){
            left_over += s.getSeeds(getIndex(opponent, i));
            s.setSeeds(getIndex(opponent, i), 0);
        }
        s.addToScore(player, left_over);
        return chosen_move;
    }

    

    while(true){
        std::cin >> chosen_move;
        if (std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Illegal Move.\n";
        }
        else {
            break;
        }
    }

    while (std::find(legalMoves.begin(), legalMoves.end(), chosen_move) == legalMoves.end()){
        std::cout << "Illegal Move\n";
        std::cin >> chosen_move;
    }

    move(s, player, chosen_move);

    return chosen_move;
};


int minimax(const GameState s, int depth, int max_player, int player){
    if(depth == 0) { 
        const int max_player_score = s.getScore(max_player);
        const int min_player_score = s.getScore(max_player ^ 1);
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
    if(player == max_player) {
        int max = INT_MIN;
        const int opponent = player ^ 1;

        for (auto curr_move : getLegalMoves(s, player)){
            GameState child(s);
            move(child, player, curr_move);
            max = std::max(minimax(child, depth-1, max_player, opponent), max);
        }
        return max;
    }
    else {
        int min = INT_MAX;
        const int opponent = player ^ 1;

        for (auto curr_move : getLegalMoves(s, player)){
            GameState child(s);
            move(child, player, curr_move);
            min = std::min(minimax(child, depth-1, max_player, opponent), min);
        }
        return min;
    }
}
int minimax_alpha_beta(const GameState s, const int depth, int alpha, int beta, const int max_player, const int player){
    if(depth == 0) { 
        const int max_player_score = s.getScore(max_player);
        const int min_player_score = s.getScore(max_player ^ 1);
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
    if(player == max_player) {
        int max = INT_MIN;

        for (auto curr_move : getLegalMoves(s, player)){
            GameState child(s);
            move(child, player, curr_move);
            max = std::max(minimax_alpha_beta(child, depth-1, alpha, beta, max_player, player ^ 1), max);
            alpha = std::max(alpha, max);
            if(alpha >= beta){ 
                return alpha; 
            }
        }
        return max;
    }
    else {
        int min = INT_MAX;

        for (auto curr_move : getLegalMoves(s, player)){
            GameState child(s);
            move(child, player, curr_move);
            min = std::min(minimax_alpha_beta(child, depth-1, alpha, beta, max_player, player ^1), min);
            beta = std::min(beta, min);
            if(beta <= alpha){ 
                return beta; 
            }
        }
        return min;
    }
}

int get_best_move(const GameState& s, const bool run_parallel, const int depth, const int player) {
    // const unsigned int num_of_threads = std::thread::hardware_concurrency();
    int bestScore = player ? INT_MIN : INT_MAX;
    int bestMove = -1;
    const int opponent = player ^ 1;

    auto legalMoves = getLegalMoves(s, player);

    if (run_parallel){
        std::vector<GameState> children(legalMoves.size());
        for (int i = 0; i < legalMoves.size(); i++){
            GameState child(s);
            move(child, player, legalMoves[i]);
            children[i] = child;
        }
        std::vector<std::future<int>> threads(legalMoves.size()); //adjust for num of threads 
        for (int i = 0; i < threads.size(); i++){
            threads[i] = std::async(std::launch::async, minimax_alpha_beta, children[i], depth -1, INT_MIN, INT_MAX, player, opponent);
        }

        int best_score = player ? INT_MIN : INT_MAX;
        int best_score_index = 0;
        int score;
        for (int i = 0; i < threads.size(); i++){
            if(player){
                score = threads[i].get();
                if(score > best_score){
                    best_score = score;
                    best_score_index = i;
                }
            }
            else{
                score = threads[i].get();
                if(score < best_score){
                    best_score = score;
                    best_score_index = i;
                }
            }
        }

        return legalMoves[best_score_index];

    }
    else {
        for (int curr_move : legalMoves) {
            GameState child(s);
            move(child, player, curr_move);
            int score = minimax_alpha_beta(child, depth - 1, INT_MIN, INT_MAX, player, opponent);

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
}

int ai_turn(GameState &s, const bool run_parallel, const int depth, const int com){
    int best_move = -1;
    if(s.getScore(com^1) >= 25){
        return best_move;
    }
    best_move = get_best_move(s, false, depth, com);
    if(best_move == -1){
        int opponent = com ^ 1;
        int left_over = 0;
        for(int i = 1; i <= 6; i++){
            left_over += s.getSeeds(getIndex(opponent, i));
            s.setSeeds(getIndex(opponent, i), 0);
        }
        s.addToScore(com, left_over);
    }
    else{
        move(s, com, best_move);
    }
    return best_move;

}
