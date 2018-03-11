#pragma once
#include <vector>

//Model
class Neuron
{
	double output;
	double input;

	std::vector<double> weight;
	std::vector<double> deltaWeight;

	int switchValue;
	double derivative;
public:
	Neuron();
	~Neuron();

	void add(double);
	double getOutput();

	std::vector<double> getWeights();
	bool setWeights(std::vector<double>);

};

