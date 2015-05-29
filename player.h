#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "game.h"
#include "neuralnet/neuralnet.h"

// Neural Network dimensions
const int inputs = 9;
const int hidden_size = 18;
const int outputs = 9;

class Player
{
public:
  int team;
  Game * game;
  Player(Game * g) : game (g), team (g->join_game()) {};
  virtual bool make_move(int) = 0;
};

class ConsolePlayer : public Player
{
public:
  bool make_move(int m)
  {
    return game->make_move(m, team);
  }
};

class AIPlayer : public Player
{
  NeuralNetwork nn;
public:
  AIPlayer(Game * g) : Player(g), nn(inputs, hidden_size, outputs) {};
  bool make_move(int);
  int pick_move();
};

#endif // __PLAYER_H__
