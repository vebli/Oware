#include "Watch.hpp"
#include "GameLogic.hpp"
#include <cstdio>
#include <cstdlib>

struct BenchmarkData{
    BenchmarkData(int Winner, int Turns, double Time): winner(Winner), turns(Turns), time(Time){
        error_state = GameState();
        failed = false;
    }
    BenchmarkData(const GameState &s): error_state(s), failed(true){
        winner = -1;
        turns = -1;
        time = -1;
    } 
    int winner;
    int turns;
    double time;
    bool failed;
    GameState error_state;
};


const int player = player1;
const int com = player2;

BenchmarkData benchmark_com_v_random(const int seed, const int depth){
    Watch w; 
    GameState s({4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4}, {0, 0});
    int winner, best_move, random_move;
    bool failed = false;
    std::vector<int> legalMoves;
    int turns = 0;
    srand(seed);
    w.start();
    while (true){
        best_move = get_best_move(s, depth, com);
        if(best_move == -1 || s.getScore(player) >= 25 ){
            winner = player;
            break;
        }
        move(s, com, best_move);
        turns ++;

        legalMoves = getLegalMoves(s, player);
        if(legalMoves.empty() || s.getScore(com) >= 25 ){
            winner = com;
            break;
        }
        random_move = legalMoves[rand() % legalMoves.size()];
        move(s, player, random_move);
        turns++;

        if(turns > 100) {
            failed = true;
            break;
        }
    }
    double elapsed = w.stop();

    return (failed == true) ? BenchmarkData(s) : BenchmarkData(winner, turns, elapsed);
}

void log_results(const std::vector<BenchmarkData> &results){
    int com_wins = 0;
    float game_time = 0;
    int successful_games = results.size();
    std::vector<GameState> failedGames;
    for(int i = 0; i < results.size(); i++){
        if(results[i].failed){ 
            successful_games--; 
            failedGames.push_back(results[i].error_state);
            continue; 
        }
        if(results[i].winner == com) {com_wins++;}
        game_time += results[i].time;
    }
   float com_win_rate = 100.f * com_wins / float(successful_games);
   float average_game_time = 100.f * game_time / float(successful_games);

   printf("Failed games:\n");
   for(auto game : failedGames){
       print_board(game);
       printf("Legal moves: \n");
        
       printf("Player 1: ");
       for(int legalMove : getLegalMoves(game, player1)){
           printf("%d ", legalMove);
       }
       printf("\n");
       printf("Player 2: ");
       for(int legalMove : getLegalMoves(game, player2)){
           printf("%d ", legalMove);
       }
       printf("\n");
   }
   printf("Successful games:\t [%d/%d]\n", successful_games, results.size());
   printf("COM win rate:\t\t %f%%\n", com_win_rate);
   printf("Average game time:\t %fs\n", average_game_time);
}

int main(){
    std::vector<BenchmarkData> results;
    const int n = 100;
    const int depth = 6; 
    const int seed_base = 0;
    for(int i = 0; i < n; i++){
        system("clear");
        printf("Running benchmark [%d/%d]\n", i+1, n);
        results.push_back(benchmark_com_v_random(seed_base + i, depth));
    }
    log_results(results);

}

