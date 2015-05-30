#include "game.h"
using namespace std;

vector< vector<int> > Game::get_board() const
{
  return board;
}

bool Game::make_move(int space, int player)
{
  if(space >= 0 && space < (board_size * board_size) && board[(space / board_size)][(space % board_size)] == 0)
  {
    board[(space / board_size)][(space % board_size)] = player;
    turns[turn] = (board);
    moves[turn] = space;
    turn++;
    return true;
  }
  return false;
}

int Game::has_winner() const
{
  int winner = 0;

  for(int i = 0; i < board_size; i++)
  {
    // Rows
    if(board[i][0] != 0 && board[i][0] == board[i][1] && board[i][1] == board[i][2])
    {
      return board[i][0];
    }
    // Columns
    if(board[0][i] != 0 && board[0][i] == board[1][i] && board[1][i] == board[2][i])
    {
      return board[0][i];
    }
  }
  // Diagonals
  if(board[1][1] != 0)
  {
    if((board[0][0] == board[2][2] && board[1][1] == board[0][0])
       || (board[0][2] == board[2][0] && board[0][2] == board[1][1]))
    {
      return board[1][1];
    }
  }

  // Tie
  if(turn == board_size * board_size)
  {
    winner = -2;
  }

  return winner;
}

int Game::join_game()
{
  players++;
  if(players == 1)
  {
    return 1;
  }
  else
  {
    return -1;
  }
}


int Game::get_turn() const
{
  return turn;
}

vector<int> Game::get_moves() const
{
  return moves;
}

vector< vector< vector<int> > > Game::get_turns() const
{
  return turns;
}

void Game::reset()
{
  turn = 0;
  vector< vector<int> > newBoard(board_size, vector<int>(board_size,0));
  board = newBoard;
}

ostream& operator<<(ostream& out, const Game& g)
{
  vector< vector<int> > board (g.get_board());
  for(int i = 0; i < board_size; i++)
  {
    for(int j = 0; j < board_size; j++)
    {
      char tile = ' ';
      if(board[i][j] == 1)
      {
        tile = 'x';
      }
      else if(board[i][j] == -1)
      {
        tile = 'o';
      }
      out << '[' << tile << ']';
    }
    out << endl;
  }
  return out;
}
