#include <string>
#include <random>

#ifndef ID_GENERATOR
#define ID_GENERATOR

namespace LogicGateNN {
	static class IDgenerator
	{
		/*
		A class containing a single function creating a random 16 character long string used to uniquely identify each node
		*/

	public:
		static std::string NewID();
	};
}

#endif