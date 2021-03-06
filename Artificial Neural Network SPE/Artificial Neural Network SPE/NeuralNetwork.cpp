#include "NeuralNetwork.h"
#include "MathOps.h"

NeuralNetwork::NeuralNetwork():
	collection( std::vector< Layer >() ),
	deriveSums( std::vector< std::vector< double >>() ),
	target( std::vector< double >() ),
	learningRate( 0.25 ),
	maxChange( 1.0 ),
	validError(0.001),
	last(0)
{
}

NeuralNetwork::NeuralNetwork( std::vector< int > v ):
	collection( std::vector< Layer >() ),
	deriveSums( std::vector< std::vector< double >>() ),
	target( std::vector< double >() ),
	learningRate( 0.01 ),
	//maxChange( 1.2 ),
	validError(0.00000001),
	last( v.size() - 1 )
{
	for (int i = 0; i < v.size(); i++)
	{
		collection.push_back(Layer(v[i]));
		deriveSums.push_back(std::vector< double >() );
		if (i < v.size() - 1)
		{
			collection[i].push_weights(v[i + 1]);
		}
		for (int j = 0; j < v[i]; j++)
		{
			deriveSums[i].push_back(0.0);
		}
	}
	/*for (unsigned int startNodes = 0; startNodes < collection[0].getSize(); startNodes++)
	{
		collection[0].setFunction(1, startNodes);
	}
	for (unsigned int endNodes = 0; endNodes < collection[last].getSize(); endNodes++) {
		collection[last].setFunction(0, endNodes);
	}*/
}

NeuralNetwork::~NeuralNetwork()
{
}

void NeuralNetwork::fillNetwork(std::vector<std::vector<double>> weights)
{
	int index = 0;
	int n = 0;
	for (int i = 0; i < weights.size(); i++)
	{
		if (i-n > collection[index].getSize()) { index++; n = i; }
		if (index < collection.size() - 1)
		{
			collection[index].setWeightsOf(i-n, weights[i]);
		}
	}
}

void NeuralNetwork::addLayer( unsigned int ns )
{
	collection.push_back( Layer( ns ) );
	last++;
}

void NeuralNetwork::shakeup()
{
	for (int i = 0; i < collection.size(); i++) {
		
		auto we = collection[i].make_matrices(true).second;
		for (int j = 0; j < we.size(); j++) {
			for (int k = 0; k < we[j].size(); k++) {
				we[j][k] += double(rand())/double(RAND_MAX);
			}
				collection[i].setWeightsOf(0, we[j]);
		}
	}
}

void NeuralNetwork::test( std::vector< std::vector< double > > input, std::vector< std::vector< double > > expected )
{
	std::vector<double> err;
	for (int i = 0; i < expected.size(); i++)
	{
		target = expected[i];
		collection[0].input(input[i]);
		forwardPropagation();
		auto M = collection[last].make_matrices(false).first;
		err.push_back(error(M, target));
		std::cout << vecToString(input[i]) << " --> " << vecToString/*Rounded*/(M) << " - " << vecToString(target) << std::endl;
	}
	std::cout << "%" << average(err) << std::endl;
}

void NeuralNetwork::train(std::vector<std::vector<double>> input, std::vector<std::vector<double>> expected)
{
	//may need to rework
	//std::vector<double> err;
	//std::vector<double> cost;
	for (int i = 0; i < expected.size(); i++)
	{
		target = expected[i];
		collection[0].input(input[i]);
		forwardPropagation();
		std::vector<double> a = collection[last].make_matrices(false).first;
		double err = error(a, target);
		//learningRate = average(cost);
		if ( err > validError ) {
			for (int L = 0; L < collection.size() - 1; L++)
			{
				for (int N = 0; N < collection[L].getSize(); N++)
				{
					for (int W = 0; W < collection[L + 1].getSize(); W++)
					{
						clearing();
						//std::cout << "cleared" << std::endl;
						double d = backwardPropagation(L, N, W);
						// std::cout << "Error With respect to weight: "<< L << ", " << N << ", " << W << " is: " << d << std::endl;
						//std::cout << d << std::endl;
						collection[L].setdWeight(N, W, collection[L].getdWeight(N, W) - d*learningRate);
					}
				}
			}
		}
	}
	//learningRate = average(cost);
	averageDeltaWeights(expected.size());
	// I did not update the weights
	updateWeights();
	
}

