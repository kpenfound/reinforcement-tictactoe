#include "player.h"
#include <iostream>
#include <ctime>
using namespace std;

int main(void)
{
  NeuralNetwork nn (inputs, hidden_size, outputs);
  int games_to_play = 1000;
  srand(time(0));


  Game * g = new Game();
  AIPlayer p1 (g);
  AIPlayer p2 (g);

  int p1wins = 0;
  int p2wins = 0;

  int counter = 0;
  AIPlayer players[] = {p1, p2};
  for(int i = 0; i < games_to_play; i++)
  {
    cout << "Starting game " << i << endl;
    while(g->has_winner() == 0)
    {
      while(! players[counter].make_move(players[counter].pick_move()))
      {};

      counter = (counter + 1) % 2;
    }
    cout << *g << endl;

    int winner = g->has_winner();
    players[0].end_game(winner);
    players[1].end_game(winner);
    g->reset();

    if(winner == 1)
    {
      p1wins++;
    }
    else if(winner == -1)
    {
      p2wins++;
    }
  }

  cout << "Player 1 wins: " << p1wins << endl;
  cout << "Player 2 wins: " << p2wins << endl;

  // Now let the user play
  bool end_game = false;
  ConsolePlayer cp (g);
  cp.team = players[1].team;
  while(!end_game)
  {
    cout << "playing the computer:" << endl;
    while(g->has_winner() == 0)
    {
      // User goes first
      int space = cp.pick_move();
      while(!cp.make_move(space))
      {
        space = cp.pick_move();
      }

      if(g->has_winner() == 0)
      {
        while(! p1.make_move(p1.pick_move()))
        {};
      }
    }
    cout << *g << endl;
    int winner = g->has_winner();
    p1.end_game(winner);
    cp.end_game(winner);
    g->reset();

    char uinput;
    cout << "Play again? (y/n)";
    cin >> uinput;
    end_game = ! (uinput == 'y' || uinput == 'Y');
  }

  return 0;
}
