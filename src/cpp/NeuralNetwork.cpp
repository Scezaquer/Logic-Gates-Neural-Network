#include "../headers/NeuralNetwork.h"

NeuralNetwork::NeuralNetwork(int Ninputs, int Noutputs, int Nlayers) {
	/*
	*Constructor of the NeuralNetwork class
	*/
	this->Ninputs = Ninputs;
	this->Noutputs = Noutputs;
	this->Nlayers = Nlayers;
}