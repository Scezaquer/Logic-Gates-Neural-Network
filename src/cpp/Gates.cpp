#include "../headers/Gates.h"

bool Gates::AND(bool inputs[], int Ninputs) {
	bool result = false;
	for (int x = 0; x < Ninputs; x++) {
		result &= inputs[x];
	}
	return result;
}

bool Gates::OR(bool inputs[], int Ninputs) {
	bool result = false;
	for (int x = 0; x < Ninputs; x++) {
		result |= inputs[x];
	}
	return result;
}

bool Gates::NAND(bool inputs[], int Ninputs) {
	return ! AND(inputs, Ninputs);
}

bool Gates::NOR(bool inputs[], int Ninputs) {
	return !OR(inputs, Ninputs);
}

bool Gates::XOR(bool inputs[], int Ninputs) {
	bool result = false;
	for (int x = 0; x < Ninputs; x++) {
		result ^= inputs[x];
	}
	return result;
}