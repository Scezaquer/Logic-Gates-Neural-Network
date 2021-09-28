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
	"Layer" is a number in string form
	"ID" is the ID of the node
	input's IDs is an array of all the ID's of input nodes
	output's IDs is an array of all the ID's of input nodes
	*/
	this->topology = topology;
	int maxlayer = 0;
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

		maxlayer = (layer > maxlayer) ? layer : maxlayer;

		this->Network.push_back(LogicGateNN::Node(Ninputs, Noutputs, gate, layer, ID));
		
		if (layer == 0) {														//If the node is in the layer 0, 
			this->InputNodes.push_back(&this->Network[this->Network.size()]);	//adds it to the list of input nodes
		}
	}
	this->Nlayers = maxlayer+1;//Number of layers in the network

	for (LogicGateNN::Node x : this->Network) {	//Goes through every node,
		if (x.getLayer() == this->Nlayers - 1) {//if the layer of the node is the max layer,
			this->OutputNodes.push_back(&x);	//adds it to the list of outputnodes 
		}
	}

	//This has terrible time complexity (like O(n^2) from the top of my head) so very inefficient for big networks :(
	for (int x = 0; x < this->Network.size(); x++) {//For every node
		for (std::string y : topology[x][1]) {//For each of its inputs
			for (int z = 0; z < this->Network.size(); z++) {//Search for the corresponding node 
				if (y.compare(this->Network[z].getID())) {
					this->Network[x].inputNodes.push_back(&this->Network[z]);	//Adds the node to the list of inuts
					this->Network[z].outputNodes.push_back(&this->Network[x]);	//Adds the node to the list of outputs
					remove(topology[x][1].begin(), topology[x][1].end(), y);						//removes the ID from the list
					remove(topology[z][2].begin(), topology[z][2].end(), this->Network[x].getID());	//remove the link in the other node to avoid making the same link twice
				}
			}
		}

		for (std::string y : topology[x][2]) {//For each of its outputs
			for (int z = 0; z < this->Network.size(); z++) {//Search for the corresponding node 
				if (y.compare(this->Network[z].getID())) {
					this->Network[x].outputNodes.push_back(&this->Network[z]);	//Adds the node to the list of outputs
					this->Network[z].inputNodes.push_back(&this->Network[x]);	//Adds the node to the list of inputs
					remove(topology[x][2].begin(), topology[x][2].end(), y);						//removes the ID from the list
					remove(topology[z][1].begin(), topology[z][1].end(), this->Network[x].getID());	//remove the ID in the other node to avoid making the same link twice
				}
			}
		}
	}
}