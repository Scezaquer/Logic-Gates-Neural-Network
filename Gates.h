#include <vector>

#ifndef GATES
#define GATES

namespace LogicGateNN {
	bool AND(std::vector<bool> inputs, int Ninputs);
	bool OR(std::vector<bool> inputs, int Ninputs);
	bool NAND(std::vector<bool> inputs, int Ninputs);
	bool NOR(std::vector<bool> inputs, int Ninputs);
	bool XOR(std::vector<bool> inputs, int Ninputs);
}

#endif // !GATES