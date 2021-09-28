# Logic-Gates-Neural-Network
A simplistic neural-network library using only logic-gates for neurons and true/false as arguments and outputs.

Each network is an array of nodes organized in layers.

A node is a logic gate with other nodes as inputs and other nodes as outputs (except for the ones in the first and the last layer,
who have either no input or no output nodes), as well as an ID (16-char random string), a type of logic gate (AND, NAND, OR, XOR, NOR),
and a layer (position in the network).

When you run a node, it takes all the outputs from the input nodes, applies the logic gate on them and gives a single
true or false output, which is then sent to run all the output nodes if it has changed only.
This way, if a change is made in one of the nodes in the 0-layer (the inputs of the network), it will
propagate through all the network changing only what should be affected and not the other nodes to save ressources.

Upon creation, each node is given a random 16-char long ID to identify links when saving and loading the model.

A node should only receive inputs from an other node located in a previous layer, while only outputing to nodes
located on following layers. This is to prevent infinite loops from occuring. It does not have to be the layers right
before or direcly after this node however. You can skip as many as you want.


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


Once loaded, the nodes forming a network are stored in a 1 dim unordered node array (NeuralNetwork.Network).
Pointers to the input nodes are stored in NeuralNetwork.InputNodes
Pointers to the output nodes are stored in NeuralNetwork.OutputNodes
