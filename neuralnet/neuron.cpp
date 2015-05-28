#include "neuralnet.h"

Neuron::Neuron(int num_inputs)
  : weights(num_inputs),
  output(0)
  {
    for(int i = 0; i < num_inputs; i++)
    {
      weights[i] = randomWeight();
    }
  }

void Neuron::set_weights(std::vector<float> w)
{
  weights.assign(w.begin(), w.end());
}

float Neuron::get_output()
{
  return output;
}

float Neuron::get_weight(int idx)
{
  if(idx >= weights.size())
  {
    // Something went wrong
    throw "Neuron weight index out of range!";
  }
  return weights[idx];
}

void Neuron::update(std::vector<float> inputs)
{
  int inputSize = inputs.size();
  float sum = 0.0;

  for(int i=0; i < inputSize; ++i)
  {
    sum += weights[i] * inputs[i];
  }

  output = NeuralNetwork::nonlinearFunction(sum);
}

float randomWeight()
{
  float w = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
  return w;
}

