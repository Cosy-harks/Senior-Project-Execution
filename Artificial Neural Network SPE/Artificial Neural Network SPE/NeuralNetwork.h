#pragma once
#include "Layer.h"

class NeuralNetwork
{
public:
	// empty Neural Network
	NeuralNetwork();

	// Takes a shaping vector<int>: input, hidden, ..., hidden, output layers.
	NeuralNetwork(std::vector<int>);
	~NeuralNetwork();

	// create a network with shape vector then fill with weights in a vector of vectors
	// 
	void fillNetwork(std::vector<std::vector<double>>);

	// push a layer with # of neurons in the layer
	void addLayer(unsigned int);

	void shakeup();

	// first < < vec > > of start values, < < vec > > expected values
	//prints the average error squared
	void test(std::vector<std::vector<double>>, std::vector<std::vector<double>>);

	void train(std::vector<std::vector<double>>, std::vector<std::vector<double>>);

	void print();

	Layer operator[](int L) { return collection[L]; }

private:
	//the layers of the neural network
	std::vector<Layer> collection;

	// the calculated output rather than another layer
	std::vector<double> target;
	std::vector<std::vector<double>> deriveSums;


	double learningRate;
	double maxChange;
	double validError;
	int last;

	// current working layer, node in next layer, current node
	int cwl, n, cn;
	//sets a deriveSum[][] value from the backProp func
	void assignDeriveSum(int L, int W);
	// cleans data holding vars for training
	void clearing();
	// moves the information along the network
	void forwardPropagation();
	//layer, node, weight return deltaError_to_deltaWeight
	double backwardPropagation(int, int, int);

	double calcErr(int L, int N, int W);

	// current working layer, current node, Tended to layer, deriveSum, specific index
	/*void wideDerivative(int, int, int, int, double &);*/

	void averageDeltaWeights(int);

	void updateWeights();
};