void NeuralNetwork::print()
{
	for (int i = 0; i < collection.size(); i++)
	{
		std::cout << collection[i].getSize() << " ";
	}
	std::cout << std::endl;
	for ( auto l : collection )
	{
		int i = 0;
		for ( auto w : l.make_matrices( true ).second ) 
		{
			std::cout << i << ": " << vecToString(w) << std::endl;
			i++;
		}
	}
}

void NeuralNetwork::assignDeriveSum(int L, int W)
{
	if (cwl > L + 3)
	{
		if (n < collection[cwl - 1].getSize())
		{
			deriveSums[cwl][cn] += collection[cwl - 1].getWeight(n, cn)*collection[cwl - 1].dOut_dIn(n)*deriveSums[cwl - 1][n];
		}
		else
		{
			// is this for bias
			deriveSums[cwl][cn] += collection[cwl - 1].getWeight(n, cn)*collection[cwl - 1].dOut_dIn(n);
		}
	}
	else if (cwl == L + 3)
	{
		if (n < collection[cwl - 1].getSize())
		{
			deriveSums[cwl][cn] += collection[L + 2].getWeight(n, cn)*collection[L + 2].dOut_dIn(n)*collection[L + 1].getWeight(W, n);
		}
		else
		{
			deriveSums[cwl][cn] += collection[L + 2].getWeight(n, cn)*collection[L + 2].dOut_dIn(n);
		}
	}
	else if (cwl == L + 2)
	{
		deriveSums[cwl][cn] = 1;
	}
}

void NeuralNetwork::clearing()
{
	for (int i = 0; i < deriveSums.size(); i++)
	{
		for (int j = 0; j < deriveSums[i].size(); j++)
		{
			deriveSums[i][j] = 0.0;
		}
	}
}

void NeuralNetwork::forwardPropagation()
{
	for ( int i = 0; i < collection.size(); i++ )
	{
		auto please = collection[i].getIn();
		collection[ i ].function_of_input();
		//std::cout << vecToString(please) << " -> " << vecToString(collection[i].make_matrices(false).first) << std::endl;
		// std::cout << i << ": " << vecToString(collection[i].make_matrices(true).first) << std::endl;
		//auto M = collection[i].make_matrices();
		//math M.first, M.second
		//auto vd = dot( collection[ i ].make_matrices() );
		if ( i + 1 < collection.size() )
		{
			collection[ i + 1 ].input(dot(collection[i].make_matrices(true)));
		}
		else
		{
			//output = dot(collection[i].make_matrices());
		}
	}
}

double NeuralNetwork::backwardPropagation(int L, int N, int W)
{
	// may need to rework
	double dErr_dLNW = 0.0;
	if (L + 1 < last)
	{
		// layer loop
		for (cwl = (L + 3 < last) ? L + 3 : last; cwl < collection.size(); cwl++)
		{
			// node in layer loop
			for (cn = 0; cn < collection[cwl].getSize(); cn++)
			{
				// node in next layer loop
				for (n = 0; n < collection[cwl - 1].getSize(); n++)
				{
					assignDeriveSum(L, W);
				}

			}
		}
		//for (int i = 0; i < output.size(); i++)
		//{
		//	for (int j = 0; j < collection[last].getSize(); j++)
		//	{
		//		dErr_dLNW += collection[last].dOut_dIn*collection[last].getWeight(j, i)*deriveSum[dsindex++];
		//	}
		//	dsindex -= output.size();
		//	deriveSum.push_back(dErr_dLNW);
		//	dErr_dLNW = 0.0;
		//	//dErr_dLNW += 2 * (output[i] - target[i]) * deriveSum[dsindex++];
		//}

		dErr_dLNW += calcErr(L, N, W);
	}
	else
	{

		//if (target[W] == 0) {
		dErr_dLNW = calcErr(L, N, W);
		//}
		//else {
		//	dErr_dLNW = ((collection[last].getOutput(W) - target[W])/target[W]) * collection[L].dOut_dIn(W)*collection[L].getOutput(N);
		//}
		//
		//
	}
	return dErr_dLNW;
}

