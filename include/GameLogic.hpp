#pragma once
#include "GameState.hpp"
#include <vector>

enum {
    player1 = 0,
    player2 = 1
};

void print_board(const GameState& s);

void print();
void move(GameState& gameState, const int player, const int pit);

bool isLegalMove(int player, int pit);
std::vector<int> getLegalMoves(const GameState &s, const int player);
std::vector<GameState> findChildren();

int getIndex(int player, int pit);
bool capture(int start, int stop);
bool reachesOpponent(GameState &s, const int player, const int pit);
bool hasEmptyField(const GameState &s, const int player);
bool canGiveToOpponent(GameState &s, int player); 
std::vector<int> getForcedMoves(GameState &s, int player);
int player_turn(GameState &s, int player);
int minimax(const GameState s, int depth, int player);
int get_best_move(const GameState& s, const bool run_parallel, const int depth, const int player); 
int ai_turn(GameState &s, const bool run_parallel, const int depth, const int com);
