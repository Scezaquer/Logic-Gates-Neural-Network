#include "../headers/Gates.h"

bool LogicGateNN::AND(std::vector<bool> inputs, int Ninputs) {
	bool result = false;
	for (int x = 0; x < Ninputs; x++) {
		result &= inputs[x];
	}
	return result;
}

bool LogicGateNN::OR(std::vector<bool> inputs, int Ninputs) {
	bool result = false;
	for (int x = 0; x < Ninputs; x++) {
		result |= inputs[x];
	}
	return result;
}

bool LogicGateNN::NAND(std::vector<bool> inputs, int Ninputs) {
	return !LogicGateNN::AND(inputs, Ninputs);
}

bool LogicGateNN::NOR(std::vector<bool> inputs, int Ninputs) {
	return !LogicGateNN::OR(inputs, Ninputs);
}

bool LogicGateNN::XOR(std::vector<bool> inputs, int Ninputs) {
	bool result = false;
	for (int x = 0; x < Ninputs; x++) {
		result ^= inputs[x];
	}
	return result;
}