double NeuralNetwork::calcErr(int L, int N, int W)
{
	double dErr_dLNW = 0.0;
	if (L + 1 < last)
	{
		for (cn = 0; cn < collection[last].getSize(); cn++)
		{
			double outErr = collection[last].getOutput(cn) - target[cn];
			if (outErr > 1 || outErr < -1)
			{
				dErr_dLNW += ((outErr > 0)? 1 : -1) * 2 * deriveSums[last][cn];
			}
			else
			{
				dErr_dLNW += ((collection[last].getOutput(cn) - target[cn]) * 2) * deriveSums[last][cn];
			}
		}
		dErr_dLNW *= collection[L + 1].dOut_dIn(W)*collection[L].getOutput(N);
	}
	else
	{
		dErr_dLNW = ((collection[last].getOutput(W) - target[W]) * 2) * collection[L].dOut_dIn(W)*collection[L].getOutput(N);
	}
	return dErr_dLNW;
}

/*void NeuralNetwork::wideDerivative(int cwl, int cn, int L, int W, double & dErr_dLNW)
{
	// May need to rework
	if (L + 3 == cwl)
	{
		for (int n = 0; n < collection[cwl - 1].getSize(); n++)
		{
			dErr_dLNW += collection[L + 2].getWeight(n, cn)*collection[L + 2].dOut_dIn(n)*collection[L + 1].getWeight(W, n);
		}
		deriveSums[cwl][cn] = dErr_dLNW;
		dErr_dLNW = 0.0;
		//dErr_dLNW *= collection[L + 1].dOut_dIn(W)*collection[L].getOutput(N);
	}
	else if (L + 2 == cwl)
	{
		for (int cn = 0; cn < collection[cwl].getSize(); cn++)
		{
			deriveSums[cwl][cn] = 1;
		}

	}
	else// L+3 < cwl
	{
		for (int n = 0; n < collection[cwl - 1].getSize(); n++)
		{
			dErr_dLNW += collection[cwl - 1].getWeight(n, cn)*collection[cwl - 1].dOut_dIn(n)*deriveSums[cwl][cn];
		}
		deriveSums[cwl][cn] = (dErr_dLNW);
		dErr_dLNW = 0.0;
	}
}*/

void NeuralNetwork::averageDeltaWeights(int averager)
{
	for (int L = 0; L < collection.size()-1; L++)
	{
		for (int N = 0; N < collection[L].getSize()+1; N++)
		{
			for (int W = 0; W < collection[L + 1].getSize(); W++)
			{
				collection[L].setdWeight(N, W, collection[L].getdWeight(N, W) / (double)averager);
			}
		}
	}
}

// move to Neuron each neuron can update it's own weights
// neurons can normalize the change in weights too
void NeuralNetwork::updateWeights()
{
	for (int L = 0; L < collection.size()-1; L++)
	{
		for (int N = 0; N < collection[L].getSize()+1; N++)
		{
			//std::vector<double> toNorm = collection[L].getdWeights(N);
			//std::cout << vecToString(toNorm) << std::endl;
			//normalize(toNorm);
			//collection[L].setdWeightsOf(N, toNorm);
			for (int W = 0; W < collection[L + 1].getSize(); W++)
			{
				// set dweights with norm
				//double change = collection[L].getdWeight(N, W);
				collection[L].setWeight(N, W, collection[L].getWeight(N, W) + collection[L].getdWeight(N, W));//((change > maxChange) ? maxChange : (change < -maxChange) ? -maxChange : change));
				collection[L].setdWeight(N, W, 0);
				//std::cout << collection[L].getdWeight(N, W);
			}
			//std::cout << std::endl;
		}
	}
}