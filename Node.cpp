#include "pch.h"
#include "Node.h"

LogicGateNN::Node::Node(int Ninputs, int Noutputs, bool (*gate)(std::vector<bool>), int layer) {

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

LogicGateNN::Node::Node(int Ninputs, int Noutputs, bool (*gate)(std::vector<bool>), int layer, std::string ID) {

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
		arrayinputs.push_back(this->inputNodes[x]->output);	//Gets all the outputs from the previous nodes
	}														//
	if (arrayinputs.size() > 0) {
		return (this->gate)(arrayinputs);
	}
	return this->output;
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
	/*
	Returns the layer this node is in
	*/
	return this->layer;
}

void LogicGateNN::Node::addInput(LogicGateNN::Node* InNode) {
	/*
	Adds an input to the node by adding the pointer passed as argument in the "inputNodes" array
	and the ID of said node in the "inputIDs" array
	*/
	this->inputNodes.push_back(InNode);
	this->inputIDs.push_back(InNode->getID());
}

void LogicGateNN::Node::addOutput(LogicGateNN::Node* OutNode) {
	/*
	Adds an output to the node by adding the pointer passed as argument in the "outputNodes" array
	and the ID of said node in the "outputIDs" array
	*/
	this->outputNodes.push_back(OutNode);
	this->outputIDs.push_back(OutNode->getID());
}

void LogicGateNN::Node::setGate(bool (*func)(std::vector<bool>)) {
	/*
	Sets the logic gate applied by the Node to be whatever is specified in the argument
	*/
	this->gate = func;
}

void LogicGateNN::Node::setLayer(int layer) {
	this->layer = layer;
}

void LogicGateNN::Node::delInput(std::string ID) {
	for (int x = 0; x < this->inputNodes.size(); x++) {
		if (this->inputNodes[x]->getID() == ID) {
			this->inputNodes.erase(this->inputNodes.begin() + x);
			break;
		}
	}
	for (int x = 0; x < this->inputIDs.size(); x++) {
		if (this->inputIDs[x] == ID) {
			this->inputIDs.erase(this->inputIDs.begin() + x);
			break;
		}
	}
}

void LogicGateNN::Node::delOutput(std::string ID) {
	for (int x = 0; x < this->outputNodes.size(); x++) {
		if (this->outputNodes[x]->getID() == ID) {
			this->outputNodes.erase(this->outputNodes.begin() + x);
			break;	//There should only be one link per node so thats fine
		}
	}
	for (int x = 0; x < this->outputIDs.size(); x++) {
		if (this->outputIDs[x] == ID) {
			this->outputIDs.erase(this->outputIDs.begin() + x);
			break;	//There should only be one link per node so thats fine
		}
	}
}

void LogicGateNN::Node::delLink(std::string ID) {
	for (LogicGateNN::Node* x : this->inputNodes) {
		if (x->getID() == ID) {
			x->delOutput(this->ID);
			break; //There should only be one link per node so thats fine
		}
	}
	for (LogicGateNN::Node* x : this->outputNodes) {
		if (x->getID() == ID) {
			x->delInput(this->ID);
			break;	//There should only be one link per node so thats fine
		}
	}
	this->delInput(ID);
	this->delOutput(ID);
}