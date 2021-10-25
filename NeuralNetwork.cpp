#include "pch.h"
#include "NeuralNetwork.h"

//TODO: A way to save and load neural networks 
//TODO: A way to mutate NNs
//TODO: A way to breed NNs

LogicGateNN::NeuralNetwork::NeuralNetwork(LogicGateNN::NeuralNetwork::Net topology) {
	/*
	Constructor of the NeuralNetwork class.
	To be used if the exact topology of the network is known (to load a saved network for example)
	Topology is a dim 3 string array containing every node in the following architecture:
	[	[ ["Type_of_the_node", "Layer", "ID"], [input's IDs], [output's IDs] ],
		[ ["Type_of_the_node", "Layer", "ID"], [input's IDs], [output's IDs] ],
		...
		[ ["Type_of_the_node", "Layer", "ID"], [input's IDs], [output's IDs] ]	]

	"Type_of_the_node" can be "AND", "NAND", "OR, "XOR", "NOR" depending on the operation it performs
	"Layer" is a number stored as a string
	"ID" is the ID of the node
	input's IDs is an array of all the ID's of input nodes
	output's IDs is an array of all the ID's of input nodes
	*/
	this->topology = topology;
	for (std::vector<std::vector<std::string>> x : this->topology) {

		//Loads the gate type
		//switch statements don't work on strings and its annoying to make one so whatever
		bool (*gate)(std::vector<bool>) = LogicGateNN::OR;
		if (x[0][0].compare("AND")) {
			gate = LogicGateNN::AND;
		}
		else if (x[0][0].compare("NAND")) {
			gate = LogicGateNN::NAND;
		}
		else if (x[0][0].compare("OR")) {
			gate = LogicGateNN::OR;
		}
		else if (x[0][0].compare("XOR")) {
			gate = LogicGateNN::XOR;
		}
		else if (x[0][0].compare("NOR")) {
			gate = LogicGateNN::NOR;
		}

		int layer = atoi(x[0][1].c_str());//Loads the layer
		std::string ID = x[0][2];
		int Ninputs = x[1].size();
		int Noutputs = x[2].size();

		this->Network[layer].push_back(LogicGateNN::Node(Ninputs, Noutputs, gate, layer, ID));

		this->Network[layer][this->Network[layer].size()].inputIDs = x[1];	//Saves the list of input ID's to create the links
		this->Network[layer][this->Network[layer].size()].outputIDs = x[2];	//Saves the list of output ID's to create the links as well
	}

	//This has terrible time complexity (like O(n^2) from the top of my head) so very inefficient for big networks :(

	for (int x = 0; x < this->Network.size(); x++) {		//For every node
		for (int b = 0; b < this->Network[x].size(); b++) {	//


			for (std::string y : this->Network[x][b].inputIDs) {		//For each of its inputs
				bool found = false;
				for (int z = 0; z < this->Network.size(); z++) {		//Search for the corresponding node 
					for (int a = 0; a < this->Network[z].size(); a++) {	//

						if (y.compare(this->Network[z][a].getID())) {
							this->Network[x][b].inputNodes.push_back(&this->Network[z][a]);		//Adds the node to the list of inputs
							this->Network[z][a].outputNodes.push_back(&this->Network[x][b]);	//Adds the node to the list of outputs

							remove(this->Network[x][b].inputIDs.begin(), this->Network[x][b].inputIDs.end(), y);							//removes the ID from the list of inputs
							remove(this->Network[x][b].outputIDs.begin(), this->Network[x][b].outputIDs.end(), this->Network[x][b].getID());//remove the link in the other node to avoid making the same link twice
							
							found = true;//leaves the loops once the corresponding node has been found and the link created
							break;
						}

					}
					if (found) { break; }
				}

			}

			for (std::string y : this->Network[x][b].outputIDs) {//For each of its outputs
				bool found = false;
				for (int z = 0; z < this->Network.size(); z++) {		//Search for the corresponding node 
					for (int a = 0; a < this->Network[z].size(); a++) {	//

						if (y.compare(this->Network[z][a].getID())) {
							this->Network[x][b].outputNodes.push_back(&this->Network[z][a]);//Adds the node to the list of outputs
							this->Network[z][a].inputNodes.push_back(&this->Network[x][b]);	//Adds the node to the list of inputs

							remove(this->Network[x][b].outputIDs.begin(), this->Network[x][b].outputIDs.end(), y);							//removes the ID from the list of outputs
							remove(this->Network[x][b].inputIDs.begin(), this->Network[x][b].inputIDs.end(), this->Network[x][b].getID());	//remove the link in the other node to avoid making the same link twice

							found = true;//leaves the loops once the corresponding node has been found and the link created
							break;
						}

					}
					if (found) { break; }
				}
			}

		}
	}
}

