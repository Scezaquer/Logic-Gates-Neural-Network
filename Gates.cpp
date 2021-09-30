#include "pch.h"
#include "Gates.h"

bool LogicGateNN::AND(std::vector<bool> inputs) {
	bool result = false;
	for (int x = 0; x < inputs.size(); x++) {
		result &= inputs[x];
	}
	return result;
}

bool LogicGateNN::OR(std::vector<bool> inputs) {
	bool result = false;
	for (int x = 0; x < inputs.size(); x++) {
		result |= inputs[x];
	}
	return result;
}

bool LogicGateNN::NAND(std::vector<bool> inputs) {
	return !LogicGateNN::AND(inputs);
}

bool LogicGateNN::NOR(std::vector<bool> inputs) {
	return !LogicGateNN::OR(inputs);
}

bool LogicGateNN::XOR(std::vector<bool> inputs) {
	bool result = false;
	for (int x = 0; x < inputs.size(); x++) {
		result ^= inputs[x];
	}
	return result;
}