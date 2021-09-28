#include "pch.h"
#include "Node.h"

LogicGateNN::Node::Node(int Ninputs, int Noutputs, bool (*gate)(std::vector<bool>, int), int layer) {

	/*
	Constructor of the Node class
	Node(number_of_inputs, number_of_outputs, logic_gate, layer)
	*/

	this->Ninputs = Ninputs;
	this->Noutputs = Noutputs;
	this->gate = gate;
	this->ID = IDgenerator::NewID();
	this->layer = layer;
	this->output = false;
}

LogicGateNN::Node::Node(int Ninputs, int Noutputs, bool (*gate)(std::vector<bool>, int), int layer, std::string ID) {

	/*
	Constructor of the Node class if the ID is already known (loaded from a saved network)
	Node(number_of_inputs, number_of_outputs, logic_gate, layer, ID)
	*/

	this->Ninputs = Ninputs;
	this->Noutputs = Noutputs;
	this->gate = gate;
	this->ID = ID;
	this->layer = layer;
	this->output = false;
}

LogicGateNN::Node::Node(int Noutputs) {
	/*
	generates a node of the first layer
	it has no inputs and must be run using the run(bool state) function
	*/
	this->layer = 0;
	this->Ninputs = 0;
	this->Noutputs = Noutputs;
	this->ID = IDgenerator::NewID();
	this->gate = LogicGateNN::OR;
	this->output = false;
}

bool LogicGateNN::Node::evaluate() {

	/*
	Returns the value this->output should have
	*/

	std::vector<bool> arrayinputs;

	for (int x = 0; x < this->Ninputs; x++) {				//
		arrayinputs.push_back(this->inputNodes[x]->output);		//Gets all the outputs from the previous nodes
	}														//

	return (this->gate)(arrayinputs, this->Ninputs);
}

void LogicGateNN::Node::update() {
	/*
	Updates the output given the current inputs
	*/
	this->setOutput(this->evaluate());
}

bool LogicGateNN::Node::getOutput() {
	/*
	returns the current output of the Node.
	/!\ Does not evaluate it /!\
	If changes have been made, you must call the .update() function
	on this node before getting the correct output.
	*/
	return this->output;
}

void LogicGateNN::Node::setOutput(bool output) {
	/*
	Sets the output of the node to be the value of output regardless fo the inputs.
	I do not recommend using this on anything other than the first layer nodes.
	*/
	this->output = output;
}

std::string LogicGateNN::Node::getID() {
	return this->ID;
}

void LogicGateNN::Node::run() {
	/*
	This function updates the output depending on the current inputs.
	It runs all the output nodes if the output from this one has changed only,
	to only compute what is necessary
	*/

	bool previousOutput = this->output;	//Saves the current output
	this->update();						//Updates the output with the current inputs
	
	if (previousOutput != this->output) {	//If the output changed
		for (Node* x : this->outputNodes) {	//
			x->run();						//Runs all the nodes dependant on said output
		}
	}

}

void LogicGateNN::Node::run(bool state) {
	/*
	Sets the output to the value of state, and runs all the output nodes if it has changed.
	I do not recommed using this on anything other than nodes from the first layer
	*/

	bool previousOutput = this->output;
	if (previousOutput != state) {	//If the output changed
		this->setOutput(state);		//Sets the output to the value of state
		for (Node* x : this->outputNodes) {	//
			x->run();						//Runs all the nodes dependant on said output
		}
	}
}

int LogicGateNN::Node::getLayer() {
	return this->layer;
}