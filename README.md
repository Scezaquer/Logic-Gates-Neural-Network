# Logic-Gates-Neural-Network
A simplistic neural-network library using only logic-gates instead of perceptrons and true/false as arguments and outputs.

# Requirements
This is a pure C++ package. It dosen't have any requirements.

# About
Namespace : LogicGateNN

Each network is an array of nodes organized in layers.

A node is a logic gate with other nodes as inputs and other nodes as outputs (except for the ones in the first and the last layer,
who have either no input or no output nodes), as well as an ID (by default a 16-char random string), a type of logic gate (AND, NAND, OR, XOR, NOR),
and a layer (position in the network).

When you run a node, it takes all the outputs from the input nodes, applies the logic gate on them and gives a single
true or false output, which is then sent to run all the output nodes if it has changed only.
This way, if a change is made in one of the nodes in the 0-layer (the inputs of the network), it will
propagate through all the network changing only what should be affected and not the other nodes to save ressources.

Upon creation, each node is given a random 16-char long ID to identify links when saving and loading the model.

A node should only receive inputs from an other node located in a previous layer, while only outputing to nodes
located on following layers. This is to prevent infinite loops from occuring. It does not have to be the layers right
before or direcly after this node however. You can skip as many as you want.

# Network topology
When saving a neural network, we are saving its topology. Reverse when loading it.

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


Once loaded, the nodes forming a network are stored in a 2 dim node array (NeuralNetwork.Network).

# Mutating and breeding
This package is meant to be used combined with a genetic algorithm to evolve quality agents. Therefore I am currently working on mutation and breeding methods.

# Documentation

## Logic Gates
`bool LogicGateNN::AND(std::vector<bool> inputs)` : function performing the AND operation on the array of inputs and returning the result
	
`bool LogicGateNN::OR(std::vector<bool> inputs)` : function performing the OR operation on the array of inputs and returning the result
	
`bool LogicGateNN::NAND(std::vector<bool> inputs)` : function performing the NAND operation on the array of inputs and returning the result
	
`bool LogicGateNN::NOR(std::vector<bool> inputs)` : function performing the NOR operation on the array of inputs and returning the result
	
`bool LogicGateNN::XOR(std::vector<bool> inputs)` : function performing the XOR operation on the array of inputs and returning the result


## IDgenerator

`LogicGateNN::IDgenerator` : A static class containing a single function, `LogicGateNN::IDgenerator::NewID()`, which generates a random 16 character long string to be used as an ID for Nodes. This does not check if the string already exist since the probability of that happening is one in 62^16.


## Node

`LogicgateNN::Node` : A class to make the nodes in a network


### Private Attributes
`std::string ID` : Randomly generated string to identify the node

`int Ninputs` : Number of inputs in the node

`int Noutputs` : Number of outputs in the node

`int layer` : The layer in which this node is located in the nn. It cannot send information to nodes of te same or a previous layer to avoid infinite loops.

`bool (*gate)(std::vector<bool>)` : Logic gate applied by the node

`bool output` : Value returned by the node



### Public Attributes

`std::vector<Node*> inputNodes` : Pointers to the nodes that send inputs

`std::vector<Node*> outputNodes` : Pointers to the nodes that shall receive the output

`std::vector<std::string> inputIDs` : ID's of the input nodes

`std::vector<std::string> outputIDs` : ID's of the output nodes


### Constructors

`LogicgateNN::Node::Node(int Ninputs, int Noutputs, bool (*gate)(std::vector<bool>), int layer, std::string ID)` : Constructor for the `LogicgateNN::Node` class.

`int Ninputs` : Number of inputs to this node

`int Noutputs` : Number of outputs to this node

`bool (*gate)(std::vector<bool>)` : One of the logic-gates functions

`int layer` : The layer of the network in which the node is

`std::string ID` : Optional, a user-defined ID for said node. If not specified, `LogicGateNN::IDgenerator::NewID()` will be called to make a new-one.


`LogicgateNN::Node::Node(int Noutputs)` : Constructor for nodes in the first layer


### Evaluate
`bool LogicgateNN::Node::evaluate()` : Calculates what the output should be given the current inputs and returns it.


### Update
`void LogicgateNN::Node::update()` : Updates the output given the current inputs 


### Run
`void LogicgateNN::Node::run()` : Runs the node (evaluate + sends inputs to the next nodes). This function updates the output depending on the current inputs. It runs all the output nodes if the output from this one has changed only, to only compute what is necessary.

`void LogicgateNN::Node::run(bool state)` : Runs the node after setting its output to whatever state is if it has changed. I do not recommed using this on anything other than nodes from the first layer


### getOutput
`bool LogicgateNN::Node::getOutput()` : Returns the output of the node /!\ Does not evaluate it /!\ If changes have been made, you must call the .update() function on this node before getting the correct output.


### setOutput
`void LogicgateNN::Node::setOutput(bool output)` : Sets the value of the output regardless of the inputs. I do not recommend using this on anything other than the first layer nodes.


### getID
`std::string LogicgateNN::Node::getID()` : Returns the ID


### getLayer
`int LogicgateNN::Node::getLayer()` : Returns the layer in which this node is located


