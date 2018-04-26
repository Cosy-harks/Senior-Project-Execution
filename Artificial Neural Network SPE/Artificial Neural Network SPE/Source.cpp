#include "MathOps.h"
#include "Node.h"
#include "Layer.h"
#include "NeuralNetwork.h"
#include "mnist/mnist_reader.hpp"
#include <sstream>
#include <iostream>
#include <iomanip>
#include <list>
#include <fstream>
#include <string>

// Idea Normalize deltaWeights before applying 


int main()
{
	std::cout.precision(3);
	std::cout.fixed;

	bool mnist = false;
	int dataNum = 20 * 15;

	std::vector<std::vector<double>> input = { { 1, 0, 0 } , { 0, 1, 1 },{ 0, 1, 0 }, { 0, 0, 0 }, { 0, 0, 1 }, { 1, 0, 1 }, { 1, 1, 1 } }; // };//
	std::vector<std::vector<double>> output = { { 1, 0, 1 } , { 1, 0, 0 },{ 0, 1, 1 }, { 0, 0, 1 }, { 0, 1, 0 }, { 1, 1, 0 }, { 0, 0, 0 }}; // };//


	if (mnist) {
		auto docs = mnist::read_dataset<std::vector, std::vector, double, uint8_t>("C:\\Users\\us3rs\\Documents\\GitHub\\mnist");

		input = docs.training_images;
		for (int a = 0; a < dataNum; a++) {
			output.push_back(std::vector<double>({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }));
			input.push_back(std::vector<double>());
			output[a][docs.training_labels[a]] = 1;
			//for (int b = 0; b < docs.training_images[0].size(); b++) {
			//	input[a].push_back(docs.training_images[a][b]);
			//}
		}
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
		{ -0.379, -1.32, 0.154, 0.31, -0.209, 1.18, -0.31 }
	,{ 0.596, -0.578, -1.01, 0.149, 0.0645, -0.692, -0.316 }
	,{ -1.46, -1.73, 0.986, -0.0762, -0.153, -1.84, 0.328 }
	,{ -0.236, 1.68, -0.628, -0.386, -0.134, 0.658, -0.103 }
	,{ 2.04, 2.23, 1.98, 2.44 }
	, { -0.124, -0.445, -1.1, -0.318 }
	,{ 1.18, 0.9, 0.842, 1.36 }
	,{ 0.341, -0.0202, -0.0868, 0.0703 }
	,{ 0.151, 0.576, 0.562, -0.0338 }
	,{ 0.327, 0.579, 0.0621, 0.15 }
	,{ -1.84, 2.37, 2.19, 2.3 }
	,{ -3.79e-05, 2.63, 2.54, 1.96 }
	,{ 1.72, 0.295, 1.49 }
	,{ 0.216, -1.79, 0.775 }
	,{ 1.33, -0.28, -1.3 }
	,{ -1.75, 3.19, 0.305 }
	,{ -0.00994, -1.28, -0.282 }
		,{}, {}, {}, {} };
		/*{ 2.39, 1.6, -2.38, -0.579, -0.0806, 1.81, -0.566 }
	,{ -4.92, -1.67, 4.35, 0.775, -0.612, -2.88, 2.58 }
	,{ 7.44, 2.61, -8.19, -2.12, -0.596, 5, -6.64 }
	,{ -1.68, -0.694, 2.45, 0.552, -0.942, -1.1, 1.47 }
	,{ -1.22, -2.06, -0.86, -1.92, -0.28, -0.848, -1.28 }
	,{ -0.307, -1.61, -0.154, -1.41, -0.448, -0.517, -0.959 }
	,{ 0.843, 0.339, 0.73, 0.46, -0.542, -0.209, 0.236 }
	,{ -0.218, 0.06, 0.0283, -0.637, -0.862, 0.0744, -0.348 }
	,{ -0.048, -0.28, 0.241, -0.623, -0.472, 0.034, -0.132 }
	,{ -2.12, -1.75, -1.16, -1.83, -0.76, -1.87, -1.67 }
	,{ 1.98, 0.705, 4.42, 0.731, -0.923, 2.74, 2.32 }
	,{ -2.38, -2.02, -1.94, -1.84, -1.07, -2.2, -2.11 }
	,{ -2.43, 2.02, 1.6 }
	,{ -2.15, 1.76, 0.567 }
	,{ -1.99, 1.3, 1.54 }
	,{ -1.47, 1.47, 0.283 }
	,{ 0.387, 0.227, 0.321 }
	,{ -0.144, 0.764, 0.671 }
	,{ -0.951, 0.684, 0.92 }
	,{ 1, 0.176, 0.352 }
	,{}, {}, {}, {}
	};
	
	
	/*{
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
	//N.shakeup();
	//std::cout << vecToString(N[0][0].weight) << std::endl;
	//N[0].setWeightsOf(0, std::vector<double> { -0.379, -1.32, 0.154, 0.31, -0.209, 1.18, -0.31 });
	//std::cout << vecToString(N[0][0].weight) << std::endl;

	N.print();
	
	if (mnist) {
		N.test(std::vector < std::vector<double>>{input[0]}, std::vector<std::vector<double>>{output[0]});
		N.test(std::vector < std::vector<double>>{input[1]}, std::vector<std::vector<double>>{output[1]});

		for (int i = 0; i < dataNum; )
		{
			
			std::vector<std::vector<double>> batch = std::vector<std::vector<double>>{ input[i] };
			std::vector<std::vector<double>> obatch = { output[i] };
			for (int _ = 0; _ < 20; _++) { batch.push_back(input[i]); obatch.push_back(output[i++]); }
			N.train(batch, obatch);
			N.print();
			N.test(batch, obatch);
			//	for (int j = 0; j < 9; j++) {
			//		input[j][0] = { randoms(20) };
			//		output[j][0] = { input[j][0]*input[j][0] };
			//	}
		}
	}
	else {
		for (int i = 0; i < 20 * 100; i++)
		{
			N.train(input, output);
			N.test(input, output);
		}
	}
	N.print();
	
	system("pause");
	return 0;
}