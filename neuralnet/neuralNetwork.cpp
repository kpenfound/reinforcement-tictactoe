#include "neuralnet.h"
using namespace std;

NeuralNetwork::NeuralNetwork(int input_s, int hidden_s, int output_s)
  : inputs(input_s, 1.0),
  hidden_layers(vector<NeuronLayer>(num_hidden_layers, NeuronLayer(hidden_s, hidden_s))),
  output_layer(output_s, hidden_s)
  {
    hidden_layers[0] = NeuronLayer(hidden_s, input_s); // Different input size than the rest of the hidden layers
  }

void NeuralNetwork::set_inputs(vector<float> in)
{
  inputs.assign(in.begin(), in.end());
}

vector<float> NeuralNetwork::get_outputs()
{
  vector<float> outs = output_layer.get_outputs();
  return outs;
}

void NeuralNetwork::update()
{
  vector<float> ins (inputs);
  for(int i = 0; i < num_hidden_layers; i++)
  {
    hidden_layers[i].update(ins);
    ins = hidden_layers[i].get_outputs();
  }
  output_layer.update(ins);
}

float NeuralNetwork::nonlinearFunction(float a)
{
  return tanh(a);
}

float NeuralNetwork::nonlinearDerivative(float a)
{
  return 1 - (tanh(a) * tanh(a));
}

void NeuralNetwork::backpropagate(vector<float> expected)
{
  int output_size = output_layer.get_size();
  int hidden_size = hidden_layers[0].get_size();
  vector<float> output_error (output_size);
  vector< vector<float> > hidden_errors (num_hidden_layers, vector<float>(hidden_size));

  // Find output layer's error
  if(expected.size() != output_size)
  {
    // Something went wrong here
    throw "Expected output is a different length than output";
  }
  for(int i = 0; i < expected.size(); i++)
  {
    Neuron output_node = output_layer.get_neuron(i);
    float out = output_node.get_output();
    output_error[i] = (expected[i] - out) * (1 - out) * out;
  }

  NeuronLayer higher_layer = output_layer;
  for(int h = num_hidden_layers - 1; h >= 0; h--)
  {
    int higher_layer_size = higher_layer.get_size();
    // Find hidden layer's error
    for(int i = 0; i < hidden_size; i++)
    {
      hidden_errors[h][i] = 0;
      for(int j = 0; j < higher_layer_size; j++)
      {
        Neuron output_node = higher_layer.get_neuron(j);
        float weight = output_node.get_weight(i);
        hidden_errors[h][i] += weight * output_error[j];
      }
    }
    higher_layer = hidden_layers[h];
  }

  // Adjust hidden layer's weights
  for(int h = 0; h < num_hidden_layers; h++)
  {
    for(int i = 0; i < hidden_size; i++)
    {
      Neuron hidden_node = hidden_layers[h].get_neuron(i);
      int input_size = hidden_size;
      if(h == 0)
      {
        input_size = inputs.size();
      }
      vector<float> adjusted_weights (input_size);
      for(int k = 0; k < input_size; k++)
      {
        adjusted_weights[k] = hidden_node.get_weight(k);
        float delta =  hidden_errors[h][i] * nonlinearDerivative(hidden_node.get_output());
        adjusted_weights[k] += delta;
      }
      hidden_node.set_weights(adjusted_weights);
      hidden_layers[h].set_neuron(i, hidden_node);
    }
  }

  // Adjust output layer's weights
  vector<float> hidden_output = hidden_layers[num_hidden_layers - 1].get_outputs();
  for(int i = 0; i < output_size; i++)
  {
    Neuron output_node = output_layer.get_neuron(i);
    vector<float> adjusted_weights (hidden_size);
    for(int k = 0; k < hidden_size; k++)
    {
      adjusted_weights[k] = output_node.get_weight(k);
      float delta =  output_error[i] * nonlinearDerivative(output_node.get_output());
      adjusted_weights[k] += delta;
    }
    output_node.set_weights(adjusted_weights);
    output_layer.set_neuron(i, output_node);
  }
}
