#pragma once

#include "ClassHeader.h"

class Element
{
public:
	Element(unsigned short p, unsigned short n, std::string name, int dName, LINT decChance, LINT tDecChance);
	bool testDecay(Element Elements[]);
	unsigned short Protons;
	unsigned short Nutrons;
	std::string elementName;
	int decayName;
	LINT decayChance;
	LINT tDecayChance;
	LINT n;
	LINT ns;
	LINT genLargeNum(int min, int max);
	boost::random::mt19937 gen;
};

