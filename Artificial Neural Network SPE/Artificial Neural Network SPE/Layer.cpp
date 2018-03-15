#include "Layer.h"
#include <iostream>

Layer::Layer():
	neurons(std::vector<Node>()),
	bias(Node())
{
	bias.add(1.0);
}

Layer::Layer(unsigned int ns) :
	neurons(std::vector<Node>()),
	bias(Node())
{
	for(;neurons.size() < ns; )
	{
		neurons.push_back(Node());
	}
	bias.add(1.0);
}


Layer::~Layer()
{
}

// Push a node into the layer
//and makes it have at least as many
//weights as the first neuron
void Layer::push_neuron(Node n)
{
	neurons.push_back(n);
	while (neurons[0].weight.size() > neurons[neurons.size()-1].weight.size())
	{
		neurons[neurons.size() - 1].pushWeight((double)rand() / (double)RAND_MAX);
	}
}

// pushes one extra weight and deltaWeight onto each neuron in the layer
void Layer::push_weights()
{
	for (int i = 0; i < neurons.size(); i++)
	{
		neurons[i].pushWeight((double)rand()/(double)RAND_MAX-0.3);// (neurons[i].getWeightSize() + 0.5)*0.1);
		neurons[i].switchValue = 0;
		std::cout << neurons[i].switchValue;
		
	}
	bias.pushWeight((double)rand()/(double)RAND_MAX-0.3);
}

void Layer::push_weights(int ws)
{
	for (int i = 0; i < ws; i++)
	{
		push_weights();
	}
}

void Layer::function_of_input()
{
	for (int i = 0; i < neurons.size(); i++)
	{
		neurons[i].mathFunctions();
	}

	//will modify the weights of it not the output.
	bias.mathFunctions();
	bias.add(1.0);
}

void Layer::setFunction(int f, unsigned int index)
{
	if (index < getSize())
	{
		neurons[index].switchValue = f;
	}
	else
	{
		bias.switchValue = f;
	}
}

int Layer::getSize()
{
	return neurons.size();
}

void Layer::setWeight(int n, int w, double v)
{
	if (n < neurons.size())
	{
		neurons[n].weight[w] = v;
	}
	else if (n == neurons.size())
	{
		bias.weight[w] = v;
	}
}

void Layer::setWeightsOf(int node, std::vector<double> with)
{
	if (node < neurons.size())
	{
		for (int w = 0; w < neurons[node].weight.size(); w++) {
			setWeight(node, w, with[w]);
		}
	}
	else if(node == neurons.size())
	{
		for (int w = 0; w < bias.weight.size(); w++) {
			setWeight(node, w, with[w]);
		}
	}
}

double Layer::getWeight(int n, int w)
{
	if (n < neurons.size())
	{
		return neurons[n].weight[w];
	}
	else
	{
		return bias.weight[w];
	}
}

void Layer::setdWeight(unsigned int n, unsigned int w, double val)
{
	if (n < neurons.size())
	{
		neurons[n].deltaWeight[w] = val;
	}
	else
	{
		bias.deltaWeight[w] = val;
	}
}

double Layer::getdWeight(unsigned int a, unsigned int b)
{
	if (a < neurons.size())
	{
		return neurons[a].deltaWeight[b];
	}
	else
	{
		return bias.deltaWeight[b];
	}
}

double Layer::dOut_dIn(int n)
{
	if (n < neurons.size())
	{
		return neurons[n].dOut_dIn();
	}
	else
	{
		return bias.dOut_dIn();
	}
}

double Layer::getOutput(int n)
{
	if (n < neurons.size())
	{
		return neurons[n].getOutput();
	}
	else
	{
		return bias.getOutput();
	}
}

std::pair<std::vector<double>, std::vector<std::vector<double>>> Layer::make_matrices(bool biass)
{
	// first 1 by nodes, second nodes by weights
	std::pair<std::vector<double>, std::vector<std::vector<double>>> _1xN_NxW;
	{
		Node a;
		for (int i = 0; i < neurons.size(); i++)
		{
			a = neurons[i];
			_1xN_NxW.first.push_back(a.getOutput());

			_1xN_NxW.second.push_back(a.getWeights());
		}
		if (biass)
		{
			a = bias;
			_1xN_NxW.first.push_back(a.getOutput());

			_1xN_NxW.second.push_back(a.getWeights());
		}
	}
	return _1xN_NxW;
}

void Layer::input(std::vector<double> in)
{
	if (in.size() == getSize())
	{
		for (int i = 0; i < in.size(); i++)
		{
			neurons[i].add(in[i]);
		}
	}
}

std::vector<double> Layer::getIn()
{
	std::vector<double> back;
	for (int I = 0; I < getSize(); I++)
	{
		back.push_back(neurons[I].getIn());
	}
	return back;
}
