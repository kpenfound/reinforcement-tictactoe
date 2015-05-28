#ifndef __RECURRENT_H__
#define __RECURRENT_H__

#include <vector>
#include <algorithm>

#include "neuralnet/neuralnet.h"

// Recurrent net
const int NUM_LAYERS = 1;
const int LAYER_SIZE = 3;

// Neural net
const int INPUT_SIZE = 3;
const int HIDDEN_SIZE = 6;
const int OUTPUT_SIZE = 3;

// The recurrent neural network: A system of neural networks
class RecurrentNeuralNetwork
{
  std::vector< std::vector<NeuralNetwork> > rnn; // The system of neural networks
  std::vector< std::vector<float> > outputs; // Storage for the set of output vectors
public:
  RecurrentNeuralNetwork(); // Empty constructor to use values seen in this header
  void update(std::vector< std::vector<float> > *); // Executes the network for inputs
  std::vector< std::vector<float> > get_outputs(); // Returns output set
  void train(std::vector< std::vector<float> >); // Executes backpropagation training
};

#endif // __RECURRENT_H__
