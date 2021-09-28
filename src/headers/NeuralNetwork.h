/*
@file main.cpp
@author Aurélien Bück-Kaeffer
@version 0.2.1 09/28/2021
*/

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