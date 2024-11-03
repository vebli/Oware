#include "GameLogic.hpp"
#include <cstdint>
#include <cstdlib>
GameLogic::GameLogic(GameState gameState) : gameState(gameState){}
void GameLogic::print(){
    gameState.print();
}
int GameLogic::getIndex(int player, int pit){
    int result = -1;
    if(player == 1){
        result = pit-1;
    }
    else if(player == 2){
        result = pit+5;
    }
    assert(result >= 0);
    return result;
}
int GameLogic::getSeeds(int player, int pit){
    return gameState.getSeeds(getIndex(player, pit));
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
void GameLogic::move(int player, int pit){
    pit = getIndex(player, pit);
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
    int i = 1;
    while(i <= 6 && hasEmptyField){
        if(getSeeds(player, i) != 0){
            hasEmptyField = false;
        }
        i++;
    }
    return hasEmptyField;
} 
bool GameLogic::reachesOponent(int player, int pit){
    if(getSeeds(player, pit) >= 7 - pit){
        return true;
    }
    return false;
}
bool GameLogic::checkGameOver(int player){
    bool result = true;
    int i = 1;
    while(i <= 6 && result){
        if(reachesOponent(player, i)){
            result = false;
        }
        i++;
    }
    return true;
}
std::vector<int> GameLogic::getForcedMoves(int player){
    std::vector<int> forcedMoves;
    int opponent = player ^ 3;
    if(!hasEmptyField(opponent)){
        return forcedMoves;
    }
    for(int i = 1; i <= 6; i++){
        if(reachesOponent(player, i)){
            forcedMoves.push_back(i);
        }
    }
    return forcedMoves;
}

std::vector<int> GameLogic::getLegalMoves(int player){
    std::vector<int> legalMoves = getForcedMoves(player);
    if(legalMoves.empty() == true){
        for(int i = 1; i <= 6; i++){
            if(getSeeds(player, i) != 0){
                legalMoves.push_back(i);
            }
        }
    }
    return legalMoves;
}

