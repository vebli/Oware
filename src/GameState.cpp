#include "GameState.hpp"
#include <cassert>

GameState::GameState(){
    state = {};
    score = {};
}
GameState::GameState(Board s, std::array<int, 2> Score): state(s), score(Score) {}
GameState::GameState(const GameState &s){
    state = s.state;
    score = s.score;
};
int GameState::getSeeds(int pit) const { 
    return state[pit];
};
void GameState::setSeeds(int pit, int seeds) { state[pit] = seeds; }

void GameState::setScore(int player, int val) {
    assert(player >= 0 && player < 2);
    score[player] = val;
};

int GameState::getScore(int player) const {
    assert(player >= 0 && player < 2);
    return score[player];
};

void GameState::addToScore(int player, int val){
    score[player] += val;
};
