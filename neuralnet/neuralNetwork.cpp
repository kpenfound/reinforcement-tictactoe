#include "neuralnet.h"

NeuralNetwork::NeuralNetwork(int input_s, int hidden_s, int output_s)
  : inputs(input_s, 1.0),
  hidden_layer(hidden_s, input_s + 1), // + 1 for left input
  output_layer(output_s, hidden_s) {}

void NeuralNetwork::set_inputs(std::vector<float> in)
{
  inputs.assign(in.begin(), in.end());
}

std::vector<float> NeuralNetwork::get_outputs()
{
  std::vector<float> outs = output_layer.get_outputs();
  return outs;
}

std::vector<float> NeuralNetwork::get_hidden_outputs()
{
  std::vector<float> outs = hidden_layer.get_outputs();
  return outs;
}

void NeuralNetwork::update(std::vector<float> left)
{
  hidden_layer.update(inputs, left);
  output_layer.update(hidden_layer.get_outputs());
}

float NeuralNetwork::nonlinearFunction(float a)
{
  return tanh(a);
}

float NeuralNetwork::nonlinearDerivative(float a)
{
  return 1 - (tanh(a) * tanh(a));
}

void NeuralNetwork::backpropagate(std::vector<float> expected)
{
  int output_size = output_layer.get_size();
  int hidden_size = hidden_layer.get_size();
  int input_size = inputs.size() + 1; // + 1 for left side input
  std::vector<float> output_error (output_size);
  std::vector<float> hidden_error (hidden_size);

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

  // Find hidden layer's error
  for(int i = 0; i < hidden_size; i++)
  {
    hidden_error[i] = 0;
    for(int j = 0; j < output_size; j++)
    {
      Neuron output_node = output_layer.get_neuron(j);
      float weight = output_node.get_weight(i);
      hidden_error[i] += weight * output_error[j];
    }
  }

  // Adjust hidden layer's weights
  for(int i = 0; i < hidden_size; i++)
  {
    Neuron hidden_node = hidden_layer.get_neuron(i);
    std::vector<float> adjusted_weights (input_size);
    for(int k = 0; k < input_size; k++)
    {
      adjusted_weights[k] = hidden_node.get_weight(k);
      float delta =  hidden_error[i] * nonlinearDerivative(hidden_node.get_output());
      adjusted_weights[k] += delta;
    }
    hidden_node.set_weights(adjusted_weights);
    hidden_layer.set_neuron(i, hidden_node);
  }

  // Adjust output layer's weights
  std::vector<float> hidden_output = hidden_layer.get_outputs();
  for(int i = 0; i < output_size; i++)
  {
    Neuron output_node = output_layer.get_neuron(i);
    std::vector<float> adjusted_weights (hidden_size);
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
