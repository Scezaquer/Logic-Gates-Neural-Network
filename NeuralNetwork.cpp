#include "pch.h"
#include "NeuralNetwork.h"

//TODO: A way to save and load neural networks 

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
		bool (*gate)(std::vector<bool>, int) = LogicGateNN::OR;
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
	layer.clear();					//Clears this array to use it for the next layer

	if (autofill){//Creation of random connections between the neurons
		for (std::vector<LogicGateNN::Node> layer : this->Network) {
			for (LogicGateNN::Node x : layer) {
				if (x.getLayer() != 0) {	//crée des connections inputs uniquement si c'est pas dans la first layer

				}
			}
		}
	}
}

int LogicGateNN::NeuralNetwork::getNlayers() {
	return this->Network.size();
}

int LogicGateNN::NeuralNetwork::getNinputs() {
	return this->Network[0].size();
}

int LogicGateNN::NeuralNetwork::getNoutputs() {
	return this->Network[Network.size()-1].size();
}