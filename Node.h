#include "Gates.h"
#include "IDgenerator.h"
#include <vector>

//TODO: create first and last layer nodes

namespace LogicGateNN {
	class Node {
	private:
		std::string ID;						//Randomly generated string to identify the node
		int Ninputs;						//Number of inputs in the node
		int Noutputs;						//Number of outputs in the node
		bool (*gate)(std::vector<bool>, int);	//Logic gate applied by the node

		std::vector<Node*> inputs;			//Pointers to the nodes that send inputs
		std::vector<Node*> outputs;		//Pointers to the nodes that shall receive the output
		bool output;						//Output

	public:
		Node(int Ninputs, int Noutputs, bool (*gate)(std::vector<bool>, int));	//Constructor
		bool evaluate();													//Calculates what the output should be given the inputs
		void run();															//Runs the node (evaluate + sends inputs to the next nodes)
		bool getOutput();													//returns the output of the node
	};
}

