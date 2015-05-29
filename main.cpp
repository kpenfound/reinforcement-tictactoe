#include "player.h"
#include <iostream>
using namespace std;

int main(void)
{
  NeuralNetwork nn (inputs, hidden_size, outputs);
  Game * g = new Game();
  AIPlayer p1 (g);
  AIPlayer p2 (g);
  int counter = 0;
  AIPlayer players[] = {p1, p2};
  while(g->has_winner() == 0)
  {
    while(! players[counter].make_move(players[counter].pick_move()))
    {};

    counter = (counter + 1) % 2;
    cout << *g << endl;
  }

  return 0;
}
