#include "GameState.hpp"
GameState::GameState(std::array<int, 14>& State){
    setState(State); 
}
void GameState::setState(std::array<int, 14>& newState){
    state = newState;
} 

// There must be two rows and 6 "s" must be in one row.
// Could be improved with multiple "s" being placeholder for digits
void GameState::print(){ 
    auto board = boardTemplate;
    int state_index = 0;
    int captures_index = 12;
    int index_capture_row = 2;
    int index_player1_row = 3;
    int inedx_player2_row = 1;
    auto replace_with_state = [this](int& index, char* ch){
        std::string str = std::to_string(this->state[index]);
        for(int l = 0; l < str.length(); l++){
            *(ch+l) = str[l]; 
        }
        index++;
    };
        std::string& player1_row = board[index_player1_row];
        for(int i = 0; i < player1_row.size(); i++){
            if(player1_row[i] == 's'){
                replace_with_state(state_index, &player1_row[i]);
            }
        }

        std::string& player2_row = board[inedx_player2_row];
        for(int i = player2_row.size() - 1; i >= 0; i--){
            if(player2_row[i] == 's'){
                replace_with_state(state_index, &player2_row[i]);
            }
        }

        std::string& capture_row = board[index_capture_row];
        for(int i = 0; i < capture_row.size(); i++){
            if(capture_row[i] == 'c'){
                replace_with_state(captures_index, &capture_row[i]);
            }
        }

    for(auto row : board){
        for(auto ch : row){
            std::cout << ch;
        }
        std::cout << "\n";
    }
};
int GameState::getSeeds(int pit){
    return state[pit];
};
void GameState::setSeeds(int pit, int seeds){
    state[pit] = seeds;
}
