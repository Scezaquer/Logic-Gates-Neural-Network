#include <vector>
namespace LogicGateNN {
	static bool AND(std::vector<bool> inputs, int Ninputs);
	static bool OR(std::vector<bool> inputs, int Ninputs);
	static bool NAND(std::vector<bool> inputs, int Ninputs);
	static bool NOR(std::vector<bool> inputs, int Ninputs);
	static bool XOR(std::vector<bool> inputs, int Ninputs);
}