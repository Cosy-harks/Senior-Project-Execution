#include "MathOps.h"
#include "Node.h"
#include "Layer.h"
#include "NeuralNetwork.h"
#include <sstream>
#include <iostream>
#include <iomanip>
#include <list>
#include <fstream>
#include <string>


int main()
{
	std::cout.precision(3);
	std::cout.fixed;
	//Node I = Node();
	//auto L = Layer();
	std::vector<std::vector<double>> input = { { 1, 0, 0 }, { 0, 1, 0 }, { 0, 0, 0 }, { 0, 1, 1 }, { 0, 0, 1 }, { 1, 0, 1 }, { 1, 1, 1 } }; //
	std::vector<std::vector<double>> output = { { 1, 0, 1 }, { 0, 1, 1 }, { 0, 0, 1 }, { 1, 0, 0 }, { 0, 1, 0 }, { 1, 1, 0 }, { 0, 0, 0 } }; //

	std::list<int> tiffs;
	std::list<int> tiffed;
	for (int i = 1; i <= 60000; i++)
	{
		tiffs.push_back(i);
	}

	for (int i = 0; i < 10; i++)
	{
		int y = round((double)rand() / (double)RAND_MAX*tiffs.size());
		tiffs.remove(y);
		tiffed.push_back(y);
		std::string tiff;
		if (y < 10) { tiff = "0000"+std::to_string(y); }
		else if (y / 10 < 10) { tiff = "000" + std::to_string(y); }
		else if (y / 100 < 10) { tiff = "00" + std::to_string(y); }
		else if (y / 1000 < 10) { tiff = "0" + std::to_string(y); }
		else { tiff = std::to_string(y); }
		std::cout << tiff << std::endl;
		tiff += ".tif";
		tiff = "../../mnist-train-images-tiff/" + tiff;
		std::cout << tiff << std::endl;
		std::ifstream tiffin (tiff);
		std::string line;
		if (tiffin.is_open()) {
			while (getline(tiffin, line))
			{
				std::cout << line << std::endl;
			}
		}
		else std::cout << "unable to open\n";
	}

	std::vector<int> D = { (int)input[0].size(), 7, 7, (int)output[0].size() };
/*Load This Binary inc networks
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
3:

3773
0: { -0.804, 1.3, -0.748, -0.484, -0.209, 0.957, -0.953 }
1: { 0.632, -1.39, -0.0692, -1.55, 0.0645, -0.815, 0.148 }
2: { -0.618, 0.417, 1.41, 1.57, -0.153, -0.298, 0.295 }
3: { 0.79, -0.324, -0.594, 0.0086, -0.134, 0.155, 0.51 }
0: { 0.663, 1.13, 0.921, 0.469, -0.0657, 0.919, 0.782 }
1: { 0.33, 0.8, 0.17, 0.606, -0.478, 0.666, 0.922 }
2: { -0.442, -0.552, -0.444, 0.598, 0.0734, -0.0952, -0.188 }
3: { 0.482, -0.0163, -0.0369, -0.0676, -0.279, 0.391, -0.127 }
4: { 0.151, 0.576, 0.562, -0.0338, -0.291, 0.185, 0.299 }
5: { 0.0897, 0.766, 0.242, 0.168, 0.571, 0.244, 0.424 }
6: { -0.037, 0.975, 0.812, 0.598, -0.129, 0.754, 0.761 }
7: { -0.0324, -0.381, -0.124, -0.701, -0.342, -0.537, -0.498 }
0: { -1.47, 1.57, 0.565 }
1: { 0.319, -0.653, 1.23 }
2: { -1.22, 0.147, 0.646 }
3: { 0.667, 0.35, -0.244 }
4: { 0.095, 0.171, 0.364 }
5: { 0.866, 1.26, -2.06 }
6: { 1.26, -0.295, -0.238 }
7: { 0.0743, -0.819, 0.0635 }
0:
1:
2:
3:

*/
	/*std::vector<std::vector<double>> fill = {
		{ -0.804, 1.3, -0.748, -0.484, -0.209, 0.957, -0.953 },
		{ 0.632, -1.39, -0.0692, -1.55, 0.0645, -0.815, 0.148 },
		{ -0.618, 0.417, 1.41, 1.57, -0.153, -0.298, 0.295 },
		{ 0.79, -0.324, -0.594, 0.0086, -0.134, 0.155, 0.51 },
		{ 0.663, 1.13, 0.921, 0.469, -0.0657, 0.919, 0.782 },
		{ 0.33, 0.8, 0.17, 0.606, -0.478, 0.666, 0.922 },
		{ -0.442, -0.552, -0.444, 0.598, 0.0734, -0.0952, -0.188 },
		{ 0.482, -0.0163, -0.0369, -0.0676, -0.279, 0.391, -0.127 },
		{ 0.151, 0.576, 0.562, -0.0338, -0.291, 0.185, 0.299 },
		{ 0.0897, 0.766, 0.242, 0.168, 0.571, 0.244, 0.424 },
		{ -0.037, 0.975, 0.812, 0.598, -0.129, 0.754, 0.761 },
		{ -0.0324, -0.381, -0.124, -0.701, -0.342, -0.537, -0.498 },
		{ -1.47, 1.57, 0.565 },
		{ 0.319, -0.653, 1.23 },
		{ -1.22, 0.147, 0.646 },
		{ 0.667, 0.35, -0.244 },
		{ 0.095, 0.171, 0.364 },
		{ 0.866, 1.26, -2.06 },
		{ 1.26, -0.295, -0.238 },
		{ 0.0743, -0.819, 0.0635 },
		{}, {}, {}, {} };
	*/
	NeuralNetwork N = NeuralNetwork(D);
	//N.fillNetwork(fill);
	//std::cout << vecToString(N[0][0].weight) << std::endl;
	//N[0].setWeightsOf(0, std::vector<double> { -0.379, -1.32, 0.154, 0.31, -0.209, 1.18, -0.31 });
	//std::cout << vecToString(N[0][0].weight) << std::endl;

	N.print();
	N.test(input, output);
	for (int i = 0; i < 20 * 1; i++)
	{
		N.train(input, output);
		N.test(input, output);
	//	for (int j = 0; j < 9; j++) {
	//		input[j][0] = { randoms(20) };
	//		output[j][0] = { input[j][0]*input[j][0] };
	//	}
	}
	N.print();

	N.test(input, output);
	//N.test(x, y);
	
	/*I.add(0.25);
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
	*/
	system("pause");
	return 0;
}