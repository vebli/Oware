#include "GameLogic.hpp"
#include <cstdint>
GameLogic::GameLogic(GameState& gameState) : gameState(gameState){}
void GameLogic::print(){
    gameState.print();
}
bool GameLogic::hasEmptyField(uint8_t player){
    bool hasEmptyField = true;
    for(int i = 1; i <= 6; i++){
        if(gameState.getSeeds(i, player)){
            hasEmptyField = false;
        }
    }
    return hasEmptyField;
} 
bool GameLogic::reachesOponent(uint8_t pit, uint8_t player){
    if(gameState.getSeeds(pit,player) > 6 - pit){
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
std::vector<uint8_t> GameLogic::getForcedMoves(uint8_t player){
    bool hasEmptyField = true;
    for(int i = 1; i <= 6; i++){
        if(gameState.getSeeds(i, player)){
            hasEmptyField = false;
        }
    }
    if(hasEmptyField){

    }

    std::vector<uint8_t> legalMoves;
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

std::vector<uint8_t> GameLogic::getLegalMoves(uint8_t player){
    std::vector<uint8_t> legalMoves = getForcedMoves(player);
    if(legalMoves.empty() == true){
        for(int i = 1; i < 6; i++){
            if(gameState.getSeeds(i, player) != 0){
                legalMoves.push_back(i);
            }
        }
    }
    return legalMoves;
}

