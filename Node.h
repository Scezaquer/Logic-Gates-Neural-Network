#include "Gates.h"
#include "IDgenerator.h"
#include <vector>

#ifndef NODE
#define NODE

namespace LogicGateNN {
	class Node {
	private:
		std::string ID;						//Randomly generated string to identify the node
		int Ninputs;						//Number of inputs in the node
		int Noutputs;						//Number of outputs in the node
		int layer;							//The layer in which this node is located in the nn. It cannot send information to nodes of te same or a previous layer to avoid infinite loops.
		bool (*gate)(std::vector<bool>, int);	//Logic gate applied by the node

		bool output;						//Output

	public:

		std::vector<Node*> inputNodes;			//Pointers to the nodes that send inputs
		std::vector<Node*> outputNodes;			//Pointers to the nodes that shall receive the output

		Node(int Ninputs, int Noutputs, bool (*gate)(std::vector<bool>, int), int layer);	//Constructor
		Node(int Ninputs, int Noutputs, bool (*gate)(std::vector<bool>, int), int layer, std::string ID);	//Constructor of nodes loaded from a saved network
		Node(int Noutputs);													//Constructor of nodes in the first layer
		bool evaluate();													//Calculates what the output should be given the inputs and returns it
		void update();														//Updates the output given the current inputs
		void run();															//Runs the node (evaluate + sends inputs to the next nodes)
		void run(bool state);												//Runs the node after setting its output to whatever state is
		bool getOutput();													//returns the output of the node
		void setOutput(bool output);										//Sets the value of the output regardless of the inputs
		std::string getID();												//returns the ID
		int getLayer();														//returns the layer
	};
}

#endif