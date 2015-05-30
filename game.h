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
  vector<int> moves;
  vector< vector< vector<int> > >turns;
  int turn;
public:
  Game()
    : board(board_size, vector<int>(board_size, 0)),
    players (0),
    turn(0),
    turns(board_size * board_size, vector< vector<int> >(board_size, vector<int>(board_size))),
    moves(board_size * board_size)
    {};
  vector< vector<int> > get_board() const;
  bool make_move(int, int);
  int has_winner() const;
  int join_game();
  int get_turn() const;
  vector<int> get_moves() const;
  vector< vector< vector<int> > > get_turns() const;
  void reset();
};

ostream& operator<<(ostream&, const Game&);

#endif // __GAME_H__
