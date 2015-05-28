#include "neuralnet.h"

NeuronLayer::NeuronLayer(int layer_s, int num_inputs)
  : layer_size (layer_s)
{
  Neuron n (num_inputs); // Initial neuron to use at each position
  neurons = std::vector<Neuron> (layer_s, n);
}

int NeuronLayer::get_size()
{
  return neurons.size();
}

Neuron NeuronLayer::get_neuron(int idx)
{
  if(idx >= neurons.size())
  {
    throw "Neuron index out of bounds!";
  }
  return neurons[idx];
}

void NeuronLayer::set_neuron(int idx, Neuron n)
{
  if(idx >= neurons.size())
  {
    throw "Neuron index out of bounds!";
  }
  neurons[idx] = n;
}

void NeuronLayer::update(std::vector<float> inputs)
{
  for(int i = 0; i < layer_size; i++)
  {
    neurons[i].update(inputs);
  }
}

void NeuronLayer::update(std::vector<float> inputs, std::vector<float> left)
{
  for(int i = 0; i < layer_size; i++)
  {
    std::vector<float> inputsWithLeft (inputs);
    inputsWithLeft.push_back(left[i]);
    neurons[i].update(inputsWithLeft);
  }
}

std::vector<float> NeuronLayer::get_outputs()
{
  std::vector<float> outputs (neurons.size());

  for(int i = 0; i < neurons.size(); i++)
  {
    outputs[i] = neurons[i].get_output();
  }

  return outputs;
}
