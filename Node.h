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
		bool (*gate)(std::vector<bool>);	//Logic gate applied by the node

		bool output;						//Output

		//These two are private because they should only be called by delLink, else they half-ass the job
		void delInput(std::string ID);		//Removes the input with specified ID
		void delOutput(std::string ID);		//Removes the output with specified ID

	public:
		//Maybe make those private?
		std::vector<Node*> inputNodes;			//Pointers to the nodes that send inputs
		std::vector<Node*> outputNodes;			//Pointers to the nodes that shall receive the output

		std::vector<std::string> inputIDs;		//ID's of the input nodes
		std::vector<std::string> outputIDs;		//ID's of the output nodes

		Node(int Ninputs, int Noutputs, bool (*gate)(std::vector<bool>), int layer);	//Constructor
		Node(int Ninputs, int Noutputs, bool (*gate)(std::vector<bool>), int layer, std::string ID);	//Constructor of nodes loaded from a saved network
		Node(int Noutputs);													//Constructor of nodes in the first layer
		bool evaluate();													//Calculates what the output should be given the inputs and returns it
		void update();														//Updates the output given the current inputs
		void run();															//Runs the node (evaluate + sends inputs to the next nodes)
		void run(bool state);												//Runs the node after setting its output to whatever state is
		bool getOutput();													//returns the output of the node
		void setOutput(bool output);										//Sets the value of the output regardless of the inputs
		std::string getID();												//returns the ID
		int getLayer();														//returns the layer in which this node is located
		void setLayer(int layer);											//Sets the ayer of this node to be whatever the value specified is
		void addInput(LogicGateNN::Node* InNode);							//Adds an input to this node
		void addOutput(LogicGateNN::Node* OutNode);							//Adds an output to this node
		void setGate(bool (*func)(std::vector<bool>));						//Changes the logic gate applied by the node
		void delLink(std::string ID);										//Deletes the link with the node of specified ID
	};
}

#endif