LogicGateNN::NeuralNetwork::NeuralNetwork(int Ninputs, int Noutputs, bool autofill) {
	/*
	Basic constructor with only the number of inputs and outputs
	if autofill is true, layers, neurons and connections will be created at random
	*/
	int Nlayers = 2;

	std::vector<LogicGateNN::Node> layer;

	for (int x = 0; x < Ninputs; x++) {		//Creates the input neurons
		layer.push_back(LogicGateNN::Node(0));
	}
	this->Network.push_back(layer);	//Adds the layer to the network
	layer.clear();					//Clears this array to use it for the next layer

	if (autofill) {
		Nlayers += std::rand() % 5;	//creates between 0 and 4 inbetween layers

		for (int x = 1; x < Nlayers - 1; x++) {					//For each inbetween layer (so excluding first and last)
			for (int y = 0; y < (std::rand() % 5) + 1; y++) {	//Creates between 1 and 5 neuron
				layer.push_back(LogicGateNN::Node(0, 0, OR, x));
			}
			this->Network.push_back(layer);	//Adds the layer to the network
			layer.clear();					//Clears this array to use it for the next layer
		}
	}

	for (int x = 0; x < Ninputs; x++) {		//Creates the input neurons
		layer.push_back(LogicGateNN::Node(0, 0, OR, Nlayers-1));
	}

	this->Network.push_back(layer);	//Adds the layer to the network
	layer.clear();	

	if (autofill){

		/////////////Creation of random connections between the neurons//////////////

		for (std::vector<LogicGateNN::Node> layer : this->Network) {	//For each Node
			for (LogicGateNN::Node x : layer) {							//

				//Input Links
				this->create_random_input_link(x, std::rand() % 3 + 1);

				//Output links
				this->create_random_output_link(x, std::rand() % 3 + 1);

			}
		}

		////////////////Sets the gates of the neurons at random////////////////

		for (int layer = 1; layer < this->Network.size(); layer++) {	//For each Node except those from the first layer
			for (LogicGateNN::Node x : Network[layer]) {				//By convention the first layer's nodes' gates are "OR", even if they technically aren't used
				
				int GateType = std::rand() % 5;	//Select a type of gate at random and sets it
				switch (GateType) {
				case 0:
					x.setGate(LogicGateNN::AND);
					break;
				case 1:
					x.setGate(LogicGateNN::OR);
					break;
				case 2:
					x.setGate(LogicGateNN::NAND);
					break;
				case 3:
					x.setGate(LogicGateNN::NOR);
					break;
				case 4:
					x.setGate(LogicGateNN::XOR);
					break;
				}
			}
		}
	}
}

std::vector<bool> LogicGateNN::NeuralNetwork::run() {
	for (int x = 1; x < this->Network.size(); x++) {
		for (LogicGateNN::Node y : this->Network[x]) {
			y.update();
		}
	}
	std::vector<bool> output;
	for (LogicGateNN::Node x : this->Network[this->Network.size() - 1]) {
		output.push_back(x.getOutput());
	}
	return output;
}

std::vector<bool> LogicGateNN::NeuralNetwork::run(int index, bool value) {
	/*
	Sets the value of the input node at the specified index and then runs the network
	*/
	this->Network[0][index].setOutput(value);
	this->Network[0][index].run();
}

std::vector<bool> LogicGateNN::NeuralNetwork::run(std::vector<bool> inputs) {
	/*
	Sets the inputs of the network to be the values in the array and runs it, returning the updated outputs
	The array must be of size = Number of inputs in the network
	*/
	this->setInputs(inputs);
	return this->run();
}

int LogicGateNN::NeuralNetwork::getNlayers() {
	//Returns the number of layers in the network
	return this->Network.size();
}

int LogicGateNN::NeuralNetwork::getNinputs() {
	//Returns the number of inputs of the network
	return this->Network[0].size();
}

int LogicGateNN::NeuralNetwork::getNoutputs() {
	//Returns the number of outputs of the network
	return this->Network[Network.size()-1].size();
}

std::vector<bool> LogicGateNN::NeuralNetwork::getOutputs() {
	//return the current values of the last layer, DOES NOT UPDATE THEM, USE NeuralNetwork.run() FOR THAT
	std::vector<bool> output;
	for (LogicGateNN::Node x : this->Network[this->Network.size() - 1]) {
		output.push_back(x.getOutput());
	}
	return output;
}

void LogicGateNN::NeuralNetwork::setInputs(std::vector<bool> inputs) {
	/*
	Sets the inputs of the network to be the values in the array
	The array must be of size = Number of inputs in the network
	*/
	for (int x = 0; x < inputs.size(); x++) {
		this->Network[0][x].setOutput(inputs[x]);
	}
}

void LogicGateNN::NeuralNetwork::create_node(int layer, bool (*gate)(std::vector<bool>)) {
	/*
	Creates a node at the specified emplacement with, by default, a random input and output
	Use LogicGateNN::NeuralNetwork::create_lonely_node to not create random input and output links
	*/
	LogicGateNN::Node node = LogicGateNN::Node(1, 1, gate, layer);
	this->create_random_input_link(node, 1);
	this->create_random_output_link(node, 1);
	this->Network[layer].push_back(node);
}

