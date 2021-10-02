/*
@file NeuralNetwork.h
@author Aurélien Bück-Kaeffer
@version 0.7 10/01/2021
*/

//TODO: this class, and give it mutation functions to use it with genetic algorithms
//TODO: Handle exceptions

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

		std::vector<bool> run();	//Mais function of the nn, updates every node, and consequently the output of the network. Returns said output
		std::vector<bool> run(int index, bool value);	//Updates a single input of the network, and changes only the nodes that should be affected to save ressources. Recommanded if the network is processing live on values that do not change all at once (one or two at a time) and very often.
		std::vector<bool> run(std::vector<bool>  inputs);	//Takes a vector of size equal to the number of inputs of the network

		int getNlayers();	//Returns the number of layers in the network
		int getNinputs();	//Returns the number of inputs of the network
		int getNoutputs();	//Returns the number of outputs of the network
		std::vector<bool> getOutputs();	//return the current values of the last layer, DOES NOT UPDATE THEM, USE NeuralNetwork.run() FOR THAT
		void setInputs(std::vector<bool> inputs);	//Sets the inputs of the network to be whatever is specified. Does not update it. (use run for that)
	};
}

#endif // !NEURALNETWORK