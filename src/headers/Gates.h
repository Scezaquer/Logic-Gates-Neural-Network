static class Gates {
	static bool AND(bool inputs[]);
	static bool OR(bool inputs[]);
	static bool NAND(bool inputs[]);
	static bool NOR(bool inputs[]);
	static bool XOR(bool inputs[]);
	static bool(*gatesList[5])(bool[]) { &AND, & OR, & NAND, & NOR, & XOR };
};