#include "../headers/Gates.h"

bool AND(std::vector<bool> inputs, int Ninputs) {
	bool result = false;
	for (int x = 0; x < Ninputs; x++) {
		result &= inputs[x];
	}
	return result;
}

bool OR(std::vector<bool> inputs, int Ninputs) {
	bool result = false;
	for (int x = 0; x < Ninputs; x++) {
		result |= inputs[x];
	}
	return result;
}

bool NAND(std::vector<bool> inputs, int Ninputs) {
	return ! AND(inputs, Ninputs);
}

bool NOR(std::vector<bool> inputs, int Ninputs) {
	return !OR(inputs, Ninputs);
}

bool XOR(std::vector<bool> inputs, int Ninputs) {
	bool result = false;
	for (int x = 0; x < Ninputs; x++) {
		result ^= inputs[x];
	}
	return result;
}