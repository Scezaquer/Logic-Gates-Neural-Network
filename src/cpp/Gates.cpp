#include "../headers/Gates.h"

static bool Gates::AND(bool inputs[]) {
	bool result = false;
	for (bool x : inputs) {
		result &= x;
	}
	return result;
}

static bool Gates::OR(bool inputs[]) {
	bool result = false;
	for (bool x : inputs) {
		result |= x;
	}
	return result;
}

static bool Gates::NAND(bool inputs[]) {
	return ! AND(inputs);
}

static bool Gates::NOR(bool inputs[]) {
	return !OR(inputs);
}

static bool Gates::XOR(bool inputs[]) {
	bool result = false;
	for (bool x : inputs) {
		result ^= x;
	}
	return result;
}