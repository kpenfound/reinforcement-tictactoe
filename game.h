#ifndef __GAME_H__
#define __GAME_H__

#include <vector>
#include <iostream>

using namespace std;

const int board_size = 3;

class Game
{
  vector< vector<int> > board;
  int players;
public:
  Game() : board(board_size, vector<int>(board_size, 0)), players (0) {};
  vector< vector<int> > get_board() const;
  bool make_move(int, int);
  int has_winner();
  int join_game();
};

ostream& operator<<(ostream&, const Game&);

#endif // __GAME_H__
