#include "GameLogic.hpp"
#include <cstdint>
#include <cstdlib>
GameLogic::GameLogic(GameState gameState) : gameState(gameState){}
void GameLogic::print(){
    gameState.print();
}
int GameLogic::getSeeds(int player, int pit){
    if(player == 1){
        return gameState.getSeeds(pit-1);
    }
    else if(player == 2){
        return gameState.getSeeds(pit+5);
    }
    else {
        std::cerr << "GameLogic::getSeeds expects player 1 or 2";
        std::exit(EXIT_FAILURE);
    }
}
void GameLogic::setSeeds(int player, int pit, int amount){
    assert(pit <= 6);
    if(player == 1){
        gameState.setSeeds(pit-1, amount);
    }
    if(player == 2){
        gameState.setSeeds(pit+5, amount);
    }
}
void GameLogic::move(int pit){
    int seeds = gameState.getSeeds(pit);
    int laps = seeds/12;
    int remainder = seeds % 12;
    int current_pit;

    for(int i = 0; i < 12; i++){
        current_pit = (pit + i) % 12;
        int new_seed_count;
        if(current_pit == pit){
            new_seed_count = laps;
        }
        else{
            new_seed_count = gameState.getSeeds(current_pit) + laps;
            if(i <= remainder){
                new_seed_count++;
            }
        }
        gameState.setSeeds(current_pit, new_seed_count);
    }
}

bool GameLogic::hasEmptyField(int player){
    bool hasEmptyField = true;
    for(int i = 1; i <= 6; i++){
        if(getSeeds(i, player)){
            hasEmptyField = false;
        }
    }
    return hasEmptyField;
} 
bool GameLogic::reachesOponent(int player, int pit){
    if(getSeeds(pit,player) > 6 - pit){
        return true;
    }
    return false;
}
bool GameLogic::checkGameOver(){
    for (int i = 1; i < 6; i++){
        reachesOponent(i, 1);
    }
    for (int i = 1; i < 6; i++){
        reachesOponent(i, 2);
    }
    return true;
}
std::vector<int> GameLogic::getForcedMoves(int player){
    bool hasEmptyField = true;
    for(int i = 1; i <= 6; i++){
        if(getSeeds(i, player)){
            hasEmptyField = false;
        }
    }
    if(hasEmptyField){

    }

    std::vector<int> legalMoves;
    if (player == 1){
        for(int i = 1; i <= 6; i++){
            if(reachesOponent(i, 1)){
                legalMoves.push_back(i);
            }
        }
    }
    else if (player == 2){
        for(int i = 1; i <= 6; i++){
            if(reachesOponent(i, 1)){
                legalMoves.push_back(i);
            }
        }
    }
    return legalMoves;
}

std::vector<int> GameLogic::getLegalMoves(int player){
    std::vector<int> legalMoves = getForcedMoves(player);
    if(legalMoves.empty() == true){
        for(int i = 1; i < 6; i++){
            if(getSeeds(i, player) != 0){
                legalMoves.push_back(i);
            }
        }
    }
    return legalMoves;
}

