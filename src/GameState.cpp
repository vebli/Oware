#include "game_state.hpp"
#include <cassert>
GameState::GameState(std::array<int, 12>& State, int Player1Captures, int Player2Captures){
    setState(State);
    player1Captures = Player1Captures;
    player2Captures = Player2Captures;
    boardTemplate = {
        "|----|-----------------------------|----|",
        "|    | s  | s  | s  | s  | s  | s  |    |",
        "| c  |-----------------------------| c  |",
        "|    | s  | s  | s  | s  | s  | s  |    |",
        "|----|-----------------------------|----|"
    };
}
void GameState::setState(std::array<int, 12>& newState){
    state = newState;
} 
void GameState::print(){
        std::vector<std::string> board = boardTemplate;
        int currentPit = 0;
        int currentCapturePit = 0;
        for(int i = 0; i < board.size(); i++){
            for(int j = 0; j < board[i].size(); j++){
                std::string seedCount_str = std::to_string(state[currentPit]);
                if(board[i][j] == 's'){
                    for(int k = 0; k < seedCount_str.size(); k++){
                        board[i][j+k] = seedCount_str[k];
                    }
                        assert(currentPit<= 13);
                        currentPit++;
                }
                else if(board[i][j] == 'c'){
                    if(currentCapturePit == 0){
                    std::string captures_str = std::to_string(player1Captures);
                        for(int l = 0; l < captures_str.size(); l++){
                            board[i][j+l] = captures_str[l];
                        }
                        currentCapturePit = 1;
                    }
                    else if (currentCapturePit == 1){
                        std::string captures_str = std::to_string(player2Captures);
                        for(int l = 0; l < captures_str.size(); l++){
                            board[i][j+l] = captures_str[l];
                        }
                    }

                };
            };
        }
        for (auto row : board){
            std::cout << row << "\n";
        }
    }

