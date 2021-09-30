/*
@file NeuralNetwork.h
@author Aurélien Bück-Kaeffer
@version 0.6 09/30/2021
*/

//TODO: this class, and give it mutation functions to use it with genetic algorithms

#include "Node.h"

#ifndef NEURALNETWORK
#define NEURALNETWORK

namespace LogicGateNN {
	class NeuralNetwork {
	public:
		typedef std::vector<std::vector<std::vector<std::string>>> Net;//An array of dim 3 containing strings

	private:
		Net topology;										//Topology of the network (an array of dim 3 containing informatio tu build each node (see NeuralNetwork.cpp))
		std::vector<std::vector<LogicGateNN::Node>> Network;//Array of dim 2 containing all the nodes making up the network
		/*
		Network.size() is the number of lazers
		Network[0].size is the number of inputs
		Networt[Network.size()-1] is the number of outputs
		*/

	public:
		NeuralNetwork(Net topology);//Constructor when loading a previously saved NN
		NeuralNetwork(int Ninputs, int Noutputs, bool autofill);//Basic constructor with only the number of inputs and outputs

		int getNlayers();	//Returns the number of layers in the network
		int getNinputs();	//Returns the number of inputs of the network
		int getNoutputs();	//Returns the number of outputs of the network
	};
}

#endif // !NEURALNETWORK