#include "Watch.hpp"
#include "GameLogic.hpp"
#include <cstdio>
#include <cstdlib>

struct BenchmarkData{
    BenchmarkData(int Winner, int Turns, const double Time): winner(Winner), turns(Turns), time(Time){
        state = GameState();
        decided = true;
    }
    BenchmarkData(const GameState &s, const double Time): state(s), time(Time), decided(false){
        winner = -1;
        turns = -1;
    } 
    int winner;
    int turns;
    double time;
    bool decided;
    GameState state;
};


const int player = player1;
const int com = player2;

BenchmarkData benchmark_com_v_random(const int seed, const int depth){
    Watch w; 
    GameState s({4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4}, {0, 0});
    int winner, best_move, random_move;
    const int max_turns = 100;
    bool decided = true;
    std::vector<int> legalMoves;
    int turns = 0;
    srand(seed);
    w.start();
    while (true){
        if(ai_turn(s, depth, com) == -1){
            winner = player;
            break;
        }
        turns ++;

        legalMoves = getLegalMoves(s, player);
        if(legalMoves.empty() || s.getScore(com) >= 25 ){
            winner = com;
            break;
        }
        random_move = legalMoves[rand() % legalMoves.size()];
        move(s, player, random_move);
        turns++;

        if(turns >= max_turns) {
            decided = false;
            break;
        }
    }
    const double elapsed = w.stop();

    return (decided) ?  BenchmarkData(winner, turns, elapsed) : BenchmarkData(s,elapsed) ;
}

void log_results(const std::vector<BenchmarkData> &results){
    int com_wins = 0;
    float game_time_decided = 0;
    float game_time_undecided = 0;
    int num_decided_games = 0;
    std::vector<GameState> undecided_games;
    for(int i = 0; i < results.size(); i++){
        if(!results[i].decided){ 
            game_time_undecided += results[i].time;
            undecided_games.push_back(results[i].state);
            continue; 
        } 
        else {
            num_decided_games++; 
            game_time_decided += results[i].time;
        }
        if(results[i].winner == com) {com_wins++;}
    }
   float com_win_rate_all = 100.f * com_wins / float(results.size());
   float average_game_time_all = 100.f * (game_time_decided + game_time_undecided)/ float(results.size());
   float com_win_rate_decided = 100.f * com_wins / float(num_decided_games);
   float average_game_time_decided = 100.f * game_time_decided / float(num_decided_games);

   printf("Undecided games:\n");
   for(auto game : undecided_games){
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
   printf("Decided games:\t [%d/%d]\t\t\n", num_decided_games, results.size());
   printf("COM win rate (all):\t\t %f%%\n", com_win_rate_all);
   printf("COM win rate (decided):\t\t %f%%\n", com_win_rate_decided);
   printf("Average game time (all):\t %fs\n", average_game_time_all);
   printf("Average game time (decided):\t %fs\n", average_game_time_decided);
}

int main(){
    std::vector<BenchmarkData> results;
    const int n = 100;
    const int depth = 10; 
    const int seed_base = 0;
    for(int i = 0; i < n; i++){
        system("clear");
        printf("Running benchmark [%d/%d]\n", i+1, n);
        results.push_back(benchmark_com_v_random(seed_base + i, depth));
    }
    log_results(results);
}

