#include "player.h"

using namespace std;

bool AIPlayer::make_move(int m)
{
  if(!game->make_move(m, team))
  {
    // Train correct moves
    vector< vector<int> > board (game->get_board());
    vector<float> availableMoves (board_size * board_size);
    for(int i = 0; i < board_size; i++)
    {
      for(int j = 0; j < board_size; j++)
      {
        availableMoves[(i * board_size) + j] = 0;
        if(board[i][j] == 0)
        {
          availableMoves[(i * board_size) + j] = 1;
        }
      }
    }
    nn.backpropagate(availableMoves);

    return false;
  }
  return true;
}

int AIPlayer::pick_move()
{
  vector< vector<int> > board (game->get_board());
  vector<float> serializedBoard (board_size * board_size);
  vector<float> leftInput(board_size * board_size, 0);
  for(int i = 0; i < board_size; i++)
  {
    for(int j = 0; j < board_size; j++)
    {
      serializedBoard.push_back(1.0 * board[i][j]);
    }
  }

  nn.set_inputs(serializedBoard);
  nn.update(leftInput);
  vector<float> outputs (nn.get_outputs());

  int max_out = 4;

  for(int i = 0; i < serializedBoard.size(); i++)
  {
    if(serializedBoard[i] > serializedBoard[max_out])
    {
      max_out = i;
    }
  }
  return max_out;
}
