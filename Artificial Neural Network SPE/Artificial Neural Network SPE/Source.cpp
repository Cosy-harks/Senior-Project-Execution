#include "MathOps.h"
#include "Node.h"
#include "Layer.h"
#include "NeuralNetwork.h"
#include <sstream>
#include <iostream>
#include <iomanip>


int main()
{
	std::cout.precision(3);
	std::cout.fixed;
	Node I = Node();
	auto L = Layer();
	std::vector<std::vector<double>> input = { { 1, 0, 0 }, { 0, 1, 0 }, { 0, 0, 0 }, { 0, 1, 1 }, { 0, 0, 1 }, { 1, 0, 1 }, { 1, 1, 1 } };
	std::vector<std::vector<double>> output = { { 1, 0, 1 }, { 0, 1, 1 }, { 0, 0, 1 }, { 1, 0, 0 }, { 0, 1, 0 }, { 1, 1, 0 }, { 0, 0, 0 } };
	std::vector<int> D = { (int)input[0].size(), 7, 4, (int)output[0].size() };
	/*Load This
3743
0: { -0.379, -1.32, 0.154, 0.31, -0.209, 1.18, -0.31 }
1: { 0.596, -0.578, -1.01, 0.149, 0.0645, -0.692, -0.316 }
2: { -1.46, -1.73, 0.986, -0.0762, -0.153, -1.84, 0.328 }
3: { -0.236, 1.68, -0.628, -0.386, -0.134, 0.658, -0.103 }
0: { 2.04, 2.23, 1.98, 2.44 }
1: { -0.124, -0.445, -1.1, -0.318 }
2: { 1.18, 0.9, 0.842, 1.36 }
3: { 0.341, -0.0202, -0.0868, 0.0703 }
4: { 0.151, 0.576, 0.562, -0.0338 }
5: { 0.327, 0.579, 0.0621, 0.15 }
6: { -1.84, 2.37, 2.19, 2.3 }
7: { -3.79e-05, 2.63, 2.54, 1.96 }
0: { 1.72, 0.295, 1.49 }
1: { 0.216, -1.79, 0.775 }
2: { 1.33, -0.28, -1.3 }
3: { -1.75, 3.19, 0.305 }
4: { -0.00994, -1.28, -0.282 }
0:
1:
2:
3:*/
	NeuralNetwork N = NeuralNetwork(D);

	N.print();
	N.test(input, output);
	for (int i = 0; i < 369; i++)
	{
		N.train(input, output);
		N.test(input, output);
	}
	N.print();

	I.add(0.25);
	//std::cout << "I.add(0.25) to input. Output = " << I.getOutput() << std::endl;
	L.push_neuron(I);
	//std::cout << "L.push_neuron(I) to layer." << std::endl;
	I.add(0.02);
	//std::cout << "I.add(0.02) to input." << std::endl;
	L.push_neuron(I);
	//std::cout << "L.push_neuron(I) to layer." << std::endl;

	L.push_weights();
	L.push_weights();
	//std::cout << "L.push_Weights() X 2" << std::endl;

	L.push_neuron(Node());
	//std::cout << "L.push_neuron(Node())" << std::endl;
	L.push_weights();
	//std::cout << "L.push_weights()" << std::endl;

	L.setFunction(1, 1);
	//std::cout << "L.setFunction(1, 1) // Activation Type, Index" << std::endl;
	L.function_of_input();
	//std::cout << "L.function_of_inputs() // func(input) = outputs" << std::endl;

	auto M = L.make_matrices(true);
	//std::cout << "M = L.make_matrices(true) // " << vecToString(M.first) << std::endl;

	std::vector<double> vd;
	for (int k = 0; k < M.second[0].size(); k++)
	{
		vd.push_back(0.0);
		for (int j = 0; j < M.first.size(); j++)
		{
			vd[k] += M.first[j] * M.second[j][k];
		}
	}
	//std::cout << "vd = M.first * M.secound // " << vecToString(vd) << std::endl;

	{
		std::string s = vecToString(M.first);
	//	std::cout << "1\n" << s << std::endl;
		for (auto i : M.second)
		{
			s = vecToString(i);
	//		std::cout << s << std::endl;
		}
		s = vecToString(vd);
	//	std::cout << s << std::endl;
	}
	for (int no = 2; no < 4; no++)
	{
		//iteration
	//	std::cout << no << std::endl;
		L.input(vd);
		L.function_of_input();

		M = L.make_matrices(true);

		for (int k = 0; k < M.second[0].size(); k++)
		{
			for (int j = 0; j < M.first.size(); j++)
			{
				vd[k] += M.first[j] * M.second[j][k];
			}
		}

		// On printout [column][row].	columns = all the weights going to the node == column
		//								row = all weights from node == row
		{
			// output of layer L into string s
			std::string s = vecToString(M.first);
	//		std::cout << s << std::endl;
			for (int i = 0; i < M.second.size(); i++)
			{
				// s = Right matrix weights of node_row[i]
				s = vecToString(M.second[i]);
	//			std::cout << s << std::endl;
			}
			s = vecToString(vd);
	//		std::cout << s << std::endl;
		}
	}
	double d = I.getOutput();
	//std::cout << "output befor activation\n" << d << std::endl;
	I.switchValue = 2;
	I.mathFunctions();
	d = I.getOutput();
	//std::cout << "output after activation\n" << d << std::endl;
	system("pause");
	return 0;
}