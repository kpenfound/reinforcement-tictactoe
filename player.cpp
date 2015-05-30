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
        availableMoves[(i * board_size) + j] = 0.1;
        if(board[i][j] == 0)
        {
          availableMoves[(i * board_size) + j] = 0.9;
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
  for(int i = 0; i < board_size; i++)
  {
    for(int j = 0; j < board_size; j++)
    {
      serializedBoard[(i * board_size) + j] = (float)(team * board[i][j]);
    }
  }

  nn.set_inputs(serializedBoard);
  nn.update();
  vector<float> outputs (nn.get_outputs());

  int max_out = 4;

  for(int i = 0; i < outputs.size(); i++)
  {
    if(outputs[i] > outputs[max_out])
    {
      max_out = i;
    }
  }
  return max_out;
}

void AIPlayer::end_game(int winner)
{
  if(winner != -2) // If not tie
  {
    int start_turn = 0;
    if(winner == -1)
    {
      start_turn = 1;
    }
    vector< vector< vector<int> > > turns (game->get_turns());
    vector<int> moves (game->get_moves());
    int turn = game->get_turn();
    vector< vector<int> > board (board_size, vector<int>(board_size, 0));

    while(start_turn <= turn)
    {
      if(start_turn > 0)
      {
        board.swap(turns[start_turn - 1]);
      }

      vector<float> serialized (board_size * board_size);
      for(int i = 0; i < board_size; i++)
      {
        for(int j = 0; j < board_size; j++)
        {
          serialized[(i * board_size) + j] = (float) board[i][j];
        }
      }

      vector<float> targets (board_size * board_size, 0.1);
      targets[moves[start_turn]] = 0.9;

      nn.set_inputs(serialized);
      nn.update();
      nn.backpropagate(targets);

      start_turn++;
    }
  }
}
