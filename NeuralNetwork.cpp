#include "pch.h"
#include "NeuralNetwork.h"

LogicGateNN::NeuralNetwork::NeuralNetwork(int Ninputs, int Noutputs, int Nlayers) {
	/*
	*Constructor of the NeuralNetwork class
	*/
	this->Ninputs = Ninputs;	//
	this->Noutputs = Noutputs;	//Initializes variables
	this->Nlayers = Nlayers;	//
}