void LogicGateNN::NeuralNetwork::create_node(int layer, bool (*gate)(std::vector<bool>), std::string ID) {
	/*
	Creates a node at the specified emplacement with, by default, a random input and output, and a user-defined ID
	Use LogicGateNN::NeuralNetwork::create_lonely_node to not create random input and output links
	*/
	LogicGateNN::Node node = LogicGateNN::Node(1, 1, gate, layer, ID);
	this->create_random_input_link(node, 1);
	this->create_random_output_link(node, 1);
	this->Network[layer].push_back(node);
}

void LogicGateNN::NeuralNetwork::create_lonely_node(int layer, bool (*gate)(std::vector<bool>)) {
	/*
	Creates a node in the specified layer with no links. It is useless by itself.
	*/
	this->Network[layer].push_back(LogicGateNN::Node(1, 1, gate, layer));
}

void LogicGateNN::NeuralNetwork::create_lonely_node(int layer, bool (*gate)(std::vector<bool>), std::string ID) {
	/*
	Creates a node in the specified layer with no links and a user-defined ID. It is useless by itself.
	*/
	this->Network[layer].push_back(LogicGateNN::Node(1, 1, gate, layer, ID));
}

void LogicGateNN::NeuralNetwork::create_random_input_link(LogicGateNN::Node node, int nbr) {
	/*
	Creates n=nbr input links on the specified node at random, except if its not possible to do that many
	*/
	std::vector<LogicGateNN::Node*> InputNodes;

	for (int i = 0; i < node.getLayer(); i++) {
		for (LogicGateNN::Node b : this->Network[i]) {	//Creates an array of all potential input nodes
			InputNodes.push_back(&b);
		}
	}
	int nbrInputs = std::min(nbr, (int)InputNodes.size());	//Makes n=nbr input links, except if that's more than the possible number of inputs

	for (int i = 0; i < nbrInputs; i++) {

		int rdmindex = std::rand() % InputNodes.size();	//Selects a possible input node at random

		InputNodes[rdmindex]->addOutput(&node);			//Creates the link
		node.addInput(InputNodes[rdmindex]);				//

		InputNodes.erase(InputNodes.begin() + rdmindex);	//Deletes this node from the list of possible inputs
	}
}

void LogicGateNN::NeuralNetwork::create_random_output_link(LogicGateNN::Node node, int nbr) {
	/*
	Creates n=nbr output links on the specified node at random, except if its not possible to do that many
	*/
	std::vector<LogicGateNN::Node*> OutputNodes;

	for (int i = node.getLayer() + 1; i < this->Network.size(); i++) {
		for (LogicGateNN::Node b : this->Network[i]) {	//Creates an array of all potential output nodes
			OutputNodes.push_back(&b);
		}
	}
	int nbrOutputs = std::min(std::rand() % 3 + 1, (int)OutputNodes.size());	//Makes between 1 and 3 output links, except if that's more than the possible number of outputs

	for (int i = 0; i < nbrOutputs; i++) {

		int rdmindex = std::rand() % OutputNodes.size();	//Selects a possible input node at random

		OutputNodes[rdmindex]->addInput(&node);			//Creates the link
		node.addOutput(OutputNodes[rdmindex]);				//

		OutputNodes.erase(OutputNodes.begin() + rdmindex);	//Deletes this node from the list of possible inputs
	}
}

void LogicGateNN::NeuralNetwork::create_link(std::string ID_1, std::string ID_2) {
	LogicGateNN::Node* inpt_node;
	LogicGateNN::Node* outpt_node;
	for (std::vector<LogicGateNN::Node> x : this->Network) {
		for (LogicGateNN::Node y : x) {
			if (y.getID() == ID_1) {
				inpt_node = &y;
			}
			if (y.getID() == ID_2) {
				outpt_node = &y;
			}
		}
	}

	inpt_node->addOutput(outpt_node);
	outpt_node->addInput(inpt_node);
}

void LogicGateNN::NeuralNetwork::create_layer(int index) {
	this->Network.insert(this->Network.begin() + index, std::vector<LogicGateNN::Node>());

	for (int x = index + 1; x < this->Network.size(); x++) {
		for (LogicGateNN::Node y : this->Network[x]) {
			y.setLayer(x);
		}
	}
}

void LogicGateNN::NeuralNetwork::delete_link(LogicGateNN::Node* node, std::string ID) {
	node->delLink(ID);
}

LogicGateNN::Node* LogicGateNN::NeuralNetwork::get_node(std::string ID) {
	for (std::vector<LogicGateNN::Node> x : this->Network) {
		for (LogicGateNN::Node y : x) {
			if (y.getID() == ID) {
				return &y;
			}
		}
	}
	return nullptr;
}

void LogicGateNN::NeuralNetwork::delete_node(std::string ID) {
	LogicGateNN::Node* node = this->get_node(ID);
	for (std::string x : node->inputIDs) {
		node->delLink(x);
	}
	for (std::string x : node->outputIDs) {
		node->delLink(x);
	}

	for (int x = 0; x < this->Network[node->getLayer()].size(); x++) {
		if (this->Network[node->getLayer()][x].getID() == ID) {
			this->Network[node->getLayer()].erase(this->Network[node->getLayer()].begin() + x);
			break;
		}
	}
}