### addInput
`void LogicgateNN::Node::addInput(LogicGateNN::Node* InNode)` : Adds an input to the node by adding the pointer passed as argument in the "inputNodes" array and the ID of said node in the "inputIDs" array


### addOutput
`void LogicgateNN::Node::addOutput(LogicGateNN::Node* OutNode)` : Adds an output to the node by adding the pointer passed as argument in the "outputNodes" array and the ID of said node in the "outputIDs" array


### setGate
`void LogicgateNN::Node::setGate(bool (*func)(std::vector<bool>))` : Changes the logic gate applied by the node


## NeuralNetwork

`LogicGateNN::NeuralNetwork` : The most important class in this package. Its the actual network of nodes performing operations


### Private Attributes
`LogicGateNN::Net topology` : Topology of the network (an array of strings dim 3 containing information to build each node (see NeuralNetwork.cpp))

`std::vector<std::vector<LogicGateNN::Node>> Network` : Array of dim 2 containing all the nodes making up the network


### Public Attributes

`typedef std::vector<std::vector<std::vector<std::string>>> Net` : A type corresponding to an array of dim 3 containing strings


### Constructors
`LogicGateNN::NeuralNetwork::NeuralNetwork(Net topology)` : 
Constructor of the NeuralNetwork class.

To be used if the exact topology of the network is known (to load a saved network for example)

Topology is a dim 3 string array containing every node in the following architecture:

	[	[ ["Type_of_the_node", "Layer", "ID"], [input's IDs], [output's IDs] ],
		[ ["Type_of_the_node", "Layer", "ID"], [input's IDs], [output's IDs] ],
		...
		[ ["Type_of_the_node", "Layer", "ID"], [input's IDs], [output's IDs] ]	]

`Type_of_the_node` can be "AND", "NAND", "OR, "XOR", "NOR" depending on the operation it performs

`Layer` is a number stored as a string

`ID` is the ID of the node

`[input's IDs]` is an array of all the ID's of input nodes

`[output's IDs]` is an array of all the ID's of input nodes



`LogicGateNN::NeuralNetwork::NeuralNetwork(int Ninputs, int Noutputs,  bool autofill)` : Basic constructor with only the number of inputs and outputs. If autofill is true, layers, neurons and connections will be created at random. Ideal to generate an initial population to then evolve.


## run
`std::vector<bool> LogicGateNN::NeuralNetwork::run()` : Main function of the nn, updates every node, and consequently the output of the network. Returns said output

`std::vector<bool> LogicGateNN::NeuralNetwork::run(int index, bool value)` : Sets the value of the input node at the specified index and ther runs the network

`std::vector<bool> LogicGateNN::NeuralNetwork::run(std::vector<bool> inputs)` : Sets the inputs of the network to be the values in the array and runs it, returning the updated outputs. The array must be of size = Number of inputs in the network.


## getNlayers
`int LogicGateNN::NeuralNetwork::getNlayers()` : Returns the number of layers in the network


## getNinputs
`int LogicGateNN::NeuralNetwork::getNinputs()` : Returns the number of inputs of the network


## getNoutputs
`int LogicGateNN::NeuralNetwork::getNoutputs()` : Returns the number of outputs of the network


## getOutputs
`std::vector<bool> LogicGateNN::NeuralNetwork::getOutputs()` : return the current values of the last layer, does not update them, use `NeuralNetwork.run()` for that


## setInputs
`void LogicGateNN::NeuralNetwork::setInputs(std::vector<bool> inputs)` : Sets the inputs of the network to be the values in the array. The array must be of size = Number of inputs in the network


## create_node
`void LogicGateNN::NeuralNetwork::create_node(int layer, bool (*gate)(std::vector<bool>), std::string ID)` : Creates a node at the specified emplacement with, by default, a random input and output. Use LogicGateNN::NeuralNetwork::create_lonely_node to not create random input and output links.

`int layer` : Layer the new node will be in

`bool (*gate)(std::vector<bool>)` : Logic gate applied by the node

`std::string ID` : Optional, sets a user-defined ID to that node. By default calls `LogicGateNN::IDgenerator::NewID()` to generate one.


## create_lonely_node
`void LogicGateNN::NeuralNetwork::create_lonely_node(int layer, bool (*gate)(std::vector<bool>), std::string ID)` : Creates a node in the specified layer with no links. It is useless by itself.

`int layer` : Layer the new node will be in

`bool (*gate)(std::vector<bool>)` : Logic gate applied by the node

`std::string ID` : Optional, sets a user-defined ID to that node. By default calls `LogicGateNN::IDgenerator::NewID()` to generate one.


## create_random_input_link
`void LogicGateNN::NeuralNetwork::create_random_input_link(LogicGateNN::Node node, int nbr)`: Creates n=nbr input links on the specified node at random, except if its not possible to do that many links.

`LogicGateNN::Node node` : Node to which we add the input link

`int nbr` : Number of links created at random (or less if its not possible to do this many links)


## create_random_output_link
`void LogicGateNN::NeuralNetwork::create_random_output_link(LogicGateNN::Node node, int nbr)` : Creates n=nbr output links on the specified node at random, except if its not possible to do that many

`LogicGateNN::Node node` : Node to which we add the output link

`int nbr` : Number of links created at random (or less if its not possible to do this many links)
