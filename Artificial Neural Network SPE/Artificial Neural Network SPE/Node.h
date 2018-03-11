#pragma once
#include <vector>

class Node
{
public:
	Node();
	~Node();

	void add(double);
	double getOutput();
	/*void setWeight(unsigned int, double);
	double getWeight(unsigned int);
	void setDeltaWeight(unsigned int, double);
	double getDeltaWeight(unsigned int);
	int getWeightSize();
	void setSwitch(int);
	*/
	// good for creating matrix
	std::vector<double> getWeights();
	bool setWeights(std::vector<double>);
	double getIn();

	double dOut_dIn();
	void mathFunctions();

	void pushWeight(double);
	void pushWeights(int);

	double output;

	std::vector<double> weight;
	std::vector<double> deltaWeight;
	

	int switchValue;

private:
	double inputSum;
	double derivativeOutputToInput;

};

