#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "game.h"
#include "neuralnet/neuralnet.h"

// Neural Network dimensions
const int inputs = 9;
const int hidden_size = 9;
const int outputs = 9;

class Player
{
public:
  int team;
  Game * game;
  Player(Game * g) : game (g), team (g->join_game()) {};
  virtual bool make_move(int) = 0;
  virtual int pick_move() = 0;
  virtual void end_game(int) = 0;
};

class ConsolePlayer : public Player
{
public:
  ConsolePlayer(Game * g) : Player(g) {};
  bool make_move(int m)
  {
    return game->make_move(m, team);
  }
  int pick_move()
  {
    cout << *game << endl;
    int m;
    cout << "Pick move (0-8):";
    cin >> m;
    return m;
  }
  void end_game(int winner)
  {
    if(winner == team)
    {
      cout << "You win!" << endl;
    }
    else if(winner == team * -1)
    {
      cout << "You lose!" << endl;
    }
    else
    {
      cout << "Tied!" << endl;
    }
  }
};

class AIPlayer : public Player
{
  NeuralNetwork nn;
public:
  AIPlayer(Game * g) : Player(g), nn(inputs, hidden_size, outputs) {};
  bool make_move(int);
  int pick_move();
  void end_game(int);
};

#endif // __PLAYER_H__
