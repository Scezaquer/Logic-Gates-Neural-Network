#include "pch.h"
#include "Node.h"

LogicGateNN::Node::Node(int Ninputs, int Noutputs, bool (*gate)(std::vector<bool>, int)) {

	/*
	Constructor of the Node class
	Node(number_of_inputs, number_of_outputs, logic_gate)
	*/

	this->Ninputs = Ninputs;
	this->Noutputs = Noutputs;
	this->gate = gate;
	this->ID = IDgenerator::NewID();
}

bool LogicGateNN::Node::evaluate() {

	/*
	Returns the value this->output should have
	*/

	std::vector<bool> arrayinputs;

	for (int x = 0; x < this->Ninputs; x++) {				//
		arrayinputs.push_back(this->inputs[x]->output);		//Gets all the outputs from the right nodes
	}														//

	return (this->gate)(arrayinputs, this->Ninputs);
}

bool LogicGateNN::Node::getOutput() {
	return this->output;
}