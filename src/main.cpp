// #include "GameState.hpp"
// #include "GameLogic.hpp"
#include "Oware.hpp"
#include <cstdlib>
#include <iostream>
#include <limits>
const std::string game_modes= R"(

0       vs COM
1       local multiplayer

)";


int main(){
    int chose_mode;

    system("clear");
    std::cout << "Choose game mode:\n";
    std::cout <<  game_modes;
    while(true){
        std::cin >> chose_mode;
        if (std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid game mode.\n";
        }
        else if(chose_mode > 2) {
            std::cout << "Invalid game mode.\n";
        }
        else {
            break;
        }
    }
    switch(chose_mode){
        case 0: 
            system("clear");
            std::cout << "Choose difficulty (1 - 10)";
            int difficulty;
            while(true){
                std::cin >> difficulty;
                if (std::cin.fail()){
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    // std::cout << "Invalid game mode.\n";
                }
                else if(chose_mode > 2) {
                    continue;
                    // std::cout << "Invalid game mode.\n";
                }
                else {
                    break;
                }
            }
            Oware::play_singleplayer(difficulty); 
            break;
        case 1: 
            Oware::play_local_multiplayer(); 
            break;
    }
    return 0;
}

