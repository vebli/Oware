#pragma once
#include <array>

using Board = std::array<int , 12>;

class GameState {
public:
  GameState();
  GameState(Board s, std::array<int, 2> Score);
  int getSeeds(int pit) const;

  void setSeeds(int pit, int seeds);
  void setState(Board newState);

  void setScore(int player, int val);
  int getScore(int player) const;

private:
  Board state;
  std::array<int, 2> score;
};

/*Indices:*/
/*    "|----|-----------------------------|----|",*/
/*    "|    | 11 | 10 | 8  | 8  | 7  | 6  |    |",*/
/*    "|    |-----------------------------|    |",*/
/*    "|    | 0  | 1  | 2  | 3  | 4  | 5  |    |",*/
/*    "|----|-----------------------------|----|"*/
