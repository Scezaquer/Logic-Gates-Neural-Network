/*
@file NeuralNetwork.h
@author Aurélien Bück-Kaeffer
@version 0.4 09/28/2021
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
		int Ninputs;	//Number of inputs in the network
		int Noutputs;	//Number of outputs in the network
		std::vector<LogicGateNN::Node*> InputNodes;
		std::vector<LogicGateNN::Node*> OutputNodes;
		int Nlayers;	//Number of layers
		Net topology;									//Topology of the network (an array of dim 3 containing informatio tu build each node (see NeuralNetwork.cpp))
		std::vector<LogicGateNN::Node> Network;			//Array of all the nodes making up the network

	public:
		NeuralNetwork(Net topology);//Constructor
	};
}

#endif // !NEURALNETWORK