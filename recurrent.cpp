#include "recurrent.h"

// Basic constructor using defined constants
RecurrentNeuralNetwork::RecurrentNeuralNetwork()
  : rnn (NUM_LAYERS, std::vector<NeuralNetwork> (LAYER_SIZE, NeuralNetwork(INPUT_SIZE, HIDDEN_SIZE, OUTPUT_SIZE))),
  outputs (LAYER_SIZE, std::vector<float> (OUTPUT_SIZE)) {}

// Executes the network for a given input set
void RecurrentNeuralNetwork::update(std::vector< std::vector<float> > * inputVector)
{
  for(int i = 0; i < NUM_LAYERS; i++) // Loop through the layers of networks
  {
    for(int j = 0; j < LAYER_SIZE; j++) // Loop through each network in this layer
    {
      std::vector<float> in (inputVector->at(j)); // The input for this network
      std::vector<float> left (HIDDEN_SIZE, 0); // The incoming left-side input for this network
      if(i > 0) // In a multi-layer situation, our inputs will be the outputs of the previous layer
      {
        in = rnn[i-1][j].get_outputs();
      }
      if(j > 0) // Our left side inputs will be the hidden_layer outputs of the network to the left
      {
        left = rnn[i][j-1].get_hidden_outputs();
      }
      rnn[i][j].set_inputs(in);
      rnn[i][j].update(left); // Execute network
      outputs[j] = rnn[i][j].get_outputs(); // Update our outputs holder with this network's output
    }
  }
}

// Returns output set
std::vector< std::vector<float> > RecurrentNeuralNetwork::get_outputs()
{
  return outputs;
}

// Trains network with backpropagation training for a given target output set
void RecurrentNeuralNetwork::train(std::vector< std::vector<float> > targets)
{
  for(int i = 0; i < LAYER_SIZE; i++)
  {
    rnn[NUM_LAYERS - 1][i].backpropagate(targets[i]);
  }
}
