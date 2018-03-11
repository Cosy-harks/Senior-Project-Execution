#pragma once
#include <vector>

class Network
{
public:
	// Empty Network
	Network();
	// Shape for Network
	Network(std::vector<int>);
	// create Network with specific weights
	Network(std::vector<std::vector<std::vector<float>>>);
	~Network();

	// fill network shape with weights
	bool fill(std::vector<std::vector<float>>);

	void addLayer(unsigned int);

	void test(std::vector<std::vector<float>>, std::vector<std::vector<float>>);


};

