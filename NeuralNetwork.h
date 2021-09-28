/*
@file main.cpp
@author Aurélien Bück-Kaeffer
@version 0.2.1 09/28/2021
*/

//TODO: this class, and give it mutation functions to use it with genetic algorithms

#include "Node.h"
namespace LogicGateNN {
	class NeuralNetwork {

	private:
		int Ninputs;	//Number of inputs in the network
		int Noutputs;	//Number of outputs in the network
		int Nlayers;	//Number of layers

	public:
		NeuralNetwork(int Ninputs, int Noutputs, int Nlayers);//Constructor
	};
}