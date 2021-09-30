#include <vector>

#ifndef GATES
#define GATES

namespace LogicGateNN {
	bool AND(std::vector<bool> inputs);
	bool OR(std::vector<bool> inputs);
	bool NAND(std::vector<bool> inputs);
	bool NOR(std::vector<bool> inputs);
	bool XOR(std::vector<bool> inputs);
}

#endif // !GATES