#ifndef __NEURALNET_H__
#define __NEURALNET_H__

#include <vector>
#include <cmath>
#include <cstdlib>

using namespace std;

const int num_hidden_layers = 3;

class Neuron
{
  vector<float> weights; // Weights corresponding to each input
  float output; // Storage for output
public:
  Neuron(int); // Constructs a neuron with a given number of inputs
  void set_weights(vector<float>); // Assigns weight to given set of weights
  float get_output(); // Returns the value of the output holder
  float get_weight(int); // Returns the weight at a given index
  void update(vector<float>); // Executes the neuron for a given input set
};

class NeuronLayer
{
  int layer_size; // Number of neurons in the layer
  vector<Neuron> neurons;
public:
  NeuronLayer(int,int); // Constructs a neuron layer for a given size and number of inputs
  int get_size(); // Returns the number of neurons in the layer
  Neuron get_neuron(int); // Returns the neuron at a given index
  void set_neuron(int, Neuron); // Assigns a neuron at the given index
  void update(vector<float>); // Executes each neuron in the layer
  vector<float> get_outputs(); // Returns the set of outputs of the neurons
};

class NeuralNetwork
{
  vector<float> inputs; // Holder for input set
  vector<NeuronLayer> hidden_layers;
  NeuronLayer output_layer;
public:
  NeuralNetwork(int,int,int); // Constructs a network with the given dimensions
  void set_inputs(vector<float>); // Assigns the network the given inputs
  vector<float> get_outputs(); // Returns the outputs of the network
  void update(); // Executes the network with the inputs
  static float nonlinearFunction(float); // Nonlinear function used for this network
  static float nonlinearDerivative(float); // Derivative of the above nonlinear function
  void backpropagate(vector<float>); // Train the network using backpropagation with the given target outputs
};

float randomWeight();

